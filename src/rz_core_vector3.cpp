/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core_macros.h"

#include "rz_core_vector3.h"
#include "rz_core_matrix.h"
#include <cmath>
#include <algorithm>

rz::vector3::vector3() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) { }
rz::vector3::vector3(rz::vector3 const &vec) : x(vec.x), y(vec.y), z(vec.z), w(1.0f) { }
rz::vector3::vector3(float x, float y, float z) : x(x), y(y), z(z), w(1.0f) { }

void rz::vector3::set(rz::vector3 const &vec)
{
	set(vec.x, vec.y, vec.z);
}

void rz::vector3::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	w = 1.0f;
}

bool rz::vector3::equals(rz::vector3 const &other) const
{
	// todo crz: possibly use a policy to control use of eplison margin
	return FLT_EQUALS(x, other.x) && FLT_EQUALS(y, other.y) && FLT_EQUALS(z, other.z);
}

rz::vector3 &rz::vector3::add(float x, float y, float z)
{
	this->x += x;
	this->y += y;
	this->z += z;

	return *this;
}

rz::vector3 &rz::vector3::subtract(float x, float y, float z)
{
	this->x -= x;
	this->y -= y;
	this->z -= z;

	return *this;
}

rz::vector3 &rz::vector3::multiply(float x, float y, float z)
{
	this->x *= x;
	this->y *= y;
	this->z *= z;

	return *this;
}

rz::vector3 &rz::vector3::divide(float x, float y, float z)
{
	this->x /= x;
	this->y /= y;
	this->z /= z;

	return *this;
}

float rz::vector3::length_squared() const
{
	return (x * x + y * y + z * z);
}

float rz::vector3::distance_squared(rz::vector3 const &other) const
{
	auto temp_x = x - other.x;
	auto temp_y = y - other.y;
	auto temp_z = z - other.z;

	return (temp_x * temp_x + temp_y * temp_y + temp_z * temp_z);
}

rz::vector3 &rz::vector3::clamp(rz::vector3 const &lower, rz::vector3 const &upper)
{
	x = std::min(x, upper.x);
	y = std::min(y, upper.y);
	z = std::min(z, upper.z);

	x = std::max(x, lower.x);
	y = std::max(y, lower.y);
	z = std::max(z, lower.z);

	return *this;
}

rz::vector3 &rz::vector3::normalise()
{
	auto ls = length_squared();
	if (ls > rz::ONE_FLT_EPSILON)
	{
		auto factor = 1.0f / (float)sqrt(ls);

		x *= factor;
		y *= factor;
		z *= factor;
	}

	return *this;
}

rz::vector3 &rz::vector3::negate()
{
	x = -x;
	y = -y;
	z = -z;

	return *this;
}

float rz::vector3::dot(rz::vector3 const &other) const
{
	return (x * other.x + y * other.y + z * other.z);
}

rz::vector3 &rz::vector3::cross(rz::vector3 const &other)
{
	auto temp_x = y * other.z - z * other.y;
	auto temp_y = z * other.x - x * other.z;
	auto temp_z = x * other.y - y * other.x;
	
	x = temp_x;
	y = temp_y;
	z = temp_z;

	return *this;
}

rz::vector3 &rz::vector3::lerp(rz::vector3 const &other, float f)
{
	x += f * (other.x - x);
	y += f * (other.y - y);
	z += f * (other.z - z);

	return *this;
}

rz::vector3 const operator+(float f, rz::vector3 const &v) { return rz::vector3(v) + f; }
rz::vector3 const operator-(float f, rz::vector3 const &v) { return rz::vector3(f - v.x, f - v.y, f - v.z); }
rz::vector3 const operator*(float f, rz::vector3 const &v) { return rz::vector3(v) * f; }
rz::vector3 const operator/(float f, rz::vector3 const &v) { return rz::vector3(f / v.x, f / v.y, f / v.z); }
