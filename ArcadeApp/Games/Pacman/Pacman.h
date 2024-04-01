#ifndef GAMES_PACMAN_PACMAN_H_
#define GAMES_PACMAN_PACMAN_H_

#include"PacmanGameUtils.h"
#include"Actor.h"
#include"../../Utils/Vec2D.h"
#include <stdint.h>
#include<string>

class Screen;
class SpriteSheet;
//class Actor;

class Pacman: public Actor
{
public:
	virtual void Init(const SpriteSheet& spriteSheet, const std::string& animationPath, const Vec2D& initialPos, uint32_t movementSpeed, bool updateSpriteOnMovement, const Color& spriteColor = Color::White()) override;
	virtual void Update(uint32_t dt) override;
	virtual void SetMovementDirection(PacmanMovement movementDir) override;

	void ResetToFirstAnimation();
	void EatenByGhost();
	void ResetScore();
	void AteItem(uint32_t value);
	void AteGhost(uint32_t value);

	inline void ResetGhostEatenMultiplier() {mGhostMultiplier = 1;}
	inline uint32_t Score() const {return mScore;}

private:
	void AddToScore(uint32_t value);

	uint32_t mScore;
	uint32_t mGhostMultiplier;
	bool mIsDying;
};


#endif 
