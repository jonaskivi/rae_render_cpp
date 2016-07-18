#ifndef _ScreenInfo_hpp_
#define _ScreenInfo_hpp_

#include <iostream>
	using namespace std;


namespace Rae
{

class ScreenInfo
{
public:

	ScreenInfo();
	ScreenInfo( int set_screenNumber, int set_screenWidthP, int set_screenHeightP, int set_visibleAreaWidthP = -1, int set_visibleAreaHeightP = -1 );
	~ScreenInfo(){}
	
	public: void printInfo()
	{
		cout << "Screen number: " << screenNumber()
			<< " width: " << screenWidthP()
			<< " height: " << screenHeightP()
			<< " aspect ratio: " << screenAspect()
			<< "\n";
	}

	// -1 is UNDEFINED, 0 is the first screen
	public: int screenNumber() { return m_screenNumber; }
	public: void screenNumber(int set) { m_screenNumber = set; }
	protected: int m_screenNumber;

	public: void setScreenSizeP(int set_widthP, int set_heightP);

	public: int screenWidthP() { return m_screenWidthP; }
	public: void screenWidthP(int set);
	protected: int m_screenWidthP;// = 1280;//1066;
	
	public: int screenHeightP() { return m_screenHeightP; }
	public: void screenHeightP(int set);
	protected: int m_screenHeightP;// = 800;
	
	// Screen width and height in height coordinates.
	public: float screenWidth() { return 1.0f*screenAspect(); }
	// screenHeight in height coordinates should always be 1.0f.
	public: float screenHeight() { return 1.0f; }

	// helpers for half screenWidth and height:

	public: float screenHalfWidth() { return 0.5f*screenAspect(); }
	// screenHalfHeight in height coordinates should always be 0.5f.
	public: float screenHalfHeight() { return 0.5f; }

	public: void calculateHalfScreens()
	{
		screenHalfWidthP( float(screenWidthP() / 2) );
		screenHalfHeightP( float(screenHeightP() / 2) );
	}
	public: float screenHalfWidthP() { return m_screenHalfWidthP; }
	public: void screenHalfWidthP(float set) { m_screenHalfWidthP = set; }
	protected: float m_screenHalfWidthP;
	public: float screenHalfHeightP() { return m_screenHalfHeightP; }
	public: void screenHalfHeightP(float set) { m_screenHalfHeightP = set; }
	protected: float m_screenHalfHeightP;

	/*public: float screenAspect()
	{
		return (float)(m_screenWidthP)/(float)(m_screenHeightP);
	}*/
	public: void calculateScreenAspect()
	{
		screenAspect( (float)(m_screenWidthP)/(float)(m_screenHeightP) );
	}
	public: float screenAspect() { return m_screenAspect; }
	public: void screenAspect(float set) { m_screenAspect = set; }
	protected: float m_screenAspect;


	
	// On Mac OS X these are the visibleFrame, which is the size of the screen that is not
	// occupied by the top main menu, the dock 
	// (or if it is hidden the activation area of the dock) etc.
	// So, if you would create a window with these sizes, it would not overlap the dock or menu.
	
	//With these, we'll use -1 as UNDEFINED
	public: int visibleAreaWidthP() { return m_visibleAreaWidthP; }
	public: void visibleAreaWidthP(int set) { m_visibleAreaWidthP = set; }
	protected: int m_visibleAreaWidthP;
	
	public: int visibleAreaHeightP() { return m_visibleAreaHeightP; }
	public: void visibleAreaHeightP(int set) { m_visibleAreaHeightP = set; }
	protected: int m_visibleAreaHeightP;
	
	//
	
	public: float pixel() { return m_pixelsToHeight; }
	public: float pixelsToHeight() { return m_pixelsToHeight; }
	protected: float m_pixelsToHeight;// = 0.00125f;//1.0f / screenHeightP;
	
	public: float heightToPixels() { return m_heightToPixels; }
	protected: float m_heightToPixels;//800, the same as m_screenHeightP...
	
	// Ok. We should make these methods as well:
	public: float pixelsToHeight(float in_pixels) { return in_pixels * m_pixelsToHeight; }
	public: float heightToPixels(float in_height) { return in_height * m_heightToPixels; }

	// Convert a percentage (e.g. -0.5 - 0.5f which is the whole screen) to "height units" (in the width direction)
	// e.g. 0.5 is 50% and it will be half of 1.78 when the aspect ratio is 1:1.78 (16:9)
	// so the result will be 0.89, which is half of the screen width in "height units".
	public: float percentToWidth(float in_percent) { return in_percent * screenAspect(); }

	//This returns and accepts Height coordinates
	float roundToPixels( float set )
	{
		float temppixel = pixel();
		return ((float)((int)( set / temppixel ))) * temppixel;
	}

	// The default dpi (dots per inch) is 96.0f.
	// The user should change it according to screen size.
	// A smaller dpi will result in smaller widgets and
	// smaller text.
	void dpi(float set)
	{
		// The range for the Dpi is currently 30-300.
		// You'll get distortions in both ends. So, the
		// real usable range is something about 60-180.
		if( set < 30.0f ) set = 30.0f;
		else if( set > 300.0f ) set = 300.0f;

		m_dpiMul = set/96.0f;

		// Adjust curveSideSize to fall on the desired range.
		// Dpi over about 190.0 will propably not look so good anymore.
		// even with these adjustments. Would have to change the texture
		// size to 128 in that case. TODO.
		m_curveSideSize = m_dpiMul * 0.3f;
		if( m_curveSideSize < 0.25f ) m_curveSideSize = 0.25f;
		else if( m_curveSideSize > 0.48f ) m_curveSideSize = 0.48f;

		m_dpi = set;
		//m_dpiForSaving = set; // So that it will be saved too.
	}
	public: float dpi() { return m_dpi; }
	protected: float m_dpi;

	public: float dpiMul(float set) { return m_dpiMul * set; }
	public: float dpiMul() { return m_dpiMul; }
	protected: float m_dpiMul;

	public: void dpiToDefault() { dpi(96.0f); }

	// A setting for RoundedRectangles:
	// e.g. in HORIZONTAL this is
	// the width of leftRect and rightRect.
	// This must be correct for the given dpi
	// because otherwise the rounded curve will
	// get clipped too soon.
	// Setting the dpi will change this too.
	// And it will get adjusted to be in the range 0.25f - 0.48f.
	public: float curveSideSize() { return m_curveSideSize; }
	protected: float m_curveSideSize;// = 0.3f;
};

}//namespace rae

#endif



