/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

namespace rz
{
	using milliseconds_t = long long;

	class time
	{
		// todo crz: I don't like this
		static double _total_zero_offset;
		static double _delta_marker;
		static double _delta;

		static long long _monotonic_correction;

	public:
		static long long get_monotonic_correction();
		static void set_monotonic_correction(long long correction);
		static long long get_monotonic_counter();
		static milliseconds_t get_monotonic_milliseconds();
		static double get_monotonic_time();

		static double get_total();
		static void reset_total(double new_time = 0.0);
		static double get_delta();
		static void reset_delta();
	};
}
