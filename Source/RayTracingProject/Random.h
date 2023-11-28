#include <type_traits>
#include <stdlib.h>

inline void seedRandom(unsigned int seed)
{
	srand(seed);
}

inline float random01()
{
	return rand() / (float)RAND_MAX;
}

inline float random(float min, float max)
{
	if (min > max) std::swap(min, max);
	return min + (max - min) * random01();
}