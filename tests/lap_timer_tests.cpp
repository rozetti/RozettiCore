#include "tests.h"

#include <thread>

#define TIME_SLOP 1.0 // meh crz: I'm bored of these tests

TEST(LapTimerTest, CtorOneSlotOneSector)
{
    rz::lap_timer t(1, 1);
    
    int num_slots = t.get_number_of_lap_history_slots();
    int num_sectors = t.get_number_of_sectors_per_lap();
    
    EXPECT_EQ(1, num_slots);
    EXPECT_EQ(1, num_sectors);
}

TEST(LapTimerTest, CtorTwoSectorsThreeSlots)
{
    rz::lap_timer t(2, 3);
    
    int num_slots = t.get_number_of_lap_history_slots();
    int num_sectors = t.get_number_of_sectors_per_lap();
    
    EXPECT_EQ(2, num_sectors);
    EXPECT_EQ(3, num_slots);
}

TEST(LapTimerTest, StartsDuringConstruction)
{
    rz::lap_timer t(1, 1);
    
    auto t0 = t.get_time();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    auto t1 = t.get_time();
    
    EXPECT_TRUE(t1 > t0);
}

TEST(LapTimerTest, StartsFromZero)
{
    rz::lap_timer t(1, 1);
    
    auto t0 = t.get_time();
    
    EXPECT_NEAR(0.0, t0, 0.001);
}

TEST(LapTimerTest, GetTimeIsRealTime)
{
    rz::lap_timer t(1, 1);
    
    auto t0 = t.get_time();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    auto t1 = t.get_time();
    
    EXPECT_TRUE(t1 > t0);
}

TEST(LapTimerTest, IsInSeconds)
{
    rz::lap_timer t(1, 1);
    
    auto t0 = t.get_time();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto t1 = t.get_time();
    
    auto elapsed = t1 - t0;
    
    EXPECT_NEAR(0.1, elapsed, TIME_SLOP); // todo crz: work out a proper way of testing this
}

TEST(LapTimerTest, GetCurrentSectorNumber)
{
    rz::lap_timer t(2, 1);
    
    auto n0 = t.get_current_sector_number();
    EXPECT_EQ(0, n0);
    
    t.sector();
    auto n1 = t.get_current_sector_number();
    EXPECT_EQ(1, n1);
    
    t.sector();
    t.lap();
    auto n2 = t.get_current_sector_number();
    EXPECT_EQ(0, n2);
    
    t.sector();
    auto n3 = t.get_current_sector_number();
    EXPECT_EQ(1, n3);
    
    t.sector();
    t.lap();
    auto n4 = t.get_current_sector_number();
    EXPECT_EQ(0, n4);
}

TEST(LapTimerTest, GetCurrentSectorStartTime)
{
	rz::lap_timer t(2, 1);

	auto s0 = t.get_current_sector_start_time();

	t.sector();

	auto s1 = t.get_current_sector_start_time();
	EXPECT_TRUE(s1 > s0);
}

TEST(LapTimerTest, LapThrowIfSectorCalledWrongNumberOfTimes)
{
	rz::lap_timer t(3, 1);

	t.sector();
	
	EXPECT_THROW(t.lap(), std::exception);
}

TEST(LapTimerTest, LapTimes)
{
    rz::lap_timer t(1, 1);
    
    auto t0 = t.get_time();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    t.sector();
    auto l0 = t.lap();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    t.sector();
    auto l1 = t.lap();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    t.sector();
    auto l2 = t.lap();
    
    auto t1 = t.get_time();
    
    auto d = l0 + l1 + l2;
    auto dt = t1 - t0;
    
    EXPECT_NEAR(dt, d, 0.01);
}

TEST(LapTimerTest, SectorTimes)
{
    rz::lap_timer t(1, 3);
    
    auto t0 = t.get_time();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto s0 = t.sector();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto s1 = t.sector();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto s2 = t.sector();
    
    auto t1 = t.get_time();
    
    auto d = s0 + s1 + s2;
    auto dt = t1 - t0;
    
    EXPECT_NEAR(dt, d, 0.01);
}

TEST(LapTimerTest, LapTimeEqualsSumOfSectorTimes)
{
    rz::lap_timer t(1, 3);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto s0 = t.sector();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto s1 = t.sector();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto s2 = t.sector();
    auto l = t.lap();
    
    auto d = s0 + s1 + s2;
    
    EXPECT_EQ(l, d);
}

TEST(LapTimerTest, GetElapsedLapTime)
{
    rz::lap_timer t(1, 1);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto l = t.get_elapsed_lap_time();
    
    EXPECT_NEAR(0.1, l, TIME_SLOP); // meh crz
}

TEST(LapTimerTest, GetElapsedSectorTime)
{
    rz::lap_timer t(1, 1);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto l = t.get_elapsed_sector_time();
    
    EXPECT_NEAR(0.1, l, TIME_SLOP); // meh crz
}

TEST(LapTimerTest, GetNumberOfLapsCompleted)
{
    rz::lap_timer t(1,1);
    
    EXPECT_EQ(0L, t.get_number_of_laps_completed());
    
    t.sector();
    t.lap();
    
    EXPECT_EQ(1L, t.get_number_of_laps_completed());
    
    t.sector();
    t.lap();
    
    EXPECT_EQ(2L, t.get_number_of_laps_completed());
}

// todo crz: get rid of exceptions
//TEST(LapTimerTest, LapThrowsIfWrongNumberOfSectors)
//{
//    rz::lap_timer t(3, 1);
//    
//    t.sector();
//    t.sector();
//    
//    Assert::ExpectException<std::exception>([&t]
//                                            {
//                                                t.lap();
//                                            });
//}

TEST(LapTimerTest, SectorsAndLapsAddUp)
{
    rz::lap_timer t(3, 1);
    
    double s = 0.0;
    double l1 = 0.0;
    double l2 = 0.0;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    s += t.sector();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    s += t.sector();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    s += t.sector();
    l1 = t.lap();
    
    EXPECT_EQ(s, l1);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    s += t.sector();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    s += t.sector();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    s += t.sector();
    l2 = t.lap();
    
    auto total = l1 + l2;
    auto time = t.get_time();
    
    EXPECT_EQ(s, total);
    
    EXPECT_NEAR(time, total, TIME_SLOP);
}

TEST(LapTimerTest, GetAverageLapTime_SameNumberOfLapsAsSlots)
{
    rz::lap_timer t(1,3);
    
    for (int i = 0; i < 3; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        t.sector();
        t.lap();
    }
    
    double av = t.get_average_lap_time();
    
    EXPECT_NEAR(0.1, av, TIME_SLOP); // meh crz
}

TEST(LapTimerTest, GetAverageLapTime_FewerLapsThanSlots)
{
    rz::lap_timer t(1,5);
    
    for (int i = 0; i < 3; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        t.sector();
        t.lap();
    }
    
    double av = t.get_average_lap_time();
    
    EXPECT_NEAR(0.1, av, TIME_SLOP); // todo crz: bit pointless
}

TEST(LapTimerTest, GetAverageLapTime_MoreLapsThanSlots)
{
    rz::lap_timer t(1,3);
    
    for (int i = 0; i < 10; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        t.sector();
        t.lap();
    }
    
    double av = t.get_average_lap_time();
    
    EXPECT_NEAR(0.1, av, TIME_SLOP);
}

TEST(LapTimerTest, GetAverageLapTime_ManySectors)
{
    rz::lap_timer t(3,3);
    
    for (int i = 0; i < 10; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        t.sector();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        t.sector();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        t.sector();
        
        t.lap();
    }
    
    double av = t.get_average_lap_time();
    
	// todo crz: this test is a bit pointless unless the machine can be somehow forced to 'settle'
    EXPECT_NEAR(0.1, av, TIME_SLOP);
}

TEST(LapTimerTest, Reset)
{
    rz::lap_timer t(1,1);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    t.sector();
    t.lap();
    
    t.reset();
    
    auto total = t.get_time();
    auto laps = t.get_number_of_laps_completed();
    
    EXPECT_NEAR(0.0, total, TIME_SLOP);
    EXPECT_EQ(0L, laps);
}
