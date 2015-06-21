/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include "rz_core_vector2.h"

// todo crz: this class has no tests, so be careful (or write some)

namespace rz
{
	template <typename T> T to_radians(T const &degrees)
	{ 
		return degrees * static_cast<T>(rz::PI) / static_cast<T>(180.0); 
	} 
	
	template <typename T> T to_degrees(T const &radians) 
	{ 
		return radians * static_cast<T>(180.0) / static_cast<T>(rz::PI); 
	} 

	template <typename T> T normalise_angle(T angle)
	{
		int n = (int)(angle / static_cast<T>(rz::TWO_PI));

		if (angle < 0) 
		{ 
			return static_cast<T>(rz::TWO_PI) + (angle - (static_cast<T>(rz::TWO_PI) * n)); 
		} 

		return angle - (static_cast<T>(rz::TWO_PI) * n); 
	}

	template <typename T> T normalise_angle_signed(T radians)
	{
        radians = normalise_angle(radians);
        
        if (radians > static_cast<T>(rz::PI))
        {
            radians -= static_cast<T>(rz::TWO_PI);
        }
        
        return radians;
	}

	// todo crz: refactor this
	template <typename T> T angle_between_points(T x1, T y1, T x2, T y2)
	{
		T dx = std::abs(x1 - x2);

		if (dx <= rz::ONE_FLT_EPSILON) // todo crz: this is worst case - specialise for float/double
		{
			if (y2 > y1)
			{
				return rz::to_radians(static_cast<T>(90.0));
			}
			else if (y2 < y1)
			{
				return rz::to_radians(static_cast<T>(-90.0));
			}
			else
			{
				return 0.0;
			}
		}
	
		T dy = std::abs(y1 - y2);
		T arctan = std::atan(dy / dx);
	
		if (x2 >= x1 && y2 <= y1)
		{
			arctan = (rz::to_radians(static_cast<T>(360.0)) - arctan);
		}
		else if (x2 >= x1 && y2 > y1)
		{
			// todo crz: what am I doing here?
		}
		else if (x2 < x1 && y2 <= y1)
		{
			arctan = (rz::to_radians(static_cast<T>(180.0)) + arctan);
		}
		else if (x2 < x1 && y2 > y1)
		{
			arctan = (rz::to_radians(static_cast<T>(180.0)) - arctan);
		}
	
		return arctan;
	}

	float angle_between_points(rz::vector2 const &origin, rz::vector2 const &target);
	double angle_between_angles(double angle0, double angle1);
}
