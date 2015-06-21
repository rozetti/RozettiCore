/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core_plane.h"
#include "rz_core_macros.h"

rz::plane::plane(rz::vector3 const &normal, float distance) :
	normal(normal),
	distance_from_origin(distance)
{
}

rz::plane::plane(float x, float y, float z, float d1) :
	normal(rz::vector3(x, y, z)),
	distance_from_origin(d1)
{
}

void rz::plane::normalise()
{
	auto t = 1.0f / sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
	normal.x *= t;
	normal.y *= t;
	normal.z *= t;
	distance_from_origin *= t;
}

rz::plane::preposition rz::plane::classify_point(rz::vector3 const &v) const
{
	auto f = v.x * normal.x + v.y * normal.y + v.z * normal.z + distance_from_origin;
	
	if (f > rz::ONE_FLT_EPSILON)
	{
		return preposition::front;
	}
	
	if(f < -rz::ONE_FLT_EPSILON)
	{
		return preposition::back;
	}

	return preposition::coincident;
}
