#include <random>
#include <algorithm>

#include "Random.hpp"

namespace Rae
{

RandomGeneratorEngine g_randomEngine;

float getRandom( float from, float to )
{
	static std::uniform_real_distribution<float> uniform_dist;
	return uniform_dist( g_randomEngine, std::uniform_real_distribution<float>::param_type(from, to) );
}

float getRandomDistribution(float mean, float deviation)
{
	static std::normal_distribution<float> normal_dist(mean, deviation);
	return normal_dist(g_randomEngine, std::normal_distribution<float>::param_type(mean, deviation));
}

int getRandomInt( int from, int to )
{
    static std::uniform_int_distribution<int> uniform_dist;
    return uniform_dist( g_randomEngine, std::uniform_int_distribution<int>::param_type(from, to) );
}

// TODO move to Utils.hpp
bool isEqual(float a, float b, float epsilon)
{
	return (fabs(a - b) <= epsilon); 
}

} // end namespace Rae
