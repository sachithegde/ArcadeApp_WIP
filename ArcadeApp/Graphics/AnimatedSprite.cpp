#include "AnimatedSprite.h"
#include "../Shapes/AARectangle.h"
#include "Screen.h"

AnimatedSprite::AnimatedSprite():mPosition(Vec2D::Zero), mnoptrSpriteSheet(nullptr)
{

}

void AnimatedSprite::Init(const std::string& animationsPath, const SpriteSheet& spriteSheet, const Color& color)
{
	mAnimationPlayer.Init(animationsPath);
	mnoptrSpriteSheet = &spriteSheet;
	mColor = color;
}

void AnimatedSprite::Update(uint32_t dt)
{
	mAnimationPlayer.Update(dt);
}

void AnimatedSprite::Draw(Screen& theScreen)
{
	AnimationFrame frame = mAnimationPlayer.GetCurrentAnimationFrame();

	Color frameColor = frame.frameColor;

	if(!frame.frameColorSet)
	{
		frameColor = mColor;
	}

	theScreen.Draw(*mnoptrSpriteSheet, frame.frame, mPosition + frame.offset, frameColor);

	if(frame.overlay.size() > 0)
	{
		theScreen.Draw(*mnoptrSpriteSheet, frame.overlay, mPosition, frame.overlayColor);
	}
}

void AnimatedSprite::SetAnimation(const std::string& animationName, bool looped)
{
	mAnimationPlayer.Play(animationName, looped);
}

Vec2D AnimatedSprite::Size() const
{
	return mAnimationPlayer.GetCurrentAnimationFrame().size;
}

void AnimatedSprite::Stop()
{
	mAnimationPlayer.Stop();
}

const AARectangle AnimatedSprite::GetBoundingBox() const
{
	AARectangle bbox = {mPosition, static_cast<unsigned int>(Size().GetX()), static_cast<unsigned int>(Size().GetY())};
	return bbox;
}


