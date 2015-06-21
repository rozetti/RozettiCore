/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

namespace rz
{
	template <typename T> T lerp(T v1, T v2, float factor)
	{
		return (v1 + ((v2 - v1) * factor));
	}
}