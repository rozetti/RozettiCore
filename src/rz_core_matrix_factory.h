/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include "rz_core_matrix.h"

namespace rz
{
	struct matrix_factory
	{
		static rz::matrix const identity;

		static rz::matrix create_zero();
		static rz::matrix create_identity();

		static rz::matrix create_4x4_from_floats(float const *);

		static rz::matrix create(rz::vector3 const &rotation, rz::vector3 const &scale, rz::vector3 const &translation);

		static rz::matrix create_rotation(rz::vector3 const &axis, float radians);
		static rz::matrix create_rotation_from_pitch_yaw_roll(rz::vector3 const &pyr);
		static rz::matrix create_rotation_around_x(float radians);
		static rz::matrix create_rotation_around_y(float radians);
		static rz::matrix create_rotation_around_z(float radians);

		static rz::matrix create_scaling(rz::vector3 const &scale);
		static rz::matrix create_translation(rz::vector3 const &translation);

		static rz::matrix create_look_at(rz::vector3 const &eye_position, rz::vector3 const &eye_target, rz::vector3 const &eye_up);
		static rz::matrix create_orthographic_projection(float left, float right, float top, float bottom, float _near, float _far);
		static rz::matrix create_perspective_projection(float fov,float aspect_ratio, float _near, float _far);
	};
}