/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include <cfloat>

namespace rz
{
	double const PI = 3.14159265358979323846;
	float const PI_f = static_cast<float>(PI);

	double const PI_OVER_TWO = PI / 2.0;
	float const PI_OVER_TWO_f = static_cast<float>(PI_OVER_TWO);
	
	double const THREE_PI_OVER_TWO = (3.0 * PI) / 2.0;
	float const THREE_PI_OVER_TWO_f = static_cast<float>(THREE_PI_OVER_TWO);

	double const TWO_PI = PI * 2.0;
	float const TWO_PI_f = static_cast<float>(TWO_PI);

	float const ONE_FLT_EPSILON = FLT_EPSILON;
	float const TWO_FLT_EPSILON = 2 * ONE_FLT_EPSILON;
	float const THREE_FLT_EPSILON = 3 * ONE_FLT_EPSILON;
}

#define FLT_EQUALS(a, b) (std::abs(a - b) < rz::TWO_FLT_EPSILON)

