#include "tests.h"

TEST(StringTest, ToInt)
{
    int i = rz::to_int(std::string("2"), 0);
    EXPECT_EQ(2, i);
}

TEST(StringTest, ToFloat)
{
    float f = rz::to_float(std::string("2"), 0.0f);
    EXPECT_EQ(2.0f, f);
}

TEST(StringTest, ToDouble)
{
    double d = rz::to_double(std::string("2"), 0.0);
    EXPECT_EQ(2.0, d);
}

TEST(StringTest, ToIntFail)
{
    int i = rz::to_int(std::string("a2"), 0);
    EXPECT_EQ(0, i);
}

TEST(StringTest, ToFloatFail)
{
    float f = rz::to_float(std::string("a2"), 0.0f);
    EXPECT_EQ(0.0f, f);
}

TEST(StringTest, ToDoubleFail)
{
    double d = rz::to_double(std::string("a2"), 0.0);
    EXPECT_EQ(0.0, d);
}
