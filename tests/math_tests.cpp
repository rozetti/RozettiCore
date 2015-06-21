#include "tests.h"

#include <algorithm>

int i = 0;
unsigned int u = 0;
float f = 0.0f;
double d = 0.0;

TEST(MathTest, StandardLib)
{
    i = std::abs(-7);
    ASSERT_EQ(7, i);
    
    i = std::min(7, -3);
    ASSERT_EQ(-3, i);
    
    i = std::max(7, -3);
    ASSERT_EQ(7, i);
    
    d = std::sqrt(16.0);
    ASSERT_EQ(4.0, d);
    
    d = std::pow(3, 4);
    ASSERT_EQ(81.0, d);
    
    d = std::pow(3.0, 4);
    ASSERT_EQ(81.0, d);
    
    d = std::floor(3.142);
    ASSERT_EQ(3.0, d);
    
    d = std::ceil(3.142);
    ASSERT_EQ(4.0, d);
}

TEST(MathTest, Min)
{
    EXPECT_TRUE(rz::min(0.0, 1.0) == 0.0);
    EXPECT_TRUE(rz::min(1.0, 0.0) == 0.0);
    
    EXPECT_TRUE(rz::min(0.0f, 1.0f) == 0.0f);
    EXPECT_TRUE(rz::min(1.0f, 0.0f) == 0.0f);
    
    EXPECT_TRUE(rz::min(0, 1) == 0);
    EXPECT_TRUE(rz::min(1, 0) == 0);
}

TEST(MathTest, Max)
{
    EXPECT_TRUE(rz::max(0.0, 1.0) == 1.0);
    EXPECT_TRUE(rz::max(1.0, 0.0) == 1.0);
    
    EXPECT_TRUE(rz::max(0.0f, 1.0f) == 1.0f);
    EXPECT_TRUE(rz::max(1.0f, 0.0f) == 1.0f);
    
    EXPECT_TRUE(rz::max(0, 1) == 1);
    EXPECT_TRUE(rz::max(1, 0) == 1);
}

TEST(MathTest, Sign)
{
    EXPECT_EQ(0, rz::sign(0));
    EXPECT_EQ(-1, rz::sign(-4));
    EXPECT_EQ(1, rz::sign(4));
    
    EXPECT_EQ(-1.0, rz::sign(-4.0));
    EXPECT_EQ(1.0, rz::sign(4.0));
}

TEST(MathTest, Clamp)
{
    i = rz::clamp(6, 10, 20);
    EXPECT_EQ(10, i);
    
    i = rz::clamp(60, 10, 20);
    EXPECT_EQ(20, i);
    
    i = rz::clamp(16, 10, 20);
    EXPECT_EQ(16, i);
}

TEST(MathTest, Round)
{
    d = rz::round(3.142);
    EXPECT_EQ(3.0, d);
    
    d = rz::round(3.842);
    EXPECT_EQ(4.0, d);
    
    d = rz::round(-3.142); // todo crz: not sure what should happen here
    EXPECT_EQ(-3.0, d);
    
    d = rz::round(-3.842);
    EXPECT_EQ(-4.0, d);
}

TEST(MathTest, Angles)
{
    d = rz::to_degrees(rz::PI);
    EXPECT_EQ(180.0, d);
    
    d = rz::to_radians(180.0);
    EXPECT_EQ(rz::PI, d);
    
    d = rz::normalise_angle(rz::PI_OVER_TWO);
    EXPECT_EQ(rz::PI_OVER_TWO, d);

    d = rz::normalise_angle_signed(rz::PI_OVER_TWO);
    EXPECT_EQ(rz::PI_OVER_TWO, d);
    
    d = rz::normalise_angle(rz::PI_OVER_TWO * 3.0);
    EXPECT_EQ(rz::PI_OVER_TWO * 3.0, d);
    
    d = rz::normalise_angle_signed(rz::PI_OVER_TWO * -3.0);
    EXPECT_EQ(rz::PI_OVER_TWO * 1.0, d);

    d = rz::normalise_angle(rz::PI_OVER_TWO * 5.0);
    EXPECT_EQ(rz::PI_OVER_TWO, d);
    
    d = rz::normalise_angle(-rz::PI_OVER_TWO);
    EXPECT_EQ(rz::PI_OVER_TWO * 3.0, d);
    
    d = rz::normalise_angle_signed(-rz::PI_OVER_TWO);
    EXPECT_EQ(rz::PI_OVER_TWO * -1.0, d);

    d = rz::normalise_angle(-(rz::PI_OVER_TWO * 5.0));
    EXPECT_EQ(rz::PI_OVER_TWO * 3.0, d);

    d = rz::normalise_angle_signed(-(rz::PI_OVER_TWO * 5.0));
    EXPECT_EQ(rz::PI_OVER_TWO * -1.0, d);
    
    // todo crz: angles between points/angles
}
