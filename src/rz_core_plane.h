/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include "rz_core_vector3.h"

namespace rz
{
	class plane
	{
	public:
		enum preposition
		{
			front,
			back,
			coincident,
		};

		rz::vector3 normal;
		float distance_from_origin;

		inline float x() const { return normal.x(); }
		inline float y() const { return normal.y(); }
		inline float z() const { return normal.z(); }
		inline float d() const { return distance_from_origin; }

		rz::plane(rz::vector3 const &normal, float distance);
		rz::plane(float x, float y, float z, float d);
		
		void normalise();

		preposition classify_point(rz::vector3 const &v) const;
	};
}
