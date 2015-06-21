/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

// todo crz: integer specialisation

namespace rz
{
	double random(double min, double max);

	template <typename T>
	T random(T const &min, T const &max)
	{
		return static_cast<T>(random(static_cast<double>(min), static_cast<double>(max)));
	}
}


