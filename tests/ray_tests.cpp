#include "tests.h"

// todo crz: needs more tests to cover the stolen code

TEST(RayTest, Ctor)
{
    rz::vector3 pos;
    auto dir = rz::vector3_factory::up;
    
    rz::ray ray(pos, dir);
    
    EXPECT_TRUE(rz::vector3_factory::zero == pos);
    EXPECT_TRUE(rz::vector3_factory::zero == ray.position);
    
    EXPECT_TRUE(rz::vector3_factory::up == dir);
    EXPECT_TRUE(rz::vector3_factory::up == ray.direction);
}

TEST(RayTest, IntersectsBoundingBox)
{
    rz::bounding_box box1(rz::vector3(1.0f, 1.0f, 1.0f), rz::vector3(2.0f, 2.0f, 2.0f));
    rz::bounding_box box2(rz::vector3(-1.0f, -1.0f, -1.0f), rz::vector3(2.0f, 2.0f, 2.0f));
    rz::bounding_box box3(rz::vector3(-1.0f, 1.0f, -1.0f), rz::vector3(2.0f, 2.0f, 2.0f));
    rz::bounding_box box4(rz::vector3(-1.0f, 10.0f, -1.0f), rz::vector3(2.0f, 20.0f, 2.0f));
    
    rz::vector3 pos;
    auto dir = rz::vector3_factory::up;
    
    rz::ray ray(pos, dir);
    
    float f1 = ray.intersection_with(box1);
    float f2 = ray.intersection_with(box2);
    float f3 = ray.intersection_with(box3);
    float f4 = ray.intersection_with(box4);
    
    EXPECT_EQ(-1.0f, f1);
	EXPECT_EQ(0.0f, f2);
	EXPECT_EQ(1.0f, f3);
	EXPECT_EQ(10.0f, f4);
}
