/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core_bounding_box.h"

rz::bounding_box::bounding_box() :
	min(rz::vector3(0.0f, 0.0f, 0.0f)), max(rz::vector3(0.0f, 0.0f, 0.0f))
{
}

rz::bounding_box::bounding_box(rz::vector3 const &min, rz::vector3 const &max) :
	min(min), max(max)
{
}

bool rz::bounding_box::contains(rz::vector3 const &point)
{
	return max.x >= point.x && min.x <= point.x && 
		max.y >= point.y && min.y <= point.y && 
		max.z >= point.z && min.z <= point.z;
}

bool rz::bounding_box::intersects(bounding_box const &box)
{
	return max.x >= box.min.x && min.x <= box.max.x && 
		max.y >= box.min.y && min.y <= box.max.y && 
		max.z >= box.min.z && min.z <= box.max.z;
}

bool rz::bounding_box::intersects(rz::bounding_sphere const &sphere)
{
	auto vector = rz::vector3::clamp(sphere.centre, min, max);

	auto d = sphere.centre.distance_squared(vector);
	
	return d <= sphere.radius * sphere.radius;
}

