#include "tests.h"

TEST(RectangleTests, DefaultCtor)
{
	rz::rectangle r;

	EXPECT_EQ(0.0f, r.x);
	EXPECT_EQ(0.0f, r.y);
	EXPECT_EQ(0.0f, r.width);
	EXPECT_EQ(0.0f, r.height);
}

TEST(RectangleTests, CTor)
{
    rz::rectangle r(2.0f, 3.0f, 4.0f, 5.0f);
    
    EXPECT_EQ(2.0f, r.x);
    EXPECT_EQ(3.0f, r.y);
    EXPECT_EQ(4.0f, r.width);
    EXPECT_EQ(5.0f, r.height);
}

TEST(RectangleTests, CopyCTor)
{
	rz::rectangle r(2.0f, 3.0f, 4.0f, 5.0f);
	auto r2(r);

	EXPECT_EQ(2.0f, r2.x);
	EXPECT_EQ(3.0f, r2.y);
	EXPECT_EQ(4.0f, r2.width);
	EXPECT_EQ(5.0f, r2.height);
}

TEST(RectangleTests, Right)
{
	rz::rectangle r(2.0f, 3.0f, 4.0f, 5.0f);

	EXPECT_EQ(6.0f, r.right());
}

TEST(RectangleTests, Bottom)
{
	rz::rectangle r(2.0f, 3.0f, 4.0f, 5.0f);

	EXPECT_EQ(8.0f, r.bottom());
}

TEST(RectangleTests, IsEmpty)
{
	rz::rectangle r1(2.0f, 3.0f, 4.0f, 5.0f);
	rz::rectangle r2(2.0f, 3.0f, 0.0f, 0.0f);

	EXPECT_FALSE(r1.is_empty());
	EXPECT_TRUE(r2.is_empty());
}

TEST(RectangleTests, Equals)
{
	rz::rectangle r(2.0f, 3.0f, 4.0f, 5.0f);
	
	rz::rectangle r_equal(2.0f, 3.0f, 4.0f, 5.0f);

	rz::rectangle r_not_equal1(9.0f, 3.0f, 4.0f, 5.0f);
	rz::rectangle r_not_equal2(2.0f, 9.0f, 4.0f, 5.0f);
	rz::rectangle r_not_equal3(2.0f, 3.0f, 9.0f, 5.0f);
	rz::rectangle r_not_equal4(2.0f, 3.0f, 4.0f, 9.0f);

	EXPECT_TRUE(r.equals(r_equal));

	EXPECT_FALSE(r.equals(r_not_equal1));
	EXPECT_FALSE(r.equals(r_not_equal2));
	EXPECT_FALSE(r.equals(r_not_equal3));
	EXPECT_FALSE(r.equals(r_not_equal4));
}

TEST(RectangleTests, UnionWith)
{
	rz::rectangle r1(2.0f, 3.0f, 4.0f, 5.0f);
	rz::rectangle r2(12.0f, 13.0f, 3.0f, 4.0f);

	auto r = r1.union_with(r2);

	EXPECT_EQ(2.0f, r.x);
	EXPECT_EQ(3.0f, r.y);
	EXPECT_EQ(13.0f, r.width);
	EXPECT_EQ(14.0f, r.height);
}

TEST(RectangleTests, UnionWithEmptyIsEmpty)
{
	rz::rectangle r1(2.0f, 3.0f, 4.0f, 5.0f);
	rz::rectangle r2(12.0f, 13.0f, 0.0f, 0.0f);

	EXPECT_TRUE(r1.union_with(r2).is_empty());
	EXPECT_TRUE(r2.union_with(r1).is_empty());
}

TEST(RectangleTests, IntersectionWith)
{
	rz::rectangle r1(2.0f, 3.0f, 4.0f, 5.0f);
	rz::rectangle r2(3.0f, 2.0f, 3.0f, 4.0f);

	auto r = r1.intersection_with(r2);

	EXPECT_EQ(3.0f, r.x);
	EXPECT_EQ(3.0f, r.y);
	EXPECT_EQ(3.0f, r.width);
	EXPECT_EQ(3.0f, r.height);
}

TEST(RectangleTests, IntersectionWith_EmptyIntersectionIsEmpty)
{
	rz::rectangle r1(2.0f, 3.0f, 4.0f, 5.0f);
	rz::rectangle r2(13.0f, 12.0f, 3.0f, 4.0f);

	auto r = r1.intersection_with(r2);

	EXPECT_TRUE(r.is_empty());
}

TEST(RectangleTests, Contains_PointInsideRectangleIsTrue)
{
	rz::rectangle r(2.0f, 3.0f, 4.0f, 5.0f);

	EXPECT_TRUE(r.contains(3.0f, 4.0f));
}

TEST(RectangleTests, Contains_PointOutsideRectangleIsFalse)
{
	rz::rectangle r(2.0f, 3.0f, 4.0f, 5.0f);

	EXPECT_FALSE(r.contains(1.0f, 4.0f));
	EXPECT_FALSE(r.contains(10.0f, 4.0f));
	EXPECT_FALSE(r.contains(5.0f, 2.0f));
	EXPECT_FALSE(r.contains(5.0f, 10.0f));
}

TEST(RectangleTests, Contains_RectangleInsideRectangleIsTrue)
{
	rz::rectangle r1(2.0f, 3.0f, 4.0f, 5.0f);
	rz::rectangle r2(3.0f, 4.0f, 1.0f, 1.0f);

	EXPECT_TRUE(r1.contains(r2));
}

TEST(RectangleTests, Contains_RectangleOutsideRectangleIsFalse)
{
	rz::rectangle r1(2.0f, 3.0f, 4.0f, 5.0f);
	rz::rectangle r2(3.0f, 4.0f, 1.0f, 1.0f);

	EXPECT_FALSE(r2.contains(r1));
}

TEST(RectangleTests, Intersects_NoIntersectionIsFalse)
{
	rz::rectangle r1(2.0f, 3.0f, 4.0f, 5.0f);
	rz::rectangle r2(13.0f, 14.0f, 1.0f, 1.0f);

	EXPECT_FALSE(r2.intersects(r1));
}

TEST(RectangleTests, Intersects_IntersectionIsTrue)
{
	rz::rectangle r1(2.0f, 3.0f, 4.0f, 5.0f);
	rz::rectangle r2(3.0f, 2.0f, 3.0f, 4.0f);

	EXPECT_TRUE(r2.intersects(r1));
}
