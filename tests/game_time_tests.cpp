#include "tests.h"

#include <thread>

#define TIME_SLOP 1.0 // meh crz: I'm bored of these tests

TEST(GameTimeTest, GetGameTime_IsConstant)
{
    auto t0 = rz::game::get_game_time();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(40));
    
    auto t1 = rz::game::get_game_time();
    
    EXPECT_EQ(t0, t1);
}

TEST(GameTimeTest, Fix)
{
    rz::game::fix_game_time();
    auto t0 = rz::game::get_game_time();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(40));
    
    rz::game::fix_game_time();
    auto t1 = rz::game::get_game_time();
    
    auto d = t1 - t0;
    
    EXPECT_NEAR(0.04, d, TIME_SLOP); // meh crz
}

TEST(GameTimeTest, GetElapsedTime)
{
    rz::game::fix_game_time();
    std::this_thread::sleep_for(std::chrono::milliseconds(40));
    rz::game::fix_game_time();
    
    auto t = rz::game::get_elapsed_game_time();
    
    EXPECT_NEAR(0.04, t, TIME_SLOP);
}

TEST(GameTimeTest, GetGameTimeMilliseconds)
{
    auto d = rz::game::get_game_time();
    
    auto l = rz::game::get_game_time_milliseconds();
    
    EXPECT_NEAR(d * 1000.0, (double)l, 10.0);
}

TEST(GameTimeTest, GetElapsedGameTimeMilliseconds)
{
    auto d = rz::game::get_elapsed_game_time();
    
    auto l = rz::game::get_elapsed_game_time_milliseconds();
    
    EXPECT_NEAR(d * 1000.0, (double)l, 10.0);
}
