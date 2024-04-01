
#include "Button.h"
#include "../Scenes/Scene.h"
#include"../Graphics/Screen.h"
#include <iostream>

Button::Button(const BitmapFont& bitmapFont, const Color& textColor, const Color& highlightColor):
	mBitmapFont(bitmapFont),mTitle(""), mTextColor(textColor), mHighlightColor(highlightColor), mAction(nullptr), mHighlighted(false)
{

}

void Button::Init(Vec2D topLeft, unsigned int width, unsigned height)
{
	mBBox = AARectangle(topLeft, width, height);
}

void Button::Draw(Screen& theScreen)
{
	theScreen.Draw(mBitmapFont, mTitle, mBitmapFont.GetDrawPosition(mTitle, mBBox, BFXA_CENTER, BFYA_CENTER), mTextColor);

	if(mHighlighted)
	{
		theScreen.Draw(mBBox, mHighlightColor);
	}
}

void Button::ExecuteAction()
{
	mAction();
}


