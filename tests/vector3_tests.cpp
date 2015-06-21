#include "tests.h"

using rz::vector3;

TEST(Vector3Test, Ctor)
{
    vector3 v(1.0f, 2.0f, 3.0f);
    
    EXPECT_EQ(1.0f, v.x);
    EXPECT_EQ(2.0f, v.y);
    EXPECT_EQ(3.0f, v.z);
}

TEST(Vector3Test, CopyCtor)
{
    vector3 v0(1.0f, 2.0f, 3.0f);
    
    vector3 v(v0);
    
    EXPECT_EQ(1.0f, v.x);
    EXPECT_EQ(2.0f, v.y);
    EXPECT_EQ(3.0f, v.z);
}

TEST(Vector3Test, Assignment)
{
    vector3 v0(1.0f, 2.0f, 3.0f);
    
    vector3 v;
    v = v0;
    
    EXPECT_EQ(1.0f, v.x);
    EXPECT_EQ(2.0f, v.y);
    EXPECT_EQ(3.0f, v.z);
}

TEST(Vector3Test, Equals)
{
    vector3 v0(1.0f, 2.0f, 3.0f);
    vector3 v1(1.0f, 2.0f, 3.0f);
    
    vector3 v2(1.1f, 2.0f, 3.0f);
    vector3 v3(1.0f, 2.1f, 3.0f);
    vector3 v4(1.0f, 2.0f, 3.1f);
    
    vector3 v5(1.0f + FLT_EPSILON, 2.0f + FLT_EPSILON, 3.0f + FLT_EPSILON);
    vector3 v6(1.0f + rz::TWO_FLT_EPSILON, 2.0f + rz::TWO_FLT_EPSILON, 3.0f + rz::TWO_FLT_EPSILON);
    vector3 v7(1.0f + rz::THREE_FLT_EPSILON, 2.0f + rz::THREE_FLT_EPSILON, 3.0f + rz::THREE_FLT_EPSILON);
    
    EXPECT_TRUE(v0.equals(v1));
    EXPECT_FALSE(v0.equals(v2));
    EXPECT_FALSE(v0.equals(v3));
    EXPECT_FALSE(v0.equals(v4));
    EXPECT_TRUE(v0.equals(v5));
    EXPECT_FALSE(v0.equals(v6));
    EXPECT_FALSE(v0.equals(v7));
}

TEST(Vector3Test, OperatorEquals)
{
    vector3 v0(1.0f, 2.0f, 3.0f);
    vector3 v1(1.0f, 2.0f, 3.0f);
    
    vector3 v2(1.1f, 2.0f, 3.0f);
    vector3 v3(1.0f, 2.1f, 3.0f);
    vector3 v4(1.0f, 2.0f, 3.1f);
    
    EXPECT_TRUE(v0 == v1);
    EXPECT_FALSE(v0 == v2);
    EXPECT_TRUE(v0 != v3);
    EXPECT_FALSE(v0 == v4);
}

TEST(Vector3Test, Add)
{
    vector3 v(1.0f, 2.0f, 3.0f);
    
    v.add(1.0f, 2.0f, 3.0f);
    
    EXPECT_EQ(2.0f, v.x);
    EXPECT_EQ(4.0f, v.y);
    EXPECT_EQ(6.0f, v.z);
}

TEST(Vector3Test, OperatorPlus_Vector3)
{
    vector3 const v1(1.0f, 2.0f, 3.0f);
    vector3 const v2(2.0f, 3.0f, 4.0f);
    
    vector3 v_out = v1 + v2;
    
    EXPECT_EQ(3.0f, v_out.x);
    EXPECT_EQ(5.0f, v_out.y);
    EXPECT_EQ(7.0f, v_out.z);
}

TEST(Vector3Test, OperatorPlus_Float)
{
    vector3 const v1(1.0f, 2.0f, 3.0f);
    
    vector3 v_out1 = v1 + 2.0f;
    
    EXPECT_EQ(3.0f, v_out1.x);
    EXPECT_EQ(4.0f, v_out1.y);
    EXPECT_EQ(5.0f, v_out1.z);
    
    vector3 v_out2 = 2.0f + v1;
    
    EXPECT_EQ(3.0f, v_out2.x);
    EXPECT_EQ(4.0f, v_out2.y);
    EXPECT_EQ(5.0f, v_out2.z);
}

TEST(Vector3Test, Subtract)
{
    vector3 v(1.0f, 2.0f, 3.0f);
    
    v.subtract(1.0f, 2.0f, 3.0f);
    
    EXPECT_EQ(0.0f, v.x);
    EXPECT_EQ(0.0f, v.y);
    EXPECT_EQ(0.0f, v.z);
}

TEST(Vector3Test, OperatorMinus_Vector3)
{
    vector3 const v1(1.0f, 2.0f, 3.0f);
    vector3 const v2(2.0f, 3.0f, 4.0f);
    
    vector3 v_out = v1 - v2;
    
    EXPECT_TRUE(vector3(-1.0f, -1.0f, -1.0f) == v_out);
    EXPECT_TRUE(vector3(1.0f, 2.0f, 3.0f) == v1);
    EXPECT_TRUE(vector3(2.0f, 3.0f, 4.0f) == v2);
}

TEST(Vector3Test, OperatorMinus_Float)
{
    vector3 const v1(1.0f, 2.0f, 3.0f);
    
    vector3 v_out1 = v1 - 2.0f;
    vector3 v_out2 = 2.0f - v1;
    
    EXPECT_TRUE(vector3(-1.0f, 0.0f, 1.0f) == v_out1);
    EXPECT_TRUE(vector3(1.0f, 0.0f, -1.0f) == v_out2);
    EXPECT_TRUE(vector3(1.0f, 2.0f, 3.0f) == v1);
}

TEST(Vector3Test, Multiply)
{
    vector3 v(1.0f, 2.0f, 3.0f);
    
    v.multiply(2.0f, 3.0f, 4.0f);
    
    EXPECT_TRUE(vector3(2.0f, 6.0f, 12.0f) == v);
}

TEST(Vector3Test, OperatorMultiply_Vector3)
{
    vector3 const v1(1.0f, 2.0f, 3.0f);
    vector3 const v2(2.0f, 3.0f, 4.0f);
    
    vector3 v_out = v1 * v2;
    
    EXPECT_TRUE(vector3(2.0f, 6.0f, 12.0f) == v_out);
    EXPECT_TRUE(vector3(1.0f, 2.0f, 3.0f) == v1);
    EXPECT_TRUE(vector3(2.0f, 3.0f, 4.0f) == v2);
}

TEST(Vector3Test, OperatorMultiply_Float)
{
    vector3 const v1(1.0f, 2.0f, 3.0f);
    
    vector3 v_out1 = v1 * 2.0f;
    vector3 v_out2 = 2.0f * v1;
    
    EXPECT_TRUE(vector3(2.0f, 4.0f, 6.0f) == v_out1);
    EXPECT_TRUE(vector3(2.0f, 4.0f, 6.0f) == v_out2);
    EXPECT_TRUE(vector3(1.0f, 2.0f, 3.0f) == v1);
}

TEST(Vector3Test, Divide)
{
    vector3 v(10.0f, 20.0f, 30.0f);
    
    v.divide(1.0f, 2.0f, 3.0f);
    
    EXPECT_EQ(10.0f, v.x);
    EXPECT_EQ(10.0f, v.y);
    EXPECT_EQ(10.0f, v.z);
}

TEST(Vector3Test, OperatorDivide_Vector3)
{
    vector3 const v1(4.0f, 6.0f, 8.0f);
    vector3 const v2(2.0f, 3.0f, 4.0f);
    
    vector3 v_out = v1 / v2;
    
    EXPECT_TRUE(vector3(2.0f, 2.0f, 2.0f) == v_out);
    EXPECT_TRUE(vector3(4.0f, 6.0f, 8.0f) == v1);
    EXPECT_TRUE(vector3(2.0f, 3.0f, 4.0f) == v2);
}

TEST(Vector3Test, OperatorDivide_Float)
{
    vector3 const v1(4.0f, 6.0f, 8.0f);
    
    vector3 v_out1 = v1 / 2.0f;
    vector3 v_out2 = 24.0f / v1;
    
    EXPECT_TRUE(vector3(2.0f, 3.0f, 4.0f) == v_out1);
    EXPECT_TRUE(vector3(6.0f, 4.0f, 3.0f) == v_out2);
    EXPECT_TRUE(vector3(4.0f, 6.0f, 8.0f) == v1);
}

TEST(Vector3Test, Cross)
{
    vector3 v1(1.0f, 2.0f, 3.0f);
    vector3 v2(2.0f, 3.0f, 4.0f);
    
    float x = 8.0f - 9.0f;
    float y = -(4.0f - 6.0f);
    float z = 3.0f - 4.0f;
    
    vector3 v_out(x, y, z);
    
    vector3 r = v1.cross(v2);
    
    EXPECT_TRUE(v_out.equals(r));
}

TEST(Vector3Test, Static_Cross)
{
	vector3 v1(1.0f, 2.0f, 3.0f);
	vector3 v2(2.0f, 3.0f, 4.0f);

	vector3 v = rz::vector3::cross(v1, v2);

	EXPECT_TRUE(v.equals(v1.cross(v2)));
}

TEST(Vector3Test, Clamp)
{
    vector3 v_too_low(0.0f, 0.0f, 0.0f);
    vector3 v_too_high(10.0f, 10.0f, 10.0f);
    vector3 v_lower_bound(1.0f, 2.0f, 3.0f);
    vector3 v_upper_bound(2.0f, 3.0f, 4.0f);
    
    vector3 v_out1 = v_too_low.clamp(v_lower_bound, v_upper_bound);
    vector3 v_out2 = v_too_high.clamp(v_lower_bound, v_upper_bound);
    
    EXPECT_TRUE(v_lower_bound == v_out1);
    EXPECT_TRUE(v_upper_bound == v_out2);
}

TEST(Vector3Test, Normalise)
{
    vector3 v(2.0f, 2.0f, 2.0f);
    v.normalise();
    
    float a = 1.0f / static_cast<float>(std::sqrt(3.0));
    
	// todo crz: this is lazy and weak
    EXPECT_EQ(a, v.x);
    EXPECT_EQ(a, v.y);
    EXPECT_EQ(a, v.z);
}

TEST(Vector3Test, Negate)
{
    vector3 v(1.0f, 2.0f, 3.0f);
    v.negate();
    
    EXPECT_TRUE(vector3(-1.0f, -2.0f, -3.0f) == v);
}

TEST(Vector3Test, LengthSquared)
{
    vector3 v(1.0f, 2.0f, 3.0f);
    
    float l = 1.0f + 4.0f + 9.0f;
    
    EXPECT_EQ(l, v.length_squared());
}

TEST(Vector3Test, Length)
{
    vector3 v(1.0f, 2.0f, 3.0f);
    
    double l = 1.0 + 4.0 + 9.0;
    l = static_cast<float>(std::sqrt(l));
    
    EXPECT_EQ(static_cast<float>(l), v.length());
}

TEST(Vector3Test, DistanceSquared)
{
    vector3 v1(1.0f, 0.0f, 0.0f);
    vector3 v2(1.0f, 2.0f, 0.0f);
    
    EXPECT_EQ(4.0f, v1.distance_squared(v2));
}

TEST(Vector3Test, Distance)
{
    vector3 v1(1.0f, 0.0f, 0.0f);
    vector3 v2(1.0f, 2.0f, 0.0f);
    
    EXPECT_EQ(2.0f, v1.distance(v2));
}

TEST(Vector3Test, Dot)
{
    vector3 v1(1.0f, 2.0f, 3.0f);
    vector3 v2(2.0f, 3.0f, 4.0f);
    
    float d = 2.0f + 6.0f + 12.0f;
    
    EXPECT_EQ(d, v1.dot(v2));
}

TEST(Vector3Test, Lerp)
{
    vector3 v1(1.0f, 2.0f, 3.0f);
    vector3 v2(2.0f, 3.0f, 4.0f);
    
    v1.lerp(v2, 0.5f);
    
    EXPECT_TRUE(vector3(1.5f, 2.5f, 3.5f) == v1);
}
