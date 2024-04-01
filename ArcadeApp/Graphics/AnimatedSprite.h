#ifndef GRAPHICS_ANIMATEDSPRITE_H_
#define GRAPHICS_ANIMATEDSPRITE_H_

#include "AnimationPlayer.h"
#include "../Utils/Vec2D.h"
#include "Color.h"
#include <stdint.h>
#include <string>


class AARectangle;
class Screen;
class SpriteSheet;

class AnimatedSprite
{
public:
	AnimatedSprite();
	void Init(const std::string& animationsPath, const SpriteSheet& spriteSheet, const Color& color = Color::White());
	void Update(uint32_t dt);
	void Draw(Screen& theScreen);

	void SetAnimation(const std::string& animationName, bool looped);
	Vec2D Size() const;
	void Stop();
	const AARectangle GetBoundingBox() const;

	inline Vec2D Position() const {return mPosition;}
	inline void SetPosition(const Vec2D& position) {mPosition = position;}
	inline void MoveBy(const Vec2D& delta) {mPosition += delta;}
	inline bool IsFinishedPlayingAnimation() const {return mAnimationPlayer.IsFinishedPlaying();}
	inline const Color& GetColor() const {return mColor;}
	const SpriteSheet* GetSpriteSheet() const {return mnoptrSpriteSheet;}

private:
	const SpriteSheet * mnoptrSpriteSheet;
	AnimationPlayer mAnimationPlayer;
	Vec2D mPosition;
	Color mColor;
};

#endif 
