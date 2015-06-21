/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core_vector3_factory.h"

rz::vector3 rz::vector3_factory::one(1.0f, 1.0f, 1.0f);
rz::vector3 rz::vector3_factory::zero(0.0f, 0.0f, 0.0f);
rz::vector3 rz::vector3_factory::up(0.0f, 1.0f, 0.0f);
rz::vector3 rz::vector3_factory::right(1.0f, 0.0f, 0.0f);
rz::vector3 rz::vector3_factory::back(0.0f, 0.0f, 1.0f);

rz::vector3 rz::vector3_factory::create_up(rz::vector3 const &eye_position, rz::vector3 const &eye_target)
{
	rz::vector3 lookat(eye_position - eye_target);
	lookat.normalise();

	auto right = rz::vector3::cross(lookat, rz::vector3_factory::up);
	right.normalise();

	return rz::vector3::cross(right, lookat);
}

