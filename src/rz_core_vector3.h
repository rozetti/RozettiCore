/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

// todo crz: template this

#include <cmath>

namespace rz
{
	class matrix;

	class vector3
	{
	public:
		float x;
		float y;	
		float z;
		float w;

		rz::vector3();
		rz::vector3(rz::vector3 const &vec);
		rz::vector3(float x, float y, float z);

		void set(rz::vector3 const &from);
		void set(float x, float y, float z);

		rz::vector3 &operator=(rz::vector3 const &other) { set(other); return *this; }

		bool equals(rz::vector3 const &value1) const;
		bool operator==(rz::vector3 const &other) const { return equals(other); }
		bool operator!=(rz::vector3 const &other) const { return !equals(other); }

		rz::vector3 &add(float x, float y, float z);
		rz::vector3 &add(rz::vector3 const &other) { return add(other.x, other.y, other.z); }
		rz::vector3 &add(float f) { return add(f, f, f); }
		rz::vector3 const operator+(float f) const { return rz::vector3(*this).add(f); }
		rz::vector3 const operator+(rz::vector3 const &other) const { return rz::vector3(*this).add(other); }
		void operator+=(float f) { (*this).add(f); }
		
		rz::vector3 &subtract(float x, float y, float z);
		rz::vector3 &subtract(rz::vector3 const &other) { return subtract(other.x, other.y, other.z); }
		rz::vector3 &subtract(float f) { return subtract(f, f, f); }
		rz::vector3 const operator-(float f) const { return rz::vector3(*this).subtract(f); }
		rz::vector3 const operator-(rz::vector3 const &other) const { return rz::vector3(*this).subtract(other); }
		void operator-=(float f) { (*this).subtract(f); }
		
		rz::vector3 &multiply(float x, float y, float z);
		rz::vector3 &multiply(rz::vector3 const &v) { return multiply(v.x, v.y, v.z); }
		rz::vector3 &multiply(float f) { return multiply(f, f, f); }
		rz::vector3 const operator*(float f) const { return rz::vector3(*this).multiply(f); }
		rz::vector3 const operator*(rz::vector3 const &v) const { return rz::vector3(*this).multiply(v); }

		rz::vector3 &divide(float x, float y, float z);
		rz::vector3 &divide(rz::vector3 const &v) { return divide(v.x, v.y, v.z); }
		rz::vector3 &divide(float f) { return divide(f, f, f); }
		rz::vector3 const operator/(float f) const { return rz::vector3(*this).divide(f); }
		rz::vector3 const operator/(rz::vector3 const &v) const { return rz::vector3(*this).divide(v); }

		rz::vector3 &clamp(rz::vector3 const &lower_bound, rz::vector3 const &upper_bound);
		rz::vector3 &normalise();
		rz::vector3 &negate();

		float length_squared() const;
		float length() const { return (float)std::sqrt(length_squared()); }
		float distance_squared(rz::vector3 const &other) const;
		float distance(rz::vector3 const &other) const { return (float)std::sqrt(distance_squared(other)); }

		rz::vector3 &cross(rz::vector3 const &other);
		float dot(rz::vector3 const &other) const;

		rz::vector3 &lerp(rz::vector3 const &other, float amt);

		static rz::vector3 normalise(rz::vector3 const &v) { return rz::vector3(v).normalise(); }
		static rz::vector3 negate(rz::vector3 const &v) { return rz::vector3(v).negate(); }

		static rz::vector3 clamp(rz::vector3 const &v, rz::vector3 const &lower, rz::vector3 const &upper)
		{
			return rz::vector3(v).clamp(lower, upper);
		}

		static rz::vector3 cross(rz::vector3 const &v1, rz::vector3 const &v2)
		{
			return rz::vector3(v1).cross(v2);
		}

		static float distance(rz::vector3 const &v1, rz::vector3 const &v2)
		{
			return rz::vector3(v1).distance(v2);
		}

		static float distance_squared(rz::vector3 const &v1, rz::vector3 const &v2)
		{
			return rz::vector3(v1).distance_squared(v2);
		}

		static float dot(rz::vector3 const &v1, rz::vector3 const &v2)
		{
			return rz::vector3(v1).dot(v2);
		}

		static rz::vector3 lerp(rz::vector3 const &v1, rz::vector3 const &v2, float amount)
		{
			return rz::vector3(v1).lerp(v2, amount);
		}
	};
}

rz::vector3 const operator+(float f, rz::vector3 const &v);
rz::vector3 const operator-(float f, rz::vector3 const &v);
rz::vector3 const operator*(float f, rz::vector3 const &v);
rz::vector3 const operator/(float f, rz::vector3 const &v);

