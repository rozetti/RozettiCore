/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include "rz_core_vector3.h"

namespace rz
{
	struct vector3_factory
	{
		static rz::vector3 create_up(rz::vector3 const &eye_position, rz::vector3 const &eye_target);

		static rz::vector3 one;
		static rz::vector3 zero;
		static rz::vector3 up;
		static rz::vector3 right;
		static rz::vector3 back;
	};
}
