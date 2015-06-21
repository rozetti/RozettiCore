/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include "rz_core_lap_timer.h"

namespace rz
{
	class game
	{
	public:
		static void fix_game_time();
		static double get_game_time();
		static double get_elapsed_game_time();

		static long long get_game_time_milliseconds();
		static long long get_elapsed_game_time_milliseconds();

	private:
		static rz::lap_timer _gameTime;
		static double _gameElapsedTime;
	};
}