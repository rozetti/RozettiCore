#include "tests.h"

TEST(MatrixFactoryTest, CreateZero)
{
    rz::matrix const &m1 = rz::matrix_factory::create_zero();
    
    rz::matrix m2;
    m2.zero();
    
    EXPECT_TRUE(m1 == m2);
}

TEST(MartixFactoryTest, Identity)
{
    rz::matrix m;
    m.identity();
    
    EXPECT_TRUE(rz::matrix_factory::identity == m);
}

TEST(MatrixFactoryTest, CreateIdentity)
{
    rz::matrix const &m1 = rz::matrix_factory::create_identity();
    
    rz::matrix m2;
    m2.identity();
    
    EXPECT_TRUE(m1 == m2);
}

TEST(MatrixFactoryTest, CreateScaling)
{
    auto v_scaled = rz::vector3_factory::one * 2.0f;
    
    auto m_scale = rz::matrix_factory::create_scaling(v_scaled);
    
    auto v1(rz::vector3_factory::one);
    rz::vector3 v2(m_scale * v1);
    
    EXPECT_TRUE(v_scaled == v2);
}

TEST(MatrixFactoryTest, CreateRotationAroundX)
{
    rz::vector3 v(0.0f, 1.0f, 0.0f);
    
    auto m = rz::matrix_factory::create_rotation_around_x(rz::PI_OVER_TWO_f);
    
    auto v2 = m * v;
    
    EXPECT_TRUE(rz::vector3(0.0f, 0.0f, 1.0f) == v2);
}

TEST(MatrixFactoryTest, CreateRotationAroundY)
{
    rz::vector3 v(1.0f, 0.0f, 0.0f);
    
    auto m = rz::matrix_factory::create_rotation_around_y(rz::PI_OVER_TWO_f);
    
    auto v2 = m * v;
    
    EXPECT_TRUE(rz::vector3(0.0f, 0.0f, -1.0f) == v2);
}

TEST(MatrixFactoryTest, CreateRotationAroundZ)
{
    rz::vector3 v(1.0f, 0.0f, 0.0f);
    
    auto m = rz::matrix_factory::create_rotation_around_z(rz::PI_OVER_TWO_f);
    
    auto v2 = m * v;
    
    EXPECT_TRUE(rz::vector3(0.0f, 1.0f, 0.0f) == v2);
}

TEST(MatrixFactoryTest, CreateTranslation)
{
    auto v = rz::vector3_factory::zero;
    
    auto m = rz::matrix_factory::create_translation(rz::vector3(1.0f, 1.0f, 1.0f));
    
    auto v2 = m * v;
    
    EXPECT_TRUE(v2 == rz::vector3_factory::one);
}
