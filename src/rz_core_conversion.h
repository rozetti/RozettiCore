/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include <ctime>
#include <string>
#include <sstream>

namespace rz
{
	template <typename T> T convert_to(std::string const &s, T default_value)
	{
		std::stringstream ss(s);

		T n = 0;
		if (ss >> n)
		{
			return n;
		}

		return default_value;
	}

	int to_int(std::string const &s, int default_value);
	float to_float(std::string const &s, float default_value);
	double to_double(std::string const &s, double default_value);
}