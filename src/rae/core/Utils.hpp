#ifndef UTILS_H
#define UTILS_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <string>

namespace Rae
{

namespace Math
{
	const float TAU = 2.0f * (float)M_PI; // www.tauday.org
	const float PI = (float)M_PI;
	const float QUARTER_TAU = 0.5f * (float)M_PI;
	const float RAD_TO_DEG = 360.0f / TAU;
	const float DEG_TO_RAD = TAU / 360.0f;

	float toRadians(float set_degrees);
	float toDegrees(float set_radians);
}

namespace Utils
{
	
int randomInt(int low, int high);

// 2D versions of distance:
float getManhattanDistance( float rx, float ry );
float getDistance( float rx, float ry );

float weightedAverageClip( float val1, float val2, float set_position );
float weightedAverage( float val1, float val2, float set_position );
float backwardsWeightedAverage( float val1, float val2, float the_val );

std::string boolToString(bool set);

float randFloat(float a_min, float a_max);
bool almostEqual(float set_a, float set_b, float epsilon = 0.0001f);

}

} // end namespace Rae

#endif
