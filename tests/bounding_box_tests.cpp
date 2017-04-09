#include "tests.h"

TEST(BoundingBoxTest, DefaultCtor)
{
	rz::bounding_box box;

	EXPECT_EQ(0, box.min().x());
	EXPECT_EQ(0, box.min().y());
	EXPECT_EQ(0, box.min().z());

	EXPECT_EQ(0, box.max().x());
	EXPECT_EQ(0, box.max().y());
	EXPECT_EQ(0, box.max().z());
}

TEST(BoundingBoxTest, Ctor)
{
    rz::vector3 min(1.0f, 1.0f, 1.0f);
    rz::vector3 max(3.0f, 3.0f, 3.0f);
    
    rz::bounding_box box(min, max);
    
    EXPECT_TRUE(min == box.min());
    EXPECT_TRUE(max == box.max());
}

TEST(BoundingBoxTest, Contains)
{
    rz::bounding_box box(rz::vector3(1.0f, 1.0f, 1.0f), rz::vector3(3.0f, 3.0f, 3.0f));
    
    EXPECT_TRUE(box.contains(rz::vector3(2.0f, 2.0f, 2.0f)));
    EXPECT_FALSE(box.contains(rz::vector3(0.0f, 0.0f, 0.0f)));
}

TEST(BoundingBoxTest, IntersectsBoundingBox)
{
    rz::bounding_box box1(rz::vector3(0.0f, 0.0f, 0.0f), rz::vector3(1.9f, 1.9f, 1.9f));
    rz::bounding_box box2(rz::vector3(1.0f, 1.0f, 1.0f), rz::vector3(2.9f, 2.9f, 2.9f));
    rz::bounding_box box3(rz::vector3(2.0f, 2.0f, 2.0f), rz::vector3(4.0f, 4.0f, 4.0f));
    
    EXPECT_TRUE(box1.intersects(box2));
    EXPECT_TRUE(box2.intersects(box1));
    EXPECT_TRUE(box2.intersects(box3));
    EXPECT_TRUE(box3.intersects(box2));
    
    EXPECT_FALSE(box1.intersects(box3));
    EXPECT_FALSE(box3.intersects(box1));
}

TEST(BoundingBoxTest, IntersectsBoundingSphere)
{
    rz::bounding_box box(rz::vector3(1.0f, 1.0f, 1.0f), rz::vector3(3.0f, 3.0f, 3.0f));
    
    rz::bounding_sphere sphere1(rz::vector3(0.0f, 0.0f, 0.0f), 0.9f);
    rz::bounding_sphere sphere2(rz::vector3(0.0f, 0.0f, 0.0f), 2.0f);
    
    EXPECT_FALSE(box.intersects(sphere1));
    EXPECT_TRUE(box.intersects(sphere2));
}
