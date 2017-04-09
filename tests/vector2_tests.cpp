#include "tests.h"

// todo crz: these tests know that vector2 is implemented in vector3

TEST(Vector2Test, DefaultCtor)
{
    rz::vector2 v;
    
    EXPECT_EQ(0.0f, v.x());
    EXPECT_EQ(0.0f, v.y());
    EXPECT_EQ(0.0f, v.z());
}

TEST(Vector2Test, CtorFloats)
{
    rz::vector2 v(1.0f, 2.0f);
    
    EXPECT_EQ(1.0f, v.x());
    EXPECT_EQ(2.0f, v.y());
    EXPECT_EQ(0.0f, v.z());
}

TEST(Vector2Test, CopyCtor)
{
    rz::vector2 v2(1.0f, 2.0f);
    rz::vector2 v(v2);
    
    EXPECT_EQ(1.0f, v.x());
    EXPECT_EQ(2.0f, v.y());
    EXPECT_EQ(0.0f, v.z());
}

TEST(Vector2Test, SetFloats)
{
    rz::vector2 v;
    v.set(1.0f, 2.0f);
    
    EXPECT_EQ(1.0f, v.x());
    EXPECT_EQ(2.0f, v.y());
    EXPECT_EQ(0.0f, v.z());
}

TEST(Vector2Test, SetVector2)
{
    rz::vector2 v2(1.0f, 2.0f);
    
    rz::vector2 v;
    v.set(v2);
    
    EXPECT_EQ(1.0f, v.x());
    EXPECT_EQ(2.0f, v.y());
    EXPECT_EQ(0.0f, v.z());
}

TEST(Vector2Test, Distance)
{
    rz::vector2 v1;
    rz::vector2 v2(3.0f, 4.0f);
    
    EXPECT_EQ(v1.distance(v2), 5.0f);
}

TEST(Vector2FactoryTest, Zero)
{
    rz::vector2 v_zero(rz::vector2_factory::zero);
    
    EXPECT_TRUE(rz::vector2(0.0f, 0.0f) == v_zero);
}

TEST(Vector2FactoryTest, One)
{
    rz::vector2 v_one(rz::vector2_factory::one);
    
    EXPECT_TRUE(rz::vector2(1.0f, 1.0f) == v_one);
}
