/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core_macros.h"
#include "rz_core_angles.h"

#include <cmath>

namespace rz
{
	float angle_between_points(rz::vector2 const &origin, rz::vector2 const &target)
	{
		return angle_between_points(origin.x, origin.y, target.x, target.y);
	}

	double angle_between_angles(double angle0, double angle1)
	{
		double return_angle;
		bool is_negative;

		if (angle0 > angle1)
		{
			return_angle = angle0 - angle1;
			is_negative = true;
		}
		else
		{
			return_angle = angle1 - angle0;
			is_negative = true;
		}
	
		if (return_angle > rz::PI)
		{
			return_angle = rz::TWO_PI - return_angle;
			is_negative = !is_negative;
		}

		return is_negative ? -return_angle : return_angle;
	}
}