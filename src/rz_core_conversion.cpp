/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core_conversion.h"

#include <string>
#include <sstream>

int rz::to_int(std::string const &s, int default_value)
{
	return convert_to<int>(s, default_value);
}

float rz::to_float(std::string const &s, float default_value)
{
	return convert_to<float>(s, default_value);
}

double rz::to_double(std::string const &s, double default_value)
{
	return convert_to<double>(s, default_value);
}