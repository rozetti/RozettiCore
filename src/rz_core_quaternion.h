/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include "rz_core_vector3.h"
#include "rz_core_matrix.h"

namespace rz
{
	class quaternion
	{
	public:
		float x;
		float y;
		float z;
		float w;

		quaternion();
		quaternion(float x, float y, float z, float w);

		void identity();
		void normalise();
		void rotation_axis(rz::vector3 const &vec, float angle);

		void to_axis_angle(rz::vector3 &out_axis, float &out_angle) const;

		rz::matrix to_matrix() const;
		rz::vector3 to_euler() const;

		static rz::quaternion create_identity();
		static rz::quaternion create_rotation_axis(rz::vector3 const &vec, float angle);
		static rz::quaternion create_from_euler(rz::vector3 const &vec);
		static rz::quaternion create_from_points(rz::vector3 const &from, rz::vector3 const &to);

		static void slerp(rz::quaternion &out, rz::quaternion const &q1, rz::quaternion const &q2, float t);
		static rz::quaternion slerp(rz::quaternion const &q1, rz::quaternion const &q2, float t);
		static rz::quaternion multiply(rz::quaternion const &q1, rz::quaternion const &q2);
	};
}
