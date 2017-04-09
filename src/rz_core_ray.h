/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include "rz_core_plane.h"
#include "rz_core_bounding_box.h"
#include "rz_core_bounding_sphere.h"

namespace rz
{
	class ray
	{
	public:
		rz::vector3 position;
		rz::vector3 direction;

		rz::ray() = delete;
		rz::ray(rz::vector3 const &pos, rz::vector3 const &dir);

		float intersection_with(rz::bounding_sphere const &sphere) const;
		float intersection_with(rz::bounding_box const &box) const;
		float intersection_with(rz::plane const &plane) const;
	};
}
