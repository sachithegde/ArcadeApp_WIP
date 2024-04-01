#ifndef GAMES_BREAKOUT_PADDLE_H_
#define GAMES_BREAKOUT_PADDLE_H_


#include "Excluder.h"
#include <stdint.h>

class Screen;
class Ball;

enum PaddleDirection
{
	LEFT = 1 << 0,
	RIGHT = 1 << 1
};

class Paddle: public Excluder
{
public:

	static const uint32_t PADDLE_WIDTH = 50;
	static const uint32_t PADDLE_HEIGHT = 10;

	void Init(const AARectangle& rect, const AARectangle & boundary);

	void Update(uint32_t dt, Ball& ball);

	void Draw(Screen& screen);

	bool Bounce(Ball& ball);

	inline bool IsMovingLeft() const {return mDirection == PaddleDirection::LEFT;}
	inline bool IsMovingRight() const {return mDirection == PaddleDirection::RIGHT;}

	
	inline void SetMovementDirection(PaddleDirection dir) {mDirection |= dir;}
	inline void UnsetMovementDirection(PaddleDirection dir) {mDirection &= ~dir;}
	inline void StopMovement() {mDirection = 0;}

private:
	uint32_t mDirection; //direction we're moving
	AARectangle mBoundary; //boundary that the paddle is confined to
	const float VELOCITY = 100.0f; //pixels/sec
	const float CORNER_BOUNCE_AMT = 0.2f;
};



#endif 
