/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include "rz_core_vector3.h"

// hack crz: this should probably be its own thing (not piggy-backing on vector3)

namespace rz
{
	class vector2 : public rz::vector3
	{
	public:
		vector2() : rz::vector3()
		{
		}

		vector2(vector2 const &vec) : rz::vector3(vec.x, vec.y, 0.0f)
		{
		}

		vector2(float x, float y) : rz::vector3(x, y, 0.0f)
		{
		}

		void set(vector2 const &from)
		{
			rz::vector3::set(from.x, from.y, 0.0f);
		}

		void set(float x, float y)
		{
			rz::vector3::set(x, y, 0.0f);
		}
	};
}
