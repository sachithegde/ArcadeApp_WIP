
#ifndef GRAPHICS_BMPIMAGE_H_
#define GRAPHICS_BMPIMAGE_H_

#include "Color.h"
#include <vector>
#include <string>
#include <stdint.h>


class BMPImage
{
public:

	BMPImage();
	bool Load(const std::string& path);

	inline const std::vector<Color>& GetPixels() const {return mPixels;}
	inline uint32_t GetWidth() const {return mWidth;}
	inline uint32_t GetHeight() const {return mHeight;}

private:

	std::vector<Color> mPixels;
	uint32_t mWidth;
	uint32_t mHeight;
};



#endif
