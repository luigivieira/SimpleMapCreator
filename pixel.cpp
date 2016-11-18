#include "pixel.h"

//-----------------------------------------
Pixel::Pixel()
{
	red = 0;
	green = 0;
	blue = 0;
}

//-----------------------------------------
Pixel::Pixel(uchar red, uchar green, uchar blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

//-----------------------------------------
Pixel::Pixel(const Pixel &other)
{
	red = other.red;
	green = other.green;
	blue = other.blue;
}