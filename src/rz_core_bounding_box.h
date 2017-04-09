/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include "rz_core_vector3.h"

namespace rz
{
	class bounding_sphere;

	class bounding_box
	{
		rz::vector3 m_min;
		rz::vector3 m_max;

	public:
		bounding_box();
		bounding_box(bounding_box const &) = default;
		bounding_box(vector3 const &min, ::rz::vector3 const &max);

		vector3 min() const { return m_min; }
		vector3 max() const { return m_max; }

		bounding_box &operator=(bounding_box const &other)
		{
			m_min = other.m_min;
			m_max = other.m_max;

			return *this;
		}

		bool contains(::rz::vector3 const &point) const;

		bool intersects(bounding_box const &box) const;
		bool intersects(rz::bounding_sphere const &sphere) const;	
		//float intersects(rz::ray const &ray); // todo crz: implement this
		
		rz::bounding_box union_with(rz::bounding_box const &) const;
		rz::bounding_box union_with(rz::vector3 const &) const;

		rz::vector3 centre() const; // todo crz: untested
	};
}
