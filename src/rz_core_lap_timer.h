/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include "rz_core_clock.h"

#include <vector>

namespace rz
{
	class lap_timer
	{
	public:
		lap_timer(int number_of_sectors_per_lap, int number_of_lap_history_slots);

		int get_number_of_lap_history_slots() const;
		int get_number_of_sectors_per_lap() const;

		double get_time() const;
		double get_current_lap_start_time() const;
		double get_current_sector_start_time() const;

		double get_elapsed_lap_time() const;
		double get_elapsed_sector_time() const;

		double get_average_lap_time() const;

		int get_current_sector_number() const;
		long get_number_of_laps_completed() const;

		void reset();
		double lap();
		double sector();

	private:
		int get_next_delta_index();
		void zero_sector_times();

	private:
		double m_timerStartTime;
		double m_currentLapStartTime;
		double m_currentSectorStartTime;

		int m_numberOfLapHistorySlots;
		int m_numberOfSectors;

		long m_numberOfLapsCompleted;
		int m_currentSectorIndex;
		int m_currentLapHistorySlotIndex;

		double m_averageLapTime;
		std::vector<double> m_averageSectorTimes;
		std::vector<double> m_sectorTimes;
		int m_nextSectorTimeIndex;
	};
}