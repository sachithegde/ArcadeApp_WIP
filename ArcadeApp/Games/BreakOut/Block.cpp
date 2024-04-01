#include "Block.h"
#include "../../Graphics/Screen.h"
#include "Ball.h"
#include "BoundaryEdge.h"

Block::Block():	mOutlineColor(Color::White()), mFillColor(Color::White()), mHp(1)
{

}

void Block::Init(const AARectangle& rect, int hp, const Color& outlineColor, const Color& fillColor)
{
	Excluder::Init(rect);
	mHp = hp;
	mOutlineColor = outlineColor;
	mFillColor = fillColor;
}

void Block::Draw(Screen& screen)
{
	screen.Draw(GetAARectangle(), mOutlineColor, true, mFillColor);
}

void Block::Bounce(Ball& ball, const BoundaryEdge& edge)
{
	ball.Bounce(edge);
}

void Block::ReduceHP()
{
	if(mHp > 0)
	{
		--mHp;
	}
}


