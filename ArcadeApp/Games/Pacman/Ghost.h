#ifndef GAMES_PACMAN_GHOST_H_
#define GAMES_PACMAN_GHOST_H_

#include "Actor.h"
#include "../../Graphics/Color.h"
#include "PacmanGameUtils.h"
#include "../../Shapes/AARectangle.h"

enum GhostName
{
	BLINKY = 0,
	PINKY,
	INKY,
	CLYDE,
	NUM_GHOSTS
};

enum GhostState
{
	GHOST_STATE_ALIVE = 0,
	GHOST_STATE_VULNERABLE,
	GHOST_STATE_VULNERABLE_ENDING,
	GHOST_STATE_DEAD
};

class GhostDelegate
{
public:
	virtual ~GhostDelegate(){}
	virtual void GhostDelegateGhostStateChangedTo(GhostState lastState, GhostState state) = 0;
	virtual void GhostWasReleasedFromPen() = 0;
	virtual void GhostWasResetToFirstPosition() = 0;
};

class Ghost: public Actor
{
public:
	static const uint32_t VULNERABILITY_TIME = 6000;
	static const uint32_t VULNERABILITY_ENDING_TIME = 4000;

	Ghost();
	virtual void Init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vec2D& initialPos, uint32_t movementSpeed, bool updateSpriteOnMovement, const Color&spriteColor = Color::White()) override;
	virtual void Update(uint32_t dt) override;

	void SetStateToVulnerable();
	virtual void SetMovementDirection(PacmanMovement direction) override;
	virtual void Stop() override;

	void EatenByPacman();
	void ResetToFirstPosition();

	void ReleaseFromPen();
	inline bool IsReleased() const {return mIsReleased;}

	inline bool IsDead() const {return mState == GHOST_STATE_DEAD;}
	inline bool IsVulnerable() const {return mState == GHOST_STATE_VULNERABLE || mState == GHOST_STATE_VULNERABLE_ENDING;}
	inline bool IsAlive() const {return mState == GHOST_STATE_ALIVE;}
	inline uint32_t GetPoints() const {return mPoints;}
	inline void LockCanChangeDirection() {mCanChangeDirection = false;}
	inline bool CanChangeDirection() const {return mCanChangeDirection;}

	void SetGhostDelegate(GhostDelegate& delegate) {mDelegate = &delegate;}
private:
	void SetGhostState(GhostState state);

	friend class GhostAI;

	uint32_t mVulnerabilityTimer;
	uint32_t mPoints;
	GhostState mState;
	bool mCanChangeDirection;
	Vec2D mInitialPos;
	bool mIsReleased;
	GhostDelegate* mDelegate;
};







#endif
