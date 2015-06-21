/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core.h"

// crz: this looks horrible, I'm not sure where I got this from (possily Noodles so be afraid..)

// crz: for now a non-intersection returns -1, hopefully I will make negative numbers mean the 
// distance at the closest point

rz::ray::ray(rz::vector3 const &pos, rz::vector3 const &dir) :
	position(pos),
	direction(dir)
{
}

float rz::ray::intersection_with(bounding_box const &box) const
{
	auto lower = 0.0f;
	auto upper = FLT_MAX;
	
	if (std::abs(direction.x) <= ONE_FLT_EPSILON)
	{
		if (position.x < box.min.x || position.x > box.max.x)
		{
			return -1.0f;
		}
	}
	else
	{
		auto a = (box.min.x - position.x) / direction.x;
		auto b = (box.max.x - position.x) / direction.x;
		if (a > b) std::swap(a, b);

		lower = rz::max(a, lower);
		upper = rz::min(b, upper);
		if (lower > upper)
		{
			return -1.0f;
		}
	}

	if (std::abs(direction.y) <= ONE_FLT_EPSILON)
	{
		if (position.y < box.min.y || position.y > box.max.y)
		{
			return -1.0f;
		}
	}
	else
	{
		auto a = (box.min.y - position.y) / direction.y;
		auto b = (box.max.y - position.y) / direction.y;
		if (a > b) std::swap(a, b);

		lower = rz::max(a, lower);
		upper = rz::min(b, upper);
		if (lower > upper)
		{
			return -1.0f;
		}
	}

	if (std::abs(direction.z) <= ONE_FLT_EPSILON)
	{
		if (position.z < box.min.z || position.z > box.max.z)
		{
			return -1.0f;
		}
	}
	else
	{
		auto a = (box.min.z - position.z) / direction.z;
		auto b = (box.max.z - position.z) / direction.z;
		if (a > b) std::swap(a, b);

		lower = rz::max(a, lower);
		upper = rz::min(b, upper);
		if (lower > upper)
		{
			return -1.0f;
		}
	}

	return lower;
}

float rz::ray::intersection_with(rz::bounding_sphere const &sphere) const
{
	auto dx = sphere.centre.x - position.x;
	auto dy = sphere.centre.y - position.y;
	auto dz = sphere.centre.z - position.z;

	auto distance_squared = dx * dx + dy * dy + dz * dz;
	auto radius_squared = sphere.radius * sphere.radius;

	if (distance_squared <= radius_squared) // crz: inside sphere
	{
		return 0.0f;
	}

	auto d_dot_direction = dx * direction.x + dy * direction.y + dz * direction.z;
	if (d_dot_direction < 0.0f) // crz: pointing away from sphere
	{
		return -1.0f;
	}

	auto perigee_squared = distance_squared - d_dot_direction * d_dot_direction;
	if (perigee_squared > radius_squared) // crz: does not intersect
	{
		return -1.0f;
	}
	
	return d_dot_direction - std::sqrt(radius_squared - perigee_squared);
}

float rz::ray::intersection_with(rz::plane const &plane) const
{
	// crz: I have no idea what I am doing here, and there are no tests, so be careful...

	auto la(position);
	auto lb(position + direction);

	auto p0(plane.distance_from_origin * plane.normal);
	auto p1(p0 + rz::matrix_factory::create_rotation_around_x(rz::PI_OVER_TWO_f) * p0);
	auto p2(p0 + rz::matrix_factory::create_rotation_around_y(rz::PI_OVER_TWO_f) * p0);

	rz::matrix m;

	m.M11(la.x - lb.x);
	m.M21(p1.x - p0.x);
	m.M31(p2.x - p0.x);
	m.M12(la.y - lb.y);
	m.M22(p1.y - p0.y);
	m.M32(p2.y - p0.y);
	m.M13(la.z - lb.z);
	m.M23(p1.z - p0.z);
	m.M33(p2.z - p0.z);
	
	m.invert();
	
	auto v = m * (la - p0);
	auto intersection = la + v.x * (lb - la);
	
	return position.distance(intersection);
}
