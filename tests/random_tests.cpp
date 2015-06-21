#include "tests.h"

TEST(RandomTest, IsWithinRange)
{
    for (int t = 0; t < 1000; ++t)
    {
        int r = rz::random(17, 29);
        
        EXPECT_TRUE(r >= 17);
        EXPECT_TRUE(r <= 29);
    }
}

TEST(RandomTest, IsReasonablyRandom)
{
    const int _iterations = 1000;
    
    int lower_half = 0;
    
    for (int t = 0; t < _iterations; ++t)
    {
        auto r = rz::random(0.0, 1.0);
        if (r < 0.5)
        {
            ++lower_half;
        }
    }
    
    EXPECT_TRUE(lower_half > (_iterations / 4));
    EXPECT_TRUE(lower_half < (3 * _iterations / 4));
}
