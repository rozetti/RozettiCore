#include "tests.h"

TEST(InterpolationTests, Lerp_FromOrigin)
{
	rz::vector3 v0;
	rz::vector3 v1(1.0f, 2.0f, 3.0f);

	auto v = rz::lerp(v0, v1, 0.5f);

	EXPECT_EQ(0.5f, v.x());
	EXPECT_EQ(1.0f, v.y());
	EXPECT_EQ(1.5f, v.z());
}

TEST(InterpolationTests, Lerp_NotFromOrigin)
{
	rz::vector3 v0(1.0f, 2.0f, 3.0f);
	rz::vector3 v1(2.0f, 3.0f, 4.0f);

	auto v = rz::lerp(v0, v1, 0.5f);

	EXPECT_EQ(1.5f, v.x());
	EXPECT_EQ(2.5f, v.y());
	EXPECT_EQ(3.5f, v.z());
}
