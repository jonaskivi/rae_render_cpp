#pragma once

#include <vector>

#include "core/ScreenInfo.hpp"

namespace Rae
{

class ScreenSystem
{
public:

	ScreenSystem()
	{
	}

	void updateScreenInfo();
	int numberOfScreens();

	int screenWidthP(int set_screen = 0);
	int screenHeightP(int set_screen = 0);
	// Screen width and height in height coordinates.
	float screenWidth(int set_screen = 0);
	// screenHeight in height coordinates should always be 1.0f.
	float screenHeight(int set_screen = 0);
	
	float screenHalfWidthP(int set_screen = 0);
	float screenHalfHeightP(int set_screen = 0);
	float screenHalfWidth(int set_screen = 0);
	float screenHalfHeight(int set_screen = 0);

	float screenAspect(int set_screen = 0);
	
	// to convert Height coordinates to pixels:
	// inHCoord * pixelsToHeight()
	// to convert pixels to Height coordinates:
	// inPixels * heightToPixels()
	// or inPixels * screenHeightP()
		
	// The height of one pixel in Height coordinates.
	// to convert pixels to Height coordinates:
	// inPixels * pixel()
	// to convert Height coordinates to pixels (slowly) (it's better to use heightToPixels *):
	// inHCoord / pixel()
	// float pixel() { return 1.0f/m_screenHeightP; }
	
	float pixel(int set_screen = 0);
	float pixelsToHeight(int set_screen = 0);
	
	float heightToPixels(int set_screen = 0);
	
	float pixelsToHeight(float in_pixels, int set_screen = 0);
	float heightToPixels(float in_height, int set_screen = 0);
	
	float percentToWidth(float in_percent, int set_screen = 0);

	// This returns and accepts Height coordinates
	float roundToPixels( float set, int set_screen = 0 );
	
	// The default dpi (dots per inch) is 96.0f.
	// The user should change it according to screen size.
	// A smaller dpi will result in smaller widgets and smaller text.
	void dpi(float set, int set_screen = 0);
	float dpi(int set_screen = 0);
	float dpiMul(float set, int set_screen = 0);
	float dpiMul(int set_screen = 0);
	void dpiToDefault(int set_screen = 0);
	float curveSideSize(int set_screen = 0);

protected:
	std::vector<ScreenInfo*> screens;
};
	
}
