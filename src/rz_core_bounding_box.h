/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include "rz_core_vector3.h"
#include "rz_core_bounding_sphere.h"

namespace rz
{
	class bounding_box
	{
	public:
		rz::vector3 min;
		rz::vector3 max;
		
		bounding_box();
		bounding_box(::rz::vector3 const &min, ::rz::vector3 const &max);

		bool contains(::rz::vector3 const &point);

		// crz: combinatorial explosion alert, need to think of a more general approach
		bool intersects(bounding_box const &box);
		bool intersects(rz::bounding_sphere const &sphere);	
	};
}
