#ifndef GAMES_BREAKOUT_BALL_H_
#define GAMES_BREAKOUT_BALL_H_

#include "../../Shapes/AARectangle.h"
#include <stdint.h>

class Screen;
struct BoundaryEdge;

class Ball
{
public:
	Ball();
	Ball(const Vec2D& pos, float radius);

	void Update(uint32_t dt);
	void Draw(Screen& screen);
	void MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& pointOnEdge, bool limitToEdge);
	inline void Stop() {mVelocity = Vec2D::Zero;}
	void MoveTo(const Vec2D& point);

	void Bounce(const BoundaryEdge& edge);

	inline const AARectangle GetBoundingRect() const {return mBBox;}
	inline void SetVelocity(const Vec2D& vel) {mVelocity = vel;}
	inline Vec2D GetVelocity() const {return mVelocity;}
	inline float GetRadius() const {return mBBox.GetWidth()/2.0f;}
	inline Vec2D GetPosition() const {return mBBox.GetCenterPoint();}

private:
	AARectangle mBBox;
	Vec2D mVelocity;

	static const float RADIUS;
};



#endif 
