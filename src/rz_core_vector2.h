/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include "rz_core_vector3.h"

// hack crz: this should probably be its own thing (not piggy-backing on vector3)
// crz: no shit (did I really do this?)

namespace rz
{
	class vector2 : public rz::vector3
	{
	public:
		using element_type = rz::vector3::element_type;
		using tuple_type = std::tuple<element_type, element_type>;

		vector2();
		vector2(vector2 const &vec);
		vector2(tuple_type const &tuple);

		vector2(float x, float y);
		void set(vector2 const &from);
		void set(float x, float y);
	};
}
