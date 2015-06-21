#include "tests.h"

#include <vector>
#include <algorithm>

struct Container
{
    static int const MIDDLE_SIZE = 5;
    
    Container()
    {
        int ii[] = { 3, 1, 4, 2, 1, 5, 6, 5, 3, 5 };
        
        int n = sizeof(ii) / sizeof(int);
        
        for (int i = 0; i < n; ++i)
        {
            vv.push_back(ii[i]);
        }
    }
    
    std::vector<int>::const_iterator begin() const { return vv.begin(); }
    std::vector<int>::const_iterator begin_middle() const
    {
        return std::find_if(vv.begin(), vv.end(), [](int const &i) { return i == 5; });
    }
    
    std::vector<int>::const_iterator end() const { return vv.end(); }
    
    std::vector<int> vv;
};

int const Container::MIDDLE_SIZE;

TEST(RangeTest, BeginEnd)
{
    Container c;
    
    auto r = rz::range<Container, std::vector<int>::const_iterator>(&c, &Container::begin, &Container::end);
    auto l = std::distance(r.begin(), r.end());
    EXPECT_EQ((size_t)l, c.vv.size());
}

TEST(RangeTest, BeginOnly)
{
    Container c;
    
    auto r = rz::range<Container, std::vector<int>::const_iterator>(&c, &Container::begin);
    auto l = std::distance(r.begin(), r.end());
    EXPECT_EQ((size_t)l, c.vv.size());
}

TEST(RangeTest, OtherBeginOnly)
{
    Container c;
    
    auto r = rz::range<Container, std::vector<int>::const_iterator>(&c, &Container::begin_middle);
    auto l = std::distance(r.begin(), r.end());
    EXPECT_EQ(l, Container::MIDDLE_SIZE);
}

TEST(RangeTest, MakeRangeCustomContainerRangeDistance)
{
    Container c;
    
    auto r1 = rz::make_range(c, &Container::begin);
    auto l1 = std::distance(r1.begin(), r1.end());
    EXPECT_EQ((size_t)l1, c.vv.size());
    
    auto r1a = rz::make_range(&c, &Container::begin, &Container::end);
    auto l1a = std::distance(r1.begin(), r1.end());
    EXPECT_EQ((size_t)l1a, c.vv.size());
    
    auto r2 = rz::make_range(c, &Container::begin_middle);
    auto l2 = std::distance(r2.begin(), r2.end());
    EXPECT_EQ(l2, Container::MIDDLE_SIZE);
    
    auto r2a = rz::make_range(&c, &Container::begin_middle, &Container::end);
    auto l2a = std::distance(r2a.begin(), r2a.end());
    EXPECT_EQ(l2a, Container::MIDDLE_SIZE);
}

TEST(RangeTest, MakeRangeCustomContainerRangeContent)
{
    Container c;
    
    auto r = rz::make_range(c, &Container::begin_middle);
    
    int n = 0;
    for (auto i : r)
    {
        int should_be = 0;
        switch (n++)
        {
            case 0:
                should_be = 5;
                break;
            case 1:
                should_be = 6;
                break;
            case 2:
                should_be = 5;
                break;
            case 3:
                should_be = 3;
                break;
            case 4:
                should_be = 5;
                break;
            default:
                ASSERT_TRUE(false) << "serious fail";
        }
        
        EXPECT_EQ(should_be, i);
    }
}

