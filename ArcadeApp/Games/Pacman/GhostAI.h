#ifndef GAMES_PACMAN_GHOSTAI_H_
#define GAMES_PACMAN_GHOSTAI_H_


#include "Ghost.h"
#include "PacmanGameUtils.h"
#include <random>
#include <stdint.h>

class PacmanLevel;
class Screen;
class Pacman;

enum GhostAIState
{
	GHOST_AI_STATE_START = 0,
	GHOST_AI_STATE_IN_PEN,
	GHOST_AI_STATE_EXIT_PEN,
	GHOST_AI_STATE_CHASE,
	GHOST_AI_STATE_SCATTER,
	GHOST_AI_STATE_GO_TO_PEN
};

class GhostAI: public GhostDelegate
{
public:

	GhostAI();
	void Init(Ghost& ghost, uint32_t lookAheadDistance, const Vec2D& scatterTarget, const Vec2D& ghostPenTarget, const Vec2D& ghostExitPenPosition, GhostName name);

	PacmanMovement Update(uint32_t dt, const Pacman& pacman, const PacmanLevel& level, const std::vector<Ghost>& ghosts);
	void Draw(Screen& screen);

	inline bool WantsToLeavePen() const {return mState == GHOST_AI_STATE_EXIT_PEN;}
	inline bool IsInPen() const {return mState == GHOST_AI_STATE_IN_PEN || mState == GHOST_AI_STATE_START;}
	inline bool IsEnteringPen() const {return mState == GHOST_AI_STATE_GO_TO_PEN;}


	virtual void GhostDelegateGhostStateChangedTo(GhostState lastState, GhostState state) override;
	virtual void GhostWasReleasedFromPen() override;
	virtual void GhostWasResetToFirstPosition() override;

private:

	void SetState(GhostAIState state);
	void ChangeTarget(const Vec2D& target);
	Vec2D GetChaseTarget(uint32_t dt, const Pacman& pacman, const PacmanLevel& level, const std::vector<Ghost>& ghosts);

	Vec2D mGhostExitPenPosition;
	Vec2D mGhostPenTarget;
	Vec2D mScatterTarget;
	Vec2D mTarget;
	uint32_t mLookAheadDistance;
	Ghost* mnoptrGhost;
	GhostName mName;
	std::default_random_engine mAIRandomGenerator;
	GhostAIState mState;
	GhostAIState mLastState;
	uint64_t mTimer;
};

#endif 
