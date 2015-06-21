/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core_clock.h"

long long rz::time::_monotonic_correction = 0;
double rz::time::_total_zero_offset = 0;
double rz::time::_delta_marker = 0;
double rz::time::_delta = 0;

// todo crz: might be able to use <chrono> instead of qpc
#ifdef WIN32
namespace rz
{
	#include <windows.h>

	struct monotonic_clock
	{
		static long long counter()
		{
			LARGE_INTEGER li;
			QueryPerformanceCounter(&li);
			return li.QuadPart;
		}

		static long long frequency()
		{
			LARGE_INTEGER li;
			QueryPerformanceFrequency(&li);
			return li.QuadPart;
		}
	};
}
#else
#include <chrono>

namespace rz
{
    struct monotonic_clock
    {
        static long long counter()
        {
            auto t = std::chrono::steady_clock::now();
            auto a = t.time_since_epoch();
            
            auto us = std::chrono::duration_cast<std::chrono::microseconds>(a);
            
            return us.count() * 10L;
        }
        
        static long long frequency()
        {
            return 1000L * 1000L * 10L;
        }
    };
}
#endif

// todo crz: use std::chrono
double rz::time::get_monotonic_time()
{
	auto c = rz::monotonic_clock::counter() + _monotonic_correction;
	auto f = rz::monotonic_clock::frequency();

	auto dc = static_cast<double>(c);
	auto df = static_cast<double>(f);

	return  dc / df;
}

long long rz::time::get_monotonic_counter()
{
	auto c = rz::monotonic_clock::counter() + _monotonic_correction;

	return c;
}

long long rz::time::get_monotonic_correction()
{
	return _monotonic_correction;
}

void rz::time::set_monotonic_correction(long long correction)
{
	_monotonic_correction = correction;

	reset_delta(); // todo crz: think of a way to avoid this
}

double rz::time::get_total()
{
	return get_monotonic_time() - _total_zero_offset;
}

void rz::time::reset_total(double new_total)
{
	auto now = get_total();

	_total_zero_offset = now - new_total;
}

double rz::time::get_delta()
{
	return _delta;
}

void rz::time::reset_delta()
{
	auto now = rz::time::get_monotonic_time();;

	_delta = now - _delta_marker;
	_delta_marker = now; 
}