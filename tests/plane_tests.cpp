#include "tests.h"

TEST(PlaneTest, Ctor)
{
    rz::plane p(rz::vector3_factory::up, 1.0f);
    
    EXPECT_EQ(1.0f, p.distance_from_origin);
    EXPECT_TRUE(rz::vector3_factory::up == p.normal);
}

TEST(PlaneTest, Ctor2)
{
	rz::plane p(1.0f, 2.0f, 3.0f, 4.0f);

	EXPECT_EQ(1.0f, p.normal.x());
	EXPECT_EQ(2.0f, p.normal.y());
	EXPECT_EQ(3.0f, p.normal.z());
	EXPECT_EQ(4.0f, p.distance_from_origin);
}

TEST(PlaneTest, Normalise)
{
	rz::plane p(1.0f, 2.0f, 3.0f, 4.0f);

	p.normalise();

	EXPECT_NEAR(0.2673f, p.normal.x(), 0.01);
	EXPECT_NEAR(0.5345f, p.normal.y(), 0.01);
	EXPECT_NEAR(0.8017f, p.normal.z(), 0.01);
	EXPECT_NEAR(1.0690f, p.distance_from_origin, 0.001);
}

TEST(PlaneTest, Classify)
{
    rz::plane p0(rz::vector3_factory::up, 0.0f);
    rz::plane p1(rz::vector3_factory::up, 1.0f);
    rz::plane p2(rz::vector3_factory::up, -1.0f);
    
    auto c0 = p0.classify_point(rz::vector3_factory::zero);
    auto c1 = p1.classify_point(rz::vector3_factory::zero);
    auto c2 = p2.classify_point(rz::vector3_factory::zero);
    
    EXPECT_EQ((int)rz::plane::preposition::coincident, (int)c0);
    EXPECT_EQ((int)rz::plane::preposition::front, (int)c1);
    EXPECT_EQ((int)rz::plane::preposition::back, (int)c2);
}
