#include "tests.h"

TEST(QuaternionTests, Ctor)
{
	rz::quaternion q;

	EXPECT_EQ(1.0f, q.w);
	EXPECT_EQ(0.0f, q.x);
	EXPECT_EQ(0.0f, q.y);
	EXPECT_EQ(0.0f, q.z);
}

// todo crz: no more tests because the code was stolen from various places, needs work
