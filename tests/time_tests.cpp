#include "tests.h"

#include <thread>

TEST(TimeTest, MonotonicTimeEvolves)
{
    auto t0 = rz::time::get_monotonic_time();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    auto t1 = rz::time::get_monotonic_time();
    
    EXPECT_TRUE(t1 > t0);
}

TEST(TimeTest, MonotonicCounterEvolves)
{
    auto c0 = rz::time::get_monotonic_counter();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    auto c1 = rz::time::get_monotonic_counter();
    
    EXPECT_TRUE(c1 > c0);
}

TEST(TimeTest, MonotonicCounterCorrectionWorks)
{
    long long correction = 1000000000;
    
    auto c0 = rz::time::get_monotonic_counter();
    rz::time::set_monotonic_correction(correction);
    
    auto c1 = rz::time::get_monotonic_counter();
    
    EXPECT_TRUE(c1 >= (c0 + correction));
    
    auto c = rz::time::get_monotonic_correction();
    EXPECT_TRUE(correction == c);
    
    rz::time::set_monotonic_correction(0);
    
    c = rz::time::get_monotonic_correction();
    EXPECT_TRUE(0 == c);
}

TEST(TimeTest, GetTotal)
{
    auto t0 = rz::time::get_total();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    auto t1 = rz::time::get_total();
    
    EXPECT_TRUE(t1 > t0);
}

TEST(TimeTest, ResetTotalWorks)
{
    auto t0 = rz::time::get_total();
    rz::time::reset_total();
    
    auto t1 = rz::time::get_total();
    
    EXPECT_TRUE(t1 < t0);
}

TEST(TimeTest, ResetTotalWithValueWorks)
{
    auto t0 = rz::time::get_total();
    
    auto new_total = t0 + 1000;
    rz::time::reset_total(new_total);
    
    auto t1 = rz::time::get_total();
    
    EXPECT_TRUE(t1 >= new_total);
}

TEST(TimeTest, GetDelta_DeltaIsConstant)
{
    auto d0 = rz::time::get_delta();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    auto d1 = rz::time::get_delta();
    
    EXPECT_EQ(d0, d1);
}

TEST(TimeTest, ResetDelta)
{
    auto d0 = rz::time::get_delta();
    
    rz::time::reset_delta();
    
    auto d1 = rz::time::get_delta();
    
    EXPECT_NE(d0, d1);
}
