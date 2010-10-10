#ifndef UTIL_HPP
#define UTIL_HPP

#include <random>
#include <cmath>

extern std::mt19937 rng;

inline double rndf()
{
	return fabs(rng())/rng.max();
}

#endif
