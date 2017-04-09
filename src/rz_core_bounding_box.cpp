/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core_bounding_box.h"
#include "rz_core_bounding_sphere.h"

rz::bounding_box::bounding_box() :
	m_min(rz::vector3(0.0f, 0.0f, 0.0f)), m_max(rz::vector3(0.0f, 0.0f, 0.0f))
{
}

rz::bounding_box::bounding_box(rz::vector3 const &min, rz::vector3 const &max) :
	m_min(min), m_max(max)
{
	// todo crz: component-wise swap if min > max
}

bool rz::bounding_box::contains(rz::vector3 const &point) const
{
	return m_max.x() >= point.x() && m_min.x() <= point.x() && 
		m_max.y() >= point.y() && m_min.y() <= point.y() && 
		m_max.z() >= point.z() && m_min.z() <= point.z();
}

bool rz::bounding_box::intersects(bounding_box const &box) const
{
	return m_max.x() >= box.m_min.x() && m_min.x() <= box.m_max.x() && 
		m_max.y() >= box.m_min.y() && m_min.y() <= box.m_max.y() && 
		m_max.z() >= box.m_min.z() && m_min.z() <= box.m_max.z();
}

bool rz::bounding_box::intersects(rz::bounding_sphere const &sphere) const
{
	rz::vector3 vector = rz::vector3::clamp(sphere.centre, m_min, m_max); // todo crz: better name for this

	float d = sphere.centre.distance_squared(vector);
	return d <= sphere.radius * sphere.radius;
}

rz::vector3 rz::bounding_box::centre() const
{
	rz::vector3 v = (min() + max()) / 2.0f;

	return v;
}

rz::bounding_box rz::bounding_box::union_with(rz::bounding_box const &other) const
{
	// todo crz: test
	auto bb = rz::bounding_box(rz::vector3::min(other.min(), min()), rz::vector3::max(other.max(), max()));

	return bb;
}

rz::bounding_box rz::bounding_box::union_with(rz::vector3 const &v) const
{
	// todo crz: test
	auto bb = rz::bounding_box(rz::vector3::min(v, min()), rz::vector3::max(v, max()));

	return bb;
}
