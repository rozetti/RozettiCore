#include "tests.h"

TEST(PrintfTest, Int)
{
    std::string s = rz::printf("%i", 1729);
    
    EXPECT_EQ(std::string("1729"), s);
}

TEST(PrintfTest, Long)
{
    std::string s = rz::printf("%li", 1729);
    
    EXPECT_EQ(std::string("1729"), s);
}

TEST(PrintfTest, Float)
{
    std::string s = rz::printf("%f", 3.142f);
    
    EXPECT_EQ(std::string("3.142000"), s); // todo crz: work out wht these have 6 d.p.
}

TEST(PrintfTest, Double)
{
    std::string s = rz::printf("%f", 3.142);
    
    EXPECT_EQ(std::string("3.142000"), s);
}

TEST(PrintfTest, String)
{
    std::string s = rz::printf("%s", "hello");
    
    EXPECT_EQ(std::string("hello"), s);
}

TEST(PrintfTest, StringAndInt)
{
    std::string s = rz::printf("%s %i", "hello", 1729);
    
    EXPECT_EQ(std::string("hello 1729"), s);
}

TEST(PrintfTest, LongAndStringAndInt)
{
    std::string s = rz::printf("%li %s %i", 1729L, "hello", 42);
    
    EXPECT_EQ(std::string("1729 hello 42"), s);
}

TEST(PrintfTest, DoubleWithPresicion)
{
    std::string s = rz::printf("%.5f", 3.142);
    EXPECT_EQ(std::string("3.14200"), s);
    
    s = rz::printf("%.0f", 3.142);
    EXPECT_EQ(std::string("3"), s);
    
    s = rz::printf("%.1f", 3.142);
    EXPECT_EQ(std::string("3.1"), s);
    
    s = rz::printf("%.3f", 3.142);
    EXPECT_EQ(std::string("3.142"), s);
    
    s = rz::printf("%.5f", 3.142);
    EXPECT_EQ(std::string("3.14200"), s);
}
