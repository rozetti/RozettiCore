/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core_bounding_sphere.h"
#include "rz_core_bounding_box.h"

rz::bounding_sphere::bounding_sphere() :
	radius(0.0f),
	centre(rz::vector3(0.0f, 0.0f, 0.0f))
{
}

rz::bounding_sphere::bounding_sphere(rz::vector3 const &center, float radius) :
	centre(center),
	radius(radius)
{
}

bool rz::bounding_sphere::intersects(rz::bounding_sphere const &sphere)
{
	auto distance_squared = centre.distance_squared(sphere.centre);

    return (radius * radius + 2.0f * radius * sphere.radius + sphere.radius * sphere.radius) > distance_squared;
}

rz::bounding_sphere rz::bounding_sphere::from_bounding_box(rz::bounding_box const &box)
{
	// notest crz
	auto extent_max = box.max() - box.centre();
	auto extent_min = box.centre() - box.min();
	auto extent = rz::vector3::max(extent_max, extent_min);

	rz::bounding_sphere sphere(box.centre(), extent.length());

	return sphere;
}
