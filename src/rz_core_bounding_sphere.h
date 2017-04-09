/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include "rz_core_vector3.h"

namespace rz
{
	class bounding_box;

	class bounding_sphere
	{
	public:
		rz::vector3 centre;
		float radius;

		rz::bounding_sphere();
		rz::bounding_sphere(rz::vector3 const &center, float radius);

		bool intersects(rz::bounding_sphere const &sphere);
		//float intersects(rz::ray const &ray); // todo crz: implement this

		static rz::bounding_sphere from_bounding_box(rz::bounding_box const &);
	};
}
