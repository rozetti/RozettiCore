/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include <cmath>

namespace rz
{
	#undef max
	#undef min

	template <typename T> T max(T const &a, T const &b)
	{
		return a > b ? a : b;
	}

	template <typename T> T min(T const &a, T const &b)
	{
		return a < b ? a : b;
	}

	template <typename T> double round(T const &n)
	{
		T a = std::floor(n + static_cast<T>(0.5)); // todo crz: handle negative numbers

		return static_cast<T>(static_cast<long>(a));
	}

	template <typename T> T sign(T const &n)
	{
		if (n < 0) return -1;
		if (n > 0) return 1;
		return 0;
	}

	template <typename T> T clamp(T const & n, T const &min, T const &max)
	{
		if (n < min) return min;
		if (n > max) return max;
		return n;
	}
}