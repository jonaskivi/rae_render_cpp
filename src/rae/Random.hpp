#ifndef RAE_RANDOM_HPP
#define RAE_RANDOM_HPP

#include <random>
#include <algorithm>

namespace Rae
{

typedef std::mt19937 RandomGeneratorEngine;
extern RandomGeneratorEngine g_randomEngine;

float getRandom( float from, float to );
float getRandomDistribution(float mean, float deviation);
int getRandomInt( int from, int to );
bool isEqual(float a, float b, float epsilon); //JONDE Move this to Utils.hpp

} // end namespace Rae

#endif