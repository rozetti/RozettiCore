#include "tests.h"

TEST(BoundingSphereTest, DefaultCtor)
{
	rz::bounding_sphere sphere;

	EXPECT_EQ(0, sphere.centre.x);
	EXPECT_EQ(0, sphere.centre.y);
	EXPECT_EQ(0, sphere.centre.z);

	EXPECT_EQ(0, sphere.radius);
}

TEST(BoundingSphereTest, Ctor)
{
    rz::vector3 centre(1.0f, 1.0f, 1.0f);
    
    rz::bounding_sphere sphere(centre, 2.0f);
    
    EXPECT_TRUE(centre == sphere.centre);
    EXPECT_EQ(2.0f, sphere.radius);
}

TEST(BoundingSphereTest, IntersectsBoundingSphere)
{
    rz::bounding_sphere sphere1(rz::vector3(1.0f, 1.0f, 1.0f), 0.9f);
    rz::bounding_sphere sphere2(rz::vector3(2.0f, 2.0f, 2.0f), 0.9f);
    rz::bounding_sphere sphere3(rz::vector3(3.0f, 3.0f, 3.0f), 0.9f);
    
    EXPECT_TRUE(sphere1.intersects(sphere2));
    EXPECT_TRUE(sphere2.intersects(sphere1));
    EXPECT_TRUE(sphere2.intersects(sphere3));
    EXPECT_TRUE(sphere3.intersects(sphere2));
    
    EXPECT_FALSE(sphere1.intersects(sphere3));
    EXPECT_FALSE(sphere3.intersects(sphere1));
}
