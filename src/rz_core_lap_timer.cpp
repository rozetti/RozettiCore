/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core_lap_timer.h"

#include <algorithm>
#include <numeric>
#include <assert.h>

rz::lap_timer::lap_timer(int number_of_sectors_per_lap, int number_of_lap_history_slots) :
	m_numberOfLapHistorySlots(number_of_lap_history_slots),
	m_numberOfSectors(number_of_sectors_per_lap),
	m_sectorTimes(m_numberOfSectors * m_numberOfLapHistorySlots),
	m_averageSectorTimes(m_numberOfSectors),
	m_averageLapTime(0.0),
	m_numberOfLapsCompleted(0),
	m_currentSectorIndex(0),
	m_timerStartTime(0.0),
	m_currentLapStartTime(0.0),
	m_currentSectorStartTime(0.0),
	m_nextSectorTimeIndex(0)
{
	reset();
}

int rz::lap_timer::get_number_of_sectors_per_lap() const
{
	return m_numberOfSectors;
}

int rz::lap_timer::get_number_of_lap_history_slots() const
{
	return m_numberOfLapHistorySlots;
}

long rz::lap_timer::get_number_of_laps_completed() const
{
	return m_numberOfLapsCompleted;
}

int rz::lap_timer::get_current_sector_number() const
{
	return m_nextSectorTimeIndex % get_number_of_sectors_per_lap();
}

void rz::lap_timer::zero_sector_times()
{
	m_sectorTimes.clear();
	m_nextSectorTimeIndex = 0;

	// irk crz: no decltype
	for (std::vector<double>::size_type i = 0; i < m_sectorTimes.capacity(); ++i)
	{
		m_sectorTimes.push_back(0.0);
	}
}

double rz::lap_timer::get_time() const
{
	return rz::time::get_total() - m_timerStartTime;
}

double rz::lap_timer::get_current_lap_start_time() const
{
	return m_currentLapStartTime;
}

double rz::lap_timer::get_current_sector_start_time() const
{
	return m_currentSectorStartTime;
}

double rz::lap_timer::get_elapsed_lap_time() const
{
	return rz::time::get_total() - m_currentLapStartTime;
}

double rz::lap_timer::get_elapsed_sector_time() const
{
	return rz::time::get_total() - m_currentSectorStartTime;
}

void rz::lap_timer::reset()
{
	zero_sector_times();

	m_numberOfLapsCompleted = 0;
	m_timerStartTime = rz::time::get_total();
	m_currentLapStartTime = m_timerStartTime;
	m_currentSectorStartTime = m_currentLapStartTime;
}

int rz::lap_timer::get_next_delta_index()
{
	auto n = m_nextSectorTimeIndex;

	auto max = get_number_of_lap_history_slots() * get_number_of_sectors_per_lap();

	++m_nextSectorTimeIndex;
	if (m_nextSectorTimeIndex == max)
	{
		m_nextSectorTimeIndex = 0;
	}

	return n;
}

double rz::lap_timer::sector()
{
	auto elapsed = get_elapsed_sector_time();

	m_sectorTimes[get_next_delta_index()] = elapsed;

	m_currentSectorStartTime += elapsed;

	return elapsed;
}

double rz::lap_timer::lap()
{
#ifdef WIN32
	if (0 != m_nextSectorTimeIndex % get_number_of_sectors_per_lap())
	{
		throw std::exception("rz::lap_timer::lap() called after wrong number of sectors");
	}
#endif
    
	++m_numberOfLapsCompleted;

	auto elapsed = m_currentSectorStartTime - m_currentLapStartTime;

	m_currentLapStartTime = m_currentSectorStartTime;

	return elapsed;
}

double rz::lap_timer::get_average_lap_time() const
{
	auto number_of_slots = static_cast<long>(get_number_of_lap_history_slots());

	auto number_of_laps = static_cast<int>(std::min(number_of_slots, get_number_of_laps_completed()));

	auto total = std::accumulate(m_sectorTimes.cbegin(), m_sectorTimes.cend(), 0.0);

	auto av = total / number_of_laps;

	return av;
}

