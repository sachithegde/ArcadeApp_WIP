#ifndef GRAPHICS_BITMAPFONT_H_
#define GRAPHICS_BITMAPFONT_H_

#include "SpriteSheet.h"
#include "../Utils/Utils.h" 
#include <stdint.h>

class Vec2D;
class AARectangle;

enum BitmapFontXAlignment
{
	BFXA_LEFT = 0,
	BFXA_CENTER,
	BFXA_RIGHT
};

enum BitmapFontYAlignment
{
	BFYA_TOP = 0,
	BFYA_CENTER,
	BFYA_BOTTOM
};

class BitmapFont
{
public:

	BitmapFont(){}
	bool Load(const std::string& name);
	Size GetSizeOf(const std::string & str) const;
	Vec2D GetDrawPosition(const std::string& str, const AARectangle& box, BitmapFontXAlignment xAlign = BFXA_LEFT, BitmapFontYAlignment yAlign = BFYA_TOP) const;

	inline const SpriteSheet& GetSpriteSheet() const {return mFontSheet;}
	inline const uint32_t GetFontSpacingBetweenLetters() const {return 2;}
	inline const uint32_t GetFontSpacingBetweenWords() const {return 5;}

private:
	SpriteSheet mFontSheet;
};

#endif 
