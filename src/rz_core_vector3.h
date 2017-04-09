/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

// todo crz: template this

#include "rz_core_math_templates.h"

#define NOMINMAX 
#include <cmath>

#undef min // crz: fear
#undef max

namespace rz
{
	class matrix;

	class vector3
	{
		float m_x;
		float m_y;
		float m_z;
		float m_w;

	public:
		inline float x() const { return m_x; }
		inline float y() const { return m_y; }
		inline float z() const { return m_z; }

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
		rz::vector3 &add(rz::vector3 const &other) { return add(other.m_x, other.m_y, other.m_z); }
		rz::vector3 &add(float f) { return add(f, f, f); }
		rz::vector3 const operator+(float f) const { return rz::vector3(*this).add(f); }
		rz::vector3 const operator+(rz::vector3 const &other) const { return rz::vector3(*this).add(other); }
		void operator+=(float f) { (*this).add(f); }
		
		rz::vector3 &subtract(float x, float y, float z);
		rz::vector3 &subtract(rz::vector3 const &other) { return subtract(other.m_x, other.m_y, other.m_z); }
		rz::vector3 &subtract(float f) { return subtract(f, f, f); }
		rz::vector3 const operator-(float f) const { return rz::vector3(*this).subtract(f); }
		rz::vector3 const operator-(rz::vector3 const &other) const { return rz::vector3(*this).subtract(other); }
		void operator-=(float f) { (*this).subtract(f); }
		
		rz::vector3 &multiply(float x, float y, float z);
		rz::vector3 &multiply(rz::vector3 const &v) { return multiply(v.m_x, v.m_y, v.m_z); }
		rz::vector3 &multiply(float f) { return multiply(f, f, f); }
		rz::vector3 const operator*(float f) const { return rz::vector3(*this).multiply(f); }
		rz::vector3 const operator*(rz::vector3 const &v) const { return rz::vector3(*this).multiply(v); }

		rz::vector3 &divide(float x, float y, float z);
		rz::vector3 &divide(rz::vector3 const &v) { return divide(v.m_x, v.m_y, v.m_z); }
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

		float sum() const 
		{
			return m_x + m_y + m_z;
		}

		vector3 squared() const
		{
			return *this * *this;
		}

		rz::vector3 &lerp(rz::vector3 const &other, float amt);

		static rz::vector3 normalise(rz::vector3 const &v) { return rz::vector3(v).normalise(); }
		static rz::vector3 negate(rz::vector3 const &v) { return rz::vector3(v).negate(); }

		static rz::vector3 clamp(rz::vector3 const &v, rz::vector3 const &lower, rz::vector3 const &upper)
		{
			return rz::vector3(v).clamp(lower, upper);
		}

		static rz::vector3 max(rz::vector3 const &v1, rz::vector3 const &v2)
		{
			vector3 v;
			v.m_x = rz::max(v1.m_x, v2.m_x);
			v.m_y = rz::max(v1.m_y, v2.m_y);
			v.m_z = rz::max(v1.m_z, v2.m_z);
			return v;
		}

		static rz::vector3 min(rz::vector3 const &v1, rz::vector3 const &v2)
		{
			vector3 v;
			v.m_x = rz::min(v1.m_x, v2.m_x);
			v.m_y = rz::min(v1.m_y, v2.m_y);
			v.m_z = rz::min(v1.m_z, v2.m_z);
			return v;
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

