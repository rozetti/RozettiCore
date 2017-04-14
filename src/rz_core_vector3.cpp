/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core_macros.h"

#include "rz_core_vector3.h"
#include "rz_core_matrix.h"
#include <cmath>
#include <algorithm>

rz::vector4::vector4() : m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(0.0f) { }
rz::vector4::vector4(rz::vector4 const &vec) : m_x(vec.x()), m_y(vec.y()), m_z(vec.z()), m_w(vec.w()) { }
rz::vector4::vector4(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w) { }

rz::vector3::vector3() : m_x(static_cast<element_type>(0)), m_y(static_cast<element_type>(0)), m_z(static_cast<element_type>(0)), m_w(static_cast<element_type>(1)) { }
rz::vector3::vector3(rz::vector3 const &vec) : m_x(vec.x()), m_y(vec.y()), m_z(vec.z()), m_w(static_cast<element_type>(1)) { }
rz::vector3::vector3(rz::vector3::tuple_type const &tuple) : m_x(std::get<0>(tuple)), m_y(std::get<1>(tuple)), m_z(std::get<2>(tuple)), m_w(1.0f) { }
rz::vector3::vector3(element_type x, element_type y, element_type z) : m_x(x), m_y(y), m_z(z), m_w(static_cast<element_type>(1)) { }

void rz::vector3::set(rz::vector3 const &vec)
{
	set(vec.x(), vec.y(), vec.z());
}

void rz::vector3::set(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = static_cast<element_type>(1);
}

bool rz::vector3::equals(rz::vector3 const &other) const
{
	// todo crz: possibly use a policy to control use of eplison margin
	return FLT_EQUALS(m_x, other.m_x) && FLT_EQUALS(m_y, other.m_y) && FLT_EQUALS(m_z, other.m_z);
}

// todo crz: de-float all of this

rz::vector3 &rz::vector3::add(float x, float y, float z)
{
	m_x += x;
	m_y += y;
	m_z += z;

	return *this;
}

rz::vector3 &rz::vector3::subtract(float x, float y, float z)
{
	m_x -= x;
	m_y -= y;
	m_z -= z;

	return *this;
}

rz::vector3 &rz::vector3::multiply(float x, float y, float z)
{
	m_x *= x;
	m_y *= y;
	m_z *= z;

	return *this;
}

rz::vector3 &rz::vector3::divide(float x, float y, float z)
{
	m_x /= x;
	m_y /= y;
	m_z /= z;

	return *this;
}

float rz::vector3::length_squared() const
{
	return (m_x * m_x + m_y * m_y + m_z * m_z);
}

float rz::vector3::distance_squared(rz::vector3 const &other) const
{
	auto temp_x = m_x - other.m_x;
	auto temp_y = m_y - other.m_y;
	auto temp_z = m_z - other.m_z;

	return (temp_x * temp_x + temp_y * temp_y + temp_z * temp_z);
}

rz::vector3 &rz::vector3::clamp(rz::vector3 const &lower, rz::vector3 const &upper)
{
	m_x = rz::min(m_x, upper.m_x);
	m_y = rz::min(m_y, upper.m_y);
	m_z = rz::min(m_z, upper.m_z);

	m_x = rz::max(m_x, lower.m_x);
	m_y = rz::max(m_y, lower.m_y);
	m_z = rz::max(m_z, lower.m_z);

	return *this;
}

rz::vector3 &rz::vector3::normalise()
{
	auto ls = length_squared();
	if (ls > rz::ONE_FLT_EPSILON)
	{
		auto factor = 1.0f / (float)sqrt(ls);

		m_x *= factor;
		m_y *= factor;
		m_z *= factor;
	}

	return *this;
}

rz::vector3 &rz::vector3::negate()
{
	m_x = -m_x;
	m_y = -m_y;
	m_z = -m_z;

	return *this;
}

float rz::vector3::dot(rz::vector3 const &other) const
{
	auto v = *this * other;
	return v.sum();
}

rz::vector3 &rz::vector3::cross(rz::vector3 const &other)
{
	auto temp_x = m_y * other.m_z - m_z * other.m_y;
	auto temp_y = m_z * other.m_x - m_x * other.m_z;
	auto temp_z = m_x * other.m_y - m_y * other.m_x;
	
	m_x = temp_x;
	m_y = temp_y;
	m_z = temp_z;

	return *this;
}

rz::vector3 &rz::vector3::lerp(rz::vector3 const &other, float f)
{
	m_x += f * (other.m_x - m_x);
	m_y += f * (other.m_y - m_y);
	m_z += f * (other.m_z - m_z);

	return *this;
}

rz::vector3 const operator+(float f, rz::vector3 const &v) { return rz::vector3(v) + f; }
rz::vector3 const operator-(float f, rz::vector3 const &v) { return rz::vector3(f - v.x(), f - v.y(), f - v.z()); }
rz::vector3 const operator*(float f, rz::vector3 const &v) { return rz::vector3(v) * f; }
rz::vector3 const operator/(float f, rz::vector3 const &v) { return rz::vector3(f / v.x(), f / v.y(), f / v.z()); }

rz::vector3 rz::transform(rz::vector3 const &vec, rz::matrix const &transformation)
{
	rz::vector3 dest;

	auto v1 = vec.x() * transformation.F[0] + vec.y() * transformation.F[4] + vec.z() * transformation.F[8] + transformation.F[12];
	auto v2 = vec.x() * transformation.F[1] + vec.y() * transformation.F[5] + vec.z() * transformation.F[9] + transformation.F[13];
	auto v3 = vec.x() * transformation.F[2] + vec.y() * transformation.F[6] + vec.z() * transformation.F[10] + transformation.F[14];

	return dest;
}
