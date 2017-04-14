/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core_macros.h"

#include "rz_core_vector2.h"
#include "rz_core_vector3.h"
#include "rz_core_matrix.h"
#include <cmath>
#include <algorithm>

namespace rz
{
	vector2::vector2() : rz::vector3()
	{
	}

	vector2::vector2(vector2 const &vec) : rz::vector3(vec.x(), vec.y(), 0.0f)
	{
	}

	vector2::vector2(rz::vector2::tuple_type const &tuple) : 
		rz::vector3(std::get<0>(tuple), std::get<1>(tuple), 0.0f)
	{
	}

	vector2::vector2(float x, float y) : rz::vector3(x, y, 0.0f)
	{
	}

	void vector2::set(vector2 const &from)
	{
		rz::vector3::set(from.x(), from.y(), 0.0f);
	}

	void vector2::set(float x, float y)
	{
		rz::vector3::set(x, y, 0.0f);
	}
}

