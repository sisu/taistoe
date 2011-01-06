#ifndef UNIT_HPP
#define UNIT_HPP

#include "Vector.hpp"
struct Unit {
	Vec3 p; // position
	Vec3 v; // velocity
	Vec3 m; // intended movement

	int type;
	int weapon;
};

#endif
