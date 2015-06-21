/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core_random.h"

#include <cstdlib>

double rz::random(double _min, double _max)
{
	auto r = static_cast<double>(std::rand());
	auto d = r / RAND_MAX;
	auto n = d * (_max - _min);
	
	return _min + n;
}


