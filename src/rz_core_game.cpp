/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core_game.h"

rz::lap_timer rz::game::_gameTime(1, 10);
double rz::game::_gameElapsedTime(0.0);

void rz::game::fix_game_time()
{
	_gameTime.sector();
	_gameElapsedTime = _gameTime.lap();
}

double rz::game::get_game_time()
{
	return _gameTime.get_current_lap_start_time();
}

double rz::game::get_elapsed_game_time()
{
	return _gameElapsedTime;
}

long long rz::game::get_game_time_milliseconds()
{
	auto t = static_cast<long long>(get_game_time() * 1000.0);

	return t;
}

long long rz::game::get_elapsed_game_time_milliseconds()
{
	auto t = static_cast<long long>(get_elapsed_game_time() * 1000.0);

	return t;
}
