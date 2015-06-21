#include "tests.h"

TEST(Vector3FactoryTest, CreateUp)
{
	auto eye = rz::vector3(0, 0, 0);
	auto target = rz::vector3(0, 0, 1);

	auto v = rz::vector3_factory::create_up(eye, target);

	EXPECT_EQ(0, v.x);
	EXPECT_EQ(1, v.y);
	EXPECT_EQ(0, v.z);
}