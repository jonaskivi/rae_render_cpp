
#include "core/ScreenInfo.hpp"

#include "core/Utils.hpp"

#ifdef version_catch
#include "core/catch.hpp"

SCENARIO("ScreenInfo unittest", "[Rae][ScreenInfo]")
{
	//2560 x 1600

	GIVEN( "A ScreenInfo of size 2560 x 1600" )
	{

		Rae::ScreenInfo screenInfo(0, 2560, 1600, 2560, 1600);

		REQUIRE(screenInfo.screenNumber() == 0);
		REQUIRE(screenInfo.screenWidthP() == 2560);
		REQUIRE(screenInfo.screenHeightP() == 1600);

		//2560 / 1600 = 1.6
		REQUIRE(screenInfo.screenAspect() == 1.6f);
		REQUIRE(screenInfo.screenHeight() == 1.0f);
		REQUIRE(screenInfo.screenWidth() == 1.6f);

		//REQUIRE(screenInfo.heightToPixels(1.0f) == 1600.0f);
		//REQUIRE(screenInfo.heightToPixels(0.5f) == 800.0f);
		//REQUIRE(screenInfo.heightToPixels(0.0f) == 0.0f);

		REQUIRE( Rae::Utils::almostEqual( screenInfo.heightToPixels(1.0f), 1600.0f ) );
		REQUIRE( Rae::Utils::almostEqual( screenInfo.heightToPixels(0.5f), 800.0f ) );
		REQUIRE( Rae::Utils::almostEqual( screenInfo.heightToPixels(0.0f), 0.0f ) );

		REQUIRE( Rae::Utils::almostEqual( screenInfo.pixelsToHeight(2560.0f), 1.6f ) );
		REQUIRE( Rae::Utils::almostEqual( screenInfo.pixelsToHeight(1600.0f), 1.0f ) );
		REQUIRE( Rae::Utils::almostEqual( screenInfo.pixelsToHeight(800.0f), 0.5f ) );
		REQUIRE( Rae::Utils::almostEqual( screenInfo.pixelsToHeight(0.0f), 0.0f ) );

		REQUIRE( Rae::Utils::almostEqual( screenInfo.percentToWidth(1.0f), 1.6f ) );
		REQUIRE( Rae::Utils::almostEqual( screenInfo.percentToWidth(0.5f), 0.8f ) );
		REQUIRE( Rae::Utils::almostEqual( screenInfo.percentToWidth(0.0f), 0.0f ) );

		WHEN( "the size is changed to 1280 x 800" )
		{
			screenInfo.setScreenSizeP(1280, 800);            

			THEN( "all is still ok." )
			{
				//1280 / 800 = 1.6
				REQUIRE(screenInfo.screenAspect() == 1.6f);
				REQUIRE(screenInfo.screenHeight() == 1.0f);
				REQUIRE(screenInfo.screenWidth() == 1.6f);

				REQUIRE( Rae::Utils::almostEqual( screenInfo.heightToPixels(1.0f), 800.0f ) );
				REQUIRE( Rae::Utils::almostEqual( screenInfo.heightToPixels(0.5f), 400.0f ) );
				REQUIRE( Rae::Utils::almostEqual( screenInfo.heightToPixels(0.0f), 0.0f ) );

				REQUIRE( Rae::Utils::almostEqual( screenInfo.pixelsToHeight(1280.0f), 1.6f ) );
				REQUIRE( Rae::Utils::almostEqual( screenInfo.pixelsToHeight(800.0f), 1.0f ) );
				REQUIRE( Rae::Utils::almostEqual( screenInfo.pixelsToHeight(400.0f), 0.5f ) );
				REQUIRE( Rae::Utils::almostEqual( screenInfo.pixelsToHeight(0.0f), 0.0f ) );

				REQUIRE( Rae::Utils::almostEqual( screenInfo.percentToWidth(1.0f), 1.6f ) );
				REQUIRE( Rae::Utils::almostEqual( screenInfo.percentToWidth(0.5f), 0.8f ) );
				REQUIRE( Rae::Utils::almostEqual( screenInfo.percentToWidth(0.0f), 0.0f ) );
			}
		}

		WHEN( "the size is changed to 4000 x 4000" )
		{
			screenInfo.setScreenSizeP(4000, 4000);            

			THEN( "all is still ok." )
			{
				//4000 / 4000 = 1.0
				REQUIRE(screenInfo.screenAspect() == 1.0f);
				REQUIRE(screenInfo.screenHeight() == 1.0f);
				REQUIRE(screenInfo.screenWidth() == 1.0f);

				REQUIRE( Rae::Utils::almostEqual( screenInfo.heightToPixels(1.0f), 4000.0f ) );
				REQUIRE( Rae::Utils::almostEqual( screenInfo.heightToPixels(0.5f), 2000.0f ) );
				REQUIRE( Rae::Utils::almostEqual( screenInfo.heightToPixels(0.0f), 0.0f ) );

				REQUIRE( Rae::Utils::almostEqual( screenInfo.pixelsToHeight(4000.0f), 1.0f ) );
				REQUIRE( Rae::Utils::almostEqual( screenInfo.pixelsToHeight(8000.0f), 2.0f ) );
				REQUIRE( Rae::Utils::almostEqual( screenInfo.pixelsToHeight(2000.0f), 0.5f ) );
				REQUIRE( Rae::Utils::almostEqual( screenInfo.pixelsToHeight(0.0f), 0.0f ) );

				REQUIRE( Rae::Utils::almostEqual( screenInfo.percentToWidth(1.0f), 1.0f ) );
				REQUIRE( Rae::Utils::almostEqual( screenInfo.percentToWidth(0.5f), 0.5f ) );
				REQUIRE( Rae::Utils::almostEqual( screenInfo.percentToWidth(0.0f), 0.0f ) );
			}
		}
	}
}
#endif

namespace Rae
{

ScreenInfo::ScreenInfo()
//ScreenInfo::ScreenInfo()
: m_screenNumber(-1),
m_screenWidthP(1280),
m_screenHeightP(800),
m_pixelsToHeight(0.00125f),
m_heightToPixels(800),
m_visibleAreaWidthP(-1),
m_visibleAreaHeightP(-1)
{
	calculateScreenAspect();
	calculateHalfScreens();

	m_curveSideSize = 0.3f;
	dpi(96.0f);

	cout<<"created ScreenInfo: ";
	printInfo();
}

ScreenInfo::ScreenInfo( int set_screenNumber, int set_screenWidthP, int set_screenHeightP, int set_visibleAreaWidthP, int set_visibleAreaHeightP)
{
	screenNumber(set_screenNumber);
	//screenHeightP(set_screenHeightP);
	//screenWidthP(set_screenWidthP);
	m_screenWidthP = set_screenWidthP;
	
	// updateScreenHeightStuff:
	m_pixelsToHeight = 1.0f / (float)set_screenHeightP;
	m_heightToPixels = (float)set_screenHeightP;
	m_screenHeightP = set_screenHeightP;

	m_visibleAreaWidthP = set_visibleAreaWidthP;
	m_visibleAreaHeightP = set_visibleAreaHeightP;

	calculateScreenAspect();
	calculateHalfScreens();

	m_curveSideSize = 0.3f;
	dpi(96.0);

	cout<<"created ScreenInfo: ";
	printInfo();
}

void ScreenInfo::setScreenSizeP(int set_widthP, int set_heightP)
{
	m_screenWidthP = set_widthP;

	// updateScreenHeightStuff:
	m_pixelsToHeight = 1.0f / (float)set_heightP;
	m_heightToPixels = (float)set_heightP;
	m_screenHeightP = set_heightP;

	calculateScreenAspect();
	calculateHalfScreens();	
}

void ScreenInfo::screenWidthP(int set)
{
	m_screenWidthP = set;
	calculateScreenAspect();
	calculateHalfScreens();
}

void ScreenInfo::screenHeightP(int set)
{
	#ifdef DebugRae
		RaeLog << "ScreenInfo::screenHeightP() set to:" << set << "\n";
	#endif
	
	// updateScreenHeightStuff:
	m_pixelsToHeight = 1.0f / (float)set;
	m_heightToPixels = (float)set;
	m_screenHeightP = set;

	calculateScreenAspect();
	calculateHalfScreens();
}

} // end namespace Rae
