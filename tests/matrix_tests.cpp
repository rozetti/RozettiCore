#include "tests.h"

static void fill(rz::matrix &m)
{
    m.M11(11.0f); m.M12(12.0f); m.M13(13.0f); m.M14(14.0f);
    m.M21(21.0f); m.M22(22.0f); m.M23(23.0f); m.M24(24.0f);
    m.M31(31.0f); m.M32(32.0f); m.M33(33.0f); m.M34(34.0f);
    m.M41(41.0f); m.M42(42.0f); m.M43(43.0f); m.M44(44.0f);
}

// todo crz: these:
//rz::vector3 rz::matrix::Up() const { return rz::vector3(M12, M22, M32); }
//rz::vector3 rz::matrix::Down() const { return rz::vector3(-M12, -M22, -M32); }
//rz::vector3 rz::matrix::Right() const { return rz::vector3(M11, M21, M31); }
//rz::vector3 rz::matrix::Left() const { return rz::vector3(-M11, -M21, -M31); }
//rz::vector3 rz::matrix::Back() const { return rz::vector3(M13, M23, M33); }
//rz::vector3 rz::matrix::Forward() const { return rz::vector3(-M13, -M23, -M33); }

TEST(MatrixTest, Ctor)
{
    rz::matrix matrix;
    
    EXPECT_EQ(1.0f, matrix.M11());
    EXPECT_EQ(0.0f, matrix.M12());
    EXPECT_EQ(0.0f, matrix.M13());
    EXPECT_EQ(0.0f, matrix.M14());
    
    EXPECT_EQ(0.0f, matrix.M21());
    EXPECT_EQ(1.0f, matrix.M22());
    EXPECT_EQ(0.0f, matrix.M23());
    EXPECT_EQ(0.0f, matrix.M24());
    
    EXPECT_EQ(0.0f, matrix.M31());
    EXPECT_EQ(0.0f, matrix.M32());
    EXPECT_EQ(1.0f, matrix.M33());
    EXPECT_EQ(0.0f, matrix.M34());
    
    EXPECT_EQ(0.0f, matrix.M41());
    EXPECT_EQ(0.0f, matrix.M42());
    EXPECT_EQ(0.0f, matrix.M43());
    EXPECT_EQ(1.0f, matrix.M44());
}

TEST(MatrixTest, BigCtor)
{
	float ff[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };

	rz::matrix matrix(ff);

	EXPECT_EQ(1.0f, matrix.M11());
	EXPECT_EQ(2.0f, matrix.M12());
	EXPECT_EQ(3.0f, matrix.M13());
	EXPECT_EQ(0.0f, matrix.M14());

	EXPECT_EQ(4.0f, matrix.M21());
	EXPECT_EQ(5.0f, matrix.M22());
	EXPECT_EQ(6.0f, matrix.M23());
	EXPECT_EQ(0.0f, matrix.M24());

	EXPECT_EQ(7.0f, matrix.M31());
	EXPECT_EQ(8.0f, matrix.M32());
	EXPECT_EQ(9.0f, matrix.M33());
	EXPECT_EQ(0.0f, matrix.M34());

	EXPECT_EQ(0.0f, matrix.M41());
	EXPECT_EQ(0.0f, matrix.M42());
	EXPECT_EQ(0.0f, matrix.M43());
	EXPECT_EQ(1.0f, matrix.M44());
}

TEST(MatrixTest, CopyCtor)
{
    rz::matrix m2;
    fill(m2);
    
    rz::matrix m1(m2);
    
    EXPECT_EQ(11.0f, m1.M11());
    EXPECT_EQ(12.0f, m1.M12());
    EXPECT_EQ(13.0f, m1.M13());
    EXPECT_EQ(14.0f, m1.M14());
    
    EXPECT_EQ(21.0f, m1.M21());
    EXPECT_EQ(22.0f, m1.M22());
    EXPECT_EQ(23.0f, m1.M23());
    EXPECT_EQ(24.0f, m1.M24());
    
    EXPECT_EQ(31.0f, m1.M31());
    EXPECT_EQ(32.0f, m1.M32());
    EXPECT_EQ(33.0f, m1.M33());
    EXPECT_EQ(34.0f, m1.M34());
    
    EXPECT_EQ(41.0f, m1.M41());
    EXPECT_EQ(42.0f, m1.M42());
    EXPECT_EQ(43.0f, m1.M43());
    EXPECT_EQ(44.0f, m1.M44());
}

TEST(MatrixTest, Assignment)
{
    rz::matrix m2;
    fill(m2);
    
    rz::matrix m1;
    m1 = m2;
    
    EXPECT_EQ(11.0f, m1.M11());
    EXPECT_EQ(12.0f, m1.M12());
    EXPECT_EQ(13.0f, m1.M13());
    EXPECT_EQ(14.0f, m1.M14());
    
    EXPECT_EQ(21.0f, m1.M21());
    EXPECT_EQ(22.0f, m1.M22());
    EXPECT_EQ(23.0f, m1.M23());
    EXPECT_EQ(24.0f, m1.M24());
    
    EXPECT_EQ(31.0f, m1.M31());
    EXPECT_EQ(32.0f, m1.M32());
    EXPECT_EQ(33.0f, m1.M33());
    EXPECT_EQ(34.0f, m1.M34());
    
    EXPECT_EQ(41.0f, m1.M41());
    EXPECT_EQ(42.0f, m1.M42());
    EXPECT_EQ(43.0f, m1.M43());
    EXPECT_EQ(44.0f, m1.M44());
}

TEST(MatrixTest, Zero)
{
    rz::matrix m2;
    fill(m2);
    
    m2.zero();
    
    EXPECT_EQ(0.0f, m2.M11());
    EXPECT_EQ(0.0f, m2.M12());
    EXPECT_EQ(0.0f, m2.M13());
    EXPECT_EQ(0.0f, m2.M14());
    
    EXPECT_EQ(0.0f, m2.M21());
    EXPECT_EQ(0.0f, m2.M22());
    EXPECT_EQ(0.0f, m2.M23());
    EXPECT_EQ(0.0f, m2.M24());
    
    EXPECT_EQ(0.0f, m2.M31());
    EXPECT_EQ(0.0f, m2.M32());
    EXPECT_EQ(0.0f, m2.M33());
    EXPECT_EQ(0.0f, m2.M34());
    
    EXPECT_EQ(0.0f, m2.M41());
    EXPECT_EQ(0.0f, m2.M42());
    EXPECT_EQ(0.0f, m2.M43());
    EXPECT_EQ(0.0f, m2.M44());
}

TEST(MatrixTest, Identity)
{
    rz::matrix m;
    m.identity();
    
    EXPECT_EQ(1.0f, m.M11());
    EXPECT_EQ(0.0f, m.M12());
    EXPECT_EQ(0.0f, m.M13());
    EXPECT_EQ(0.0f, m.M14());
    
    EXPECT_EQ(0.0f, m.M21());
    EXPECT_EQ(1.0f, m.M22());
    EXPECT_EQ(0.0f, m.M23());
    EXPECT_EQ(0.0f, m.M24());
    
    EXPECT_EQ(0.0f, m.M31());
    EXPECT_EQ(0.0f, m.M32());
    EXPECT_EQ(1.0f, m.M33());
    EXPECT_EQ(0.0f, m.M34());
    
    EXPECT_EQ(0.0f, m.M41());
    EXPECT_EQ(0.0f, m.M42());
    EXPECT_EQ(0.0f, m.M43());
    EXPECT_EQ(1.0f, m.M44());
}

TEST(MatrixTest, OperatorEquals)
{
    rz::matrix m1;
    rz::matrix m2;
    
    EXPECT_TRUE(m1 == m1);
    EXPECT_TRUE(m2 == m1);
    
    m1.zero();
    EXPECT_FALSE(m1 == m2);
    EXPECT_FALSE(m2 == m1);
    
    m2.zero();
    EXPECT_TRUE(m1 == m2);
    EXPECT_TRUE(m2 == m1);
    
    fill(m1);
    EXPECT_FALSE(m1 == m2);
    EXPECT_FALSE(m2 == m1);
    
    fill(m2);
    EXPECT_TRUE(m1 == m2);
    EXPECT_TRUE(m2 == m1);
}

TEST(MatrixTest, OperatorNotEquals)
{
    rz::matrix m1;
    rz::matrix m2;
    
    EXPECT_FALSE(m1 != m1);
    EXPECT_FALSE(m2 != m1);
    
    m1.zero();
    EXPECT_TRUE(m1 != m2);
    EXPECT_TRUE(m2 != m1);
    
    m2.zero();
    EXPECT_FALSE(m1 != m2);
    EXPECT_FALSE(m2 != m1);
    
    fill(m1);
    EXPECT_TRUE(m1 != m2);
    EXPECT_TRUE(m2 != m1);
    
    fill(m2);
    EXPECT_FALSE(m1 != m2);
    EXPECT_FALSE(m2 != m1);
}

TEST(MatrixTest, MultiplyMatrix)
{
    rz::matrix m1;
    rz::matrix m2;
    
    m1.identity();
    m2.identity();
    
    m1.multiply(m2);
    
    EXPECT_EQ(m1, m2);
    
    fill(m2);
    m1.multiply(m2);
    
    EXPECT_EQ(m1, m2);
    
    fill(m1);
    m2.identity();
    
    m2.multiply(m1);
    EXPECT_EQ(m1, m2);
}

TEST(MatrixTest, MultiplyFloat)
{
    rz::matrix m;
    fill(m);
    
    rz::matrix m1 = m * 2.0f;
    
    EXPECT_EQ(22.0f, m1.M11());
    EXPECT_EQ(24.0f, m1.M12());
    EXPECT_EQ(26.0f, m1.M13());
    EXPECT_EQ(28.0f, m1.M14());
    
    EXPECT_EQ(42.0f, m1.M21());
    EXPECT_EQ(44.0f, m1.M22());
    EXPECT_EQ(46.0f, m1.M23());
    EXPECT_EQ(48.0f, m1.M24());
    
    EXPECT_EQ(62.0f, m1.M31());
    EXPECT_EQ(64.0f, m1.M32());
    EXPECT_EQ(66.0f, m1.M33());
    EXPECT_EQ(68.0f, m1.M34());
    
    EXPECT_EQ(82.0f, m1.M41());
    EXPECT_EQ(84.0f, m1.M42());
    EXPECT_EQ(86.0f, m1.M43());
    EXPECT_EQ(88.0f, m1.M44());
}

TEST(MatrixTest, OperatorMultiplyFloat)
{
    rz::matrix m;
    fill(m);
    auto m_save(m);
    
    auto should_be(m);
    should_be.multiply(2.0f);
    
    rz::matrix m1 = m * 2.0f;
    
    EXPECT_TRUE(m1 == should_be);
    EXPECT_TRUE(m_save == m);
}

TEST(MatrixTest, MultiplyVector3)
{
    rz::matrix m;
    
    m.identity();
    m.multiply(2.0f);
    
    rz::vector3 v(rz::vector3_factory::one);
    
    auto v2 = m.multiply(v);
    
    EXPECT_TRUE(rz::vector3(2.0f, 2.0f, 2.0f) == v2);
}

TEST(MatrixTest, OperatorMultiplyVector3)
{
    rz::matrix m;
    
    m.identity();
    m.multiply(2.0f);
    
    auto m_save(m);
    
    rz::vector3 v(rz::vector3_factory::one);
    auto v_save(v);
    
    auto v2 = m * v;
    
    EXPECT_TRUE(rz::vector3(2.0f, 2.0f, 2.0f) == v2);
    EXPECT_TRUE(v_save == v);
    EXPECT_TRUE(m_save == m);
}

TEST(MatrixTest, Transpose)
{
    rz::matrix m;
    fill(m);
    m.transpose();
    
    EXPECT_EQ(11.0f, m.M11());
    EXPECT_EQ(21.0f, m.M12());
    EXPECT_EQ(31.0f, m.M13());
    EXPECT_EQ(41.0f, m.M14());
    
    EXPECT_EQ(12.0f, m.M21());
    EXPECT_EQ(22.0f, m.M22());
    EXPECT_EQ(32.0f, m.M23());
    EXPECT_EQ(42.0f, m.M24());
    
    EXPECT_EQ(13.0f, m.M31());
    EXPECT_EQ(23.0f, m.M32());
    EXPECT_EQ(33.0f, m.M33());
    EXPECT_EQ(43.0f, m.M34());
    
    EXPECT_EQ(14.0f, m.M41());
    EXPECT_EQ(24.0f, m.M42());
    EXPECT_EQ(34.0f, m.M43());
    EXPECT_EQ(44.0f, m.M44());
}

TEST(MatrixTest, Invert)
{
	float ff[] = { -1.0f, 3.0f, -3.0f, 0.0f, -6.0f, 5.0f, -5.0f, -3.0f, 1.0f };

	rz::matrix matrix(ff);

	matrix.invert();

	EXPECT_NEAR(3.0f / 2.0f, matrix.M11(), FLT_EPSILON);
	EXPECT_NEAR(1.0f, matrix.M12(), FLT_EPSILON);
	EXPECT_NEAR(-1.0f / 2.0f, matrix.M13(), FLT_EPSILON);
	EXPECT_NEAR(0.0f, matrix.M14(), FLT_EPSILON);

	EXPECT_NEAR(-25.0f / 6.0f, matrix.M21(), FLT_EPSILON * 10.0f); // todo crz: look at why this is a long way off
	EXPECT_NEAR(-8.0f / 3.0f, matrix.M22(), FLT_EPSILON);
	EXPECT_NEAR(5.0f / 6.0f, matrix.M23(), FLT_EPSILON);
	EXPECT_NEAR(0.0f, matrix.M24(), FLT_EPSILON);

	EXPECT_NEAR(-5.0f, matrix.M31(), FLT_EPSILON);
	EXPECT_NEAR(-3.0f, matrix.M32(), FLT_EPSILON);
	EXPECT_NEAR(1.0f, matrix.M33(), FLT_EPSILON);
	EXPECT_NEAR(0.0f, matrix.M34(), FLT_EPSILON);

	EXPECT_NEAR(0.0f, matrix.M41(), FLT_EPSILON);
	EXPECT_NEAR(0.0f, matrix.M42(), FLT_EPSILON);
	EXPECT_NEAR(0.0f, matrix.M43(), FLT_EPSILON);
	EXPECT_NEAR(1.0f, matrix.M44(), FLT_EPSILON);
}