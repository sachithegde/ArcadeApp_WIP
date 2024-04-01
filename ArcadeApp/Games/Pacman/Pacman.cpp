#include "Pacman.h"
#include "../../Utils/Utils.h"


void Pacman::Init(const SpriteSheet& spriteSheet, const std::string& animationPath, const Vec2D& initialPos, uint32_t movementSpeed, bool updateSpriteOnMovement, const Color&spriteColor)
{
	Actor::Init(spriteSheet, animationPath, initialPos, movementSpeed, false, spriteColor);

	ResetToFirstAnimation();
	ResetScore();
	mIsDying = false;
	ResetGhostEatenMultiplier();

}
void Pacman::Update(uint32_t dt)
{
	if(mIsDying)
	{
		mSprite.Update(dt);
		mIsDying = !IsFinishedAnimation();
		return;
	}

	Actor::Update(dt);
}

void Pacman::SetMovementDirection(PacmanMovement movementDir)
{
	PacmanMovement currentDirection = GetMovementDirection();

	if(movementDir == PACMAN_MOVEMENT_LEFT && currentDirection != PACMAN_MOVEMENT_LEFT)
	{
		SetAnimation("move_left", true);
		ResetDelta();
	}
	else if(movementDir == PACMAN_MOVEMENT_RIGHT && currentDirection != PACMAN_MOVEMENT_RIGHT)
	{
		SetAnimation("move_right", true);
		ResetDelta();
	}
	else if(movementDir == PACMAN_MOVEMENT_DOWN && currentDirection != PACMAN_MOVEMENT_DOWN)
	{
		SetAnimation("move_down", true);
		ResetDelta();
	}
	else if(movementDir == PACMAN_MOVEMENT_UP && currentDirection != PACMAN_MOVEMENT_UP)
	{
		SetAnimation("move_up", true);
		ResetDelta();
	}

	Actor::SetMovementDirection(movementDir);
}

void Pacman::ResetToFirstAnimation()
{
	SetAnimation("move_left", true);
	Stop();
}

void Pacman::EatenByGhost()
{
	SetAnimation("death", false);
	mIsDying = true;
	ResetGhostEatenMultiplier();
}

void Pacman::ResetScore()
{
	mScore = 0;
}

void Pacman::AteItem(uint32_t value)
{
	AddToScore(value);
}

void Pacman::AteGhost(uint32_t value)
{
	AddToScore(value * mGhostMultiplier);
	mGhostMultiplier *= 2;
}

void Pacman::AddToScore(uint32_t value)
{
	mScore += value;
}

