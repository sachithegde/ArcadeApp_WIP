#include "GhostAI.h"
#include "../../Graphics/Screen.h"
#include "PacmanLevel.h"
#include "Pacman.h"
#include <cassert>
#include <algorithm>
#include "../../Graphics/Color.h"
#include "../../Shapes/Circle.h"

namespace
{
	const uint32_t PEN_WAIT_DURATION = 5000;
	const uint32_t SCATTER_MODE_DURATION = 10000;
}

GhostAI::GhostAI():mnoptrGhost(nullptr)
{

}

void GhostAI::Init(Ghost& ghost, uint32_t lookAheadDistance, const Vec2D& scatterTarget, const Vec2D& ghostPenTarget, const Vec2D& ghostExitPenPosition, GhostName name)
{
	mGhostPenTarget = ghostPenTarget;
	mGhostExitPenPosition = ghostExitPenPosition;
	mScatterTarget = scatterTarget;
	mLookAheadDistance = lookAheadDistance;
	mnoptrGhost = &ghost;
	mName = name;
	std::random_device r;
	mAIRandomGenerator.seed(r());
	mTimer = 0;
	SetState(GHOST_AI_STATE_SCATTER);
	mLastState = GHOST_AI_STATE_SCATTER;
}

PacmanMovement GhostAI::Update(uint32_t dt, const Pacman& pacman, const PacmanLevel& level, const std::vector<Ghost>& ghosts)
{
	if(mnoptrGhost)
	{

		if(mState == GHOST_AI_STATE_START)
		{
			return PACMAN_MOVEMENT_NONE;
		}

		if(mState == GHOST_AI_STATE_IN_PEN)
		{
			mTimer += dt;

			if(mTimer >= PEN_WAIT_DURATION)
			{
				SetState(GHOST_AI_STATE_EXIT_PEN);
			}

			return PACMAN_MOVEMENT_NONE;

		}

		if(mState == GHOST_AI_STATE_GO_TO_PEN && mnoptrGhost->Position() == mGhostPenTarget)
		{
			SetState(GHOST_AI_STATE_IN_PEN);

			mnoptrGhost->SetGhostState(GHOST_STATE_ALIVE);

			return PACMAN_MOVEMENT_NONE;
		}

		if(mState == GHOST_AI_STATE_EXIT_PEN && mnoptrGhost->Position() == mGhostExitPenPosition)
		{
			SetState(GHOST_AI_STATE_SCATTER);
		}

		if(mState == GHOST_AI_STATE_SCATTER)
		{
			mTimer += dt;
			if(mTimer >= SCATTER_MODE_DURATION)
			{
				SetState(GHOST_AI_STATE_CHASE);
			}
		}

		PacmanMovement currentDirection = mnoptrGhost->GetMovementDirection();

		std::vector<PacmanMovement> tempDirections;
		std::vector<PacmanMovement> possibleDirections;

		possibleDirections = GetPerpendicularMovements(currentDirection);

		if(currentDirection != PACMAN_MOVEMENT_NONE)
		{
			possibleDirections.push_back(currentDirection);
		}

		for(const auto& pDirection : possibleDirections)
		{
			tempDirections.push_back(pDirection);
		}

		possibleDirections.clear();

		for(const auto& direction : tempDirections)
		{
			if(!level.WillCollide(*mnoptrGhost, *this, direction))
			{
				possibleDirections.push_back(direction);
			}
		}

		
		if(possibleDirections.size() == 0)
		{

			std::cout << mName << " can't go anywhere!" << std::endl;
			std::cout << mState << " is the state" << std::endl;
			assert(false && "Why can't we go anywhere?");
		}

		std::sort(possibleDirections.begin(), possibleDirections.end(), [](const PacmanMovement& direction1, const PacmanMovement& direction2){
			return direction1 < direction2;
		});


		if(mnoptrGhost->IsVulnerable() && (mState == GHOST_AI_STATE_SCATTER || mState == GHOST_AI_STATE_CHASE))
		{
			std::uniform_int_distribution<size_t> distribution(0, possibleDirections.size()-1);
			return possibleDirections[static_cast<int>(distribution(mAIRandomGenerator))];
		}

		if(mState == GHOST_AI_STATE_CHASE)
		{
			ChangeTarget(GetChaseTarget(dt, pacman, level, ghosts));
		}

		PacmanMovement directionToGoIn = PACMAN_MOVEMENT_NONE;

		uint32_t lowestDistance = UINT32_MAX;

		for(const auto& direction : possibleDirections)
		{
			Vec2D movementVec = GetMovementVector(direction) * mLookAheadDistance;

			AARectangle bbox = mnoptrGhost->GetBoundingBox();

			bbox.MoveBy(movementVec);

			uint32_t distanceToTarget = bbox.GetCenterPoint().Distance(mTarget);

			if(distanceToTarget < lowestDistance)
			{
				directionToGoIn = direction;
				lowestDistance = distanceToTarget;
			}
		}

		assert(directionToGoIn != PACMAN_MOVEMENT_NONE);

		return directionToGoIn;
	}

	return PACMAN_MOVEMENT_NONE;
}

void GhostAI::Draw(Screen& screen)
{
	if(mnoptrGhost)
	{
		Circle targetCircle = Circle(mTarget, 4);

		screen.Draw(targetCircle, mnoptrGhost->GetSpriteColor(), true, mnoptrGhost->GetSpriteColor());

		AARectangle bbox = mnoptrGhost->GetBoundingBox();

		bbox.MoveBy(GetMovementVector(mnoptrGhost->GetMovementDirection())*mnoptrGhost->GetBoundingBox().GetWidth());

		Color c = Color(mnoptrGhost->GetSpriteColor().GetRed(), mnoptrGhost->GetSpriteColor().GetGreen(), mnoptrGhost->GetSpriteColor().GetBlue(), 200);

		screen.Draw(bbox, mnoptrGhost->GetSpriteColor(), true, c);
	}
}

void GhostAI::ChangeTarget(const Vec2D& target)
{
	mTarget = target;
}

Vec2D GhostAI::GetChaseTarget(uint32_t dt, const Pacman& pacman, const PacmanLevel& level, const std::vector<Ghost>& ghosts)
{
	Vec2D target;

	switch(mName)
	{
	case BLINKY:
		target = pacman.GetBoundingBox().GetCenterPoint();
		break;

	case PINKY:
		target = pacman.GetBoundingBox().GetCenterPoint() + 2 * GetMovementVector(pacman.GetMovementDirection()) * pacman.GetBoundingBox().GetWidth();
		break;

	case INKY:
	{
		Vec2D pacmanOffsetPoint = pacman.GetBoundingBox().GetCenterPoint() + (GetMovementVector(pacman.GetMovementDirection()) * pacman.GetBoundingBox().GetWidth());

		target = (pacmanOffsetPoint - ghosts[BLINKY].GetBoundingBox().GetCenterPoint())*2 + ghosts[BLINKY].GetBoundingBox().GetCenterPoint();
	}
		break;
	case CLYDE:
	{
		auto distanceToPacman = mnoptrGhost->GetBoundingBox().GetCenterPoint().Distance(pacman.GetBoundingBox().GetCenterPoint());

		if(distanceToPacman > pacman.GetBoundingBox().GetWidth()*4)
		{
			target = pacman.GetBoundingBox().GetCenterPoint();
		}
		else
		{
			target = mScatterTarget;
		}
	}
	break;
	case NUM_GHOSTS:
		assert(false && "DO NOT PASS NUM_GHOSTS AS THE GHOST NAME!");
	}

	return target;
}

void GhostAI::SetState(GhostAIState state)
{
	if(mState == GHOST_AI_STATE_SCATTER || mState == GHOST_AI_STATE_CHASE)
	{
		mLastState = mState;
	}

	mState = state;

	switch(state) {
	case GHOST_AI_STATE_IN_PEN:
		mTimer = 0;
		break;
	case GHOST_AI_STATE_GO_TO_PEN:
		{
			Vec2D target = {mGhostPenTarget.GetX() + mnoptrGhost->GetBoundingBox().GetWidth()/2, mGhostPenTarget.GetY() - mnoptrGhost->GetBoundingBox().GetHeight()/2};

			ChangeTarget(target);
		}
		break;
	case GHOST_AI_STATE_EXIT_PEN:
		ChangeTarget(mGhostExitPenPosition);
		break;
	case GHOST_AI_STATE_SCATTER:
		mTimer = 0;
		ChangeTarget(mScatterTarget);
		break;
	default:
		break;
	}
}

void GhostAI::GhostDelegateGhostStateChangedTo(GhostState lastState, GhostState state)
{
	if(mnoptrGhost && mnoptrGhost->IsReleased() && (lastState == GHOST_STATE_VULNERABLE || lastState == GHOST_STATE_VULNERABLE_ENDING)
			&& !(IsInPen() || WantsToLeavePen()))
	{
		mnoptrGhost->SetMovementDirection(GetOppositeDirection(mnoptrGhost->GetMovementDirection()));
	}

	if(state == GHOST_STATE_DEAD)
	{
		SetState(GHOST_AI_STATE_GO_TO_PEN);
	}
	else if((lastState == GHOST_STATE_VULNERABLE || lastState == GHOST_STATE_VULNERABLE_ENDING) && state == GHOST_STATE_ALIVE)
	{
		if(mState == GHOST_AI_STATE_CHASE || mState == GHOST_AI_STATE_SCATTER)
		{
			SetState(mLastState);
		}
	}

}

void GhostAI::GhostWasReleasedFromPen()
{
	if(mState == GHOST_AI_STATE_START)
	{
		SetState(GHOST_AI_STATE_EXIT_PEN);
	}
}

void GhostAI::GhostWasResetToFirstPosition()
{
	SetState(GHOST_AI_STATE_START);
}
