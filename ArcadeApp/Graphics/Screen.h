
#ifndef GRAPHICS_SCREEN_H_
#define GRAPHICS_SCREEN_H_

#include <stdint.h>
#include "ScreenBuffer.h"
#include "Color.h"
#include <functional>
#include <vector>
#include<string>

class Vec2D;
class Line2D;
class Triangle;
class AARectangle;
class Circle;
struct SDL_Window;
struct SDL_Surface;
class BMPImage;
class SpriteSheet;
struct Sprite;
class BitmapFont;

struct SDL_Renderer;
struct SDL_PixelFormat;
struct SDL_Texture;

class Screen
{
public:
	Screen();
	~Screen();

	SDL_Window* Init(uint32_t w, uint32_t h, uint32_t mag, bool fast = true);
	void SwapScreens();

	inline void SetClearColor(const Color& clearColor) {mClearColor = clearColor;}
	inline uint32_t Width() const {return mWidth;}
	inline uint32_t Height() const {return mHeight;}

	//Draw Methods go here

	void Draw(int x, int y, const Color& color);
	void Draw(const Vec2D& point, const Color& color);
	void Draw(const Line2D& line, const Color& color);
	void Draw(const Triangle& triangle, const Color& color, bool fill = false, const Color& fillColor = Color::White());
	void Draw(const AARectangle& rect, const Color& color, bool fill = false, const Color& fillColor = Color::White());
	void Draw(const Circle& circle, const Color& color, bool fill = false, const Color& fillColor = Color::White());

	void Draw(const BMPImage& image, const Sprite& sprite, const Vec2D& pos, const Color& overlayColor = Color::White());
	void Draw(const SpriteSheet& ss, const std::string& spriteName, const Vec2D& pos, const Color& overlayColor = Color::White());
	void Draw(const BitmapFont& font, const std::string& textLine, const Vec2D& pos, const Color& overlayColor = Color::White());

private:

	Screen(const Screen& screen);
	Screen& operator=(const Screen& screen);

	void ClearScreen();

	using FillPolyFunc = std::function<Color (uint32_t x, uint32_t y)>;

	void FillPoly(const std::vector<Vec2D>& points, FillPolyFunc func);
	uint32_t mWidth;
	uint32_t mHeight;

	Color mClearColor;
	ScreenBuffer mBackBuffer;

	SDL_Window* moptrWindow;
	SDL_Surface* mnoptrWindowSurface;

	SDL_Renderer* mRenderer;
	SDL_PixelFormat* mPixelFormat;
	SDL_Texture* mTexture;
	bool mFast;
};



#endif 
