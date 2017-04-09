/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

// todo crz: integrate this
//#include <DirectXMath.h>

#include "rz_core_matrix.h"
#include "rz_core_macros.h"

#include <algorithm>

rz::matrix::matrix() : 
	F(M)
{
	identity();
}
		
rz::matrix::matrix(float f[9]) :
	F(M)
{
	identity();

	M[_11] = f[0];
	M[_12] = f[1];
	M[_13] = f[2];
	M[_21] = f[3];
	M[_22] = f[4];
	M[_23] = f[5];
	M[_31] = f[6];
	M[_32] = f[7];
	M[_33] = f[8];
}

rz::matrix::matrix(rz::matrix const &other) : 
	F(0)
{
    F = M;
	memcpy(F, other.F, sizeof(M));
}

rz::matrix &rz::matrix::identity()
{
	zero();
	M11(1.0);
	M22(1.0);
	M33(1.0);
	M44(1.0);

	return *this;
}

rz::matrix const &rz::matrix::operator=(rz::matrix const &other)
{
    F = M;
	memcpy(F, other.F, sizeof(M));

	return *this;
}

bool rz::matrix::equals(rz::matrix const &other) const
{
	// todo crz: memcmp possibly a tad faster?

	return 
		FLT_EQUALS(M11(), other.M11()) &&
		FLT_EQUALS(M12(), other.M12()) &&
		FLT_EQUALS(M13(), other.M13()) &&
		FLT_EQUALS(M14(), other.M14()) &&
		FLT_EQUALS(M21(), other.M21()) &&
		FLT_EQUALS(M22(), other.M22()) &&
		FLT_EQUALS(M23(), other.M23()) &&
		FLT_EQUALS(M24(), other.M24()) &&
		FLT_EQUALS(M31(), other.M31()) &&
		FLT_EQUALS(M32(), other.M32()) &&
		FLT_EQUALS(M33(), other.M33()) &&
		FLT_EQUALS(M34(), other.M34()) &&
		FLT_EQUALS(M41(), other.M41()) &&
		FLT_EQUALS(M42(), other.M42()) &&
		FLT_EQUALS(M43(), other.M43()) &&
		FLT_EQUALS(M44(), other.M44());
}

// todo crz
// Left handed rotation
// --           --   --           --   --                 --
// |  1   0   0  |   |  cy  0   sy |   |  cy    0     sy   |
// |  0   cx -sx | * |  0   1   0  | = |  sxsy  cx   -sxcy |
// |  0   sx  cx |   | -sy  0   cy |   | -cxsy  sx    cxcy |
// --           --   --           --   --                 --
//
// X*Y Rot rz::matrix        * Z Rot rz::matrix    = X*Y*Z Rot rz::matrix (the result)
// --                 --   --           --   --                               --
// |  cy    0     sy   |   |  cz -sz  0  |   |  cycz        -cysz         sy   |
// |  sxsy  cx   -sxcy | * |  sz  cz  0  | = |  sxsycz+cxsz -sxsysz+cxcz -sxcy |
// | -cxsy  sx    cxcy |   |  0   0   1  |   | -cxsycz+sxsz  cxsysz+sxcz  cxcy |
// --                 --   --           --   --                               --
//

#ifdef DXMATH
void Matrix4Mul(const float* src_mat_1, const float* src_mat_2, float* dst_mat)
{
	DirectX::XMMATRIX m1 = DirectX::XMLoadFloat4x4((DirectX::XMFLOAT4X4*)src_mat_1);
	DirectX::XMMATRIX m2 = DirectX::XMLoadFloat4x4((DirectX::XMFLOAT4X4*)src_mat_2);
	DirectX::XMMATRIX dst;

	dst = DirectX::XMMatrixMultiply(m1, m2);
	DirectX::XMStoreFloat4x4((DirectX::XMFLOAT4X4*)dst_mat, dst);
}
#endif

rz::matrix &rz::matrix::multiply(rz::matrix const &other)
{
#ifdef DXMATH
	Matrix4Mul(&M11, &matrix1.M11, &M11);
#else
    rz::matrix m(*this);
    
    M11(m.M11() * other.M11() + m.M12() * other.M21() + m.M13() * other.M31() + m.M14() * other.M41());
    M12(m.M11() * other.M12() + m.M12() * other.M22() + m.M13() * other.M32() + m.M14() * other.M42());
    M13(m.M11() * other.M13() + m.M12() * other.M23() + m.M13() * other.M33() + m.M14() * other.M43());
    M14(m.M11() * other.M14() + m.M12() * other.M24() + m.M13() * other.M34() + m.M14() * other.M44());

    M21(m.M21() * other.M11() + m.M22() * other.M21() + m.M23() * other.M31() + m.M24() * other.M41());
    M22(m.M21() * other.M12() + m.M22() * other.M22() + m.M23() * other.M32() + m.M24() * other.M42());
    M23(m.M21() * other.M13() + m.M22() * other.M23() + m.M23() * other.M33() + m.M24() * other.M43());
    M24(m.M21() * other.M14() + m.M22() * other.M24() + m.M23() * other.M34() + m.M24() * other.M44());
    
    M31(m.M31() * other.M11() + m.M32() * other.M21() + m.M33() * other.M31() + m.M34() * other.M41());
    M32(m.M31() * other.M12() + m.M32() * other.M22() + m.M33() * other.M32() + m.M34() * other.M42());
    M33(m.M31() * other.M13() + m.M32() * other.M23() + m.M33() * other.M33() + m.M34() * other.M43());
    M34(m.M31() * other.M14() + m.M32() * other.M24() + m.M33() * other.M34() + m.M34() * other.M44());
    
    M41(m.M41() * other.M11() + m.M42() * other.M21() + m.M43() * other.M31() + m.M44() * other.M41());
    M42(m.M41() * other.M12() + m.M42() * other.M22() + m.M43() * other.M32() + m.M44() * other.M42());
    M43(m.M41() * other.M13() + m.M42() * other.M23() + m.M43() * other.M33() + m.M44() * other.M43());
    M44(m.M41() * other.M14() + m.M42() * other.M24() + m.M43() * other.M34() + m.M44() * other.M44());
    
#endif
	return *this;
}

rz::vector3 rz::matrix::multiply(rz::vector3 const &v) const
{
	// todo crz: rz_platform optimisation
	float x = M11() * v.x() + M12() * v.y() + M13() * v.z() + M41();
	float y = M21() * v.x() + M22() * v.y() + M23() * v.z() + M42();
	float z = M31() * v.x() + M32() * v.y() + M33() * v.z() + M43();

	return rz::vector3(x, y, z);
}

rz::matrix &rz::matrix::multiply(float f)
{
	std::for_each(std::begin(M), std::end(M), [f](float &a) { a *= f; });

	return *this;
}

static void XNAInvert(float* in, float* out)
{
	float num  = in[10] * in[15] - in[11] * in[14];
	float num2 = in[9] * in[15] - in[11] * in[13];
	float num3 = in[9] * in[14] - in[10] * in[13];
	float num4 = in[8] * in[15] - in[11] * in[12];
	float num5 = in[8] * in[14] - in[10] * in[12];
	float num6 = in[8] * in[13] - in[9] * in[12];
	float num7 = in[5] * num - in[6] * num2 + in[7] * num3;
	float num8 = -(in[4] * num - in[6] * num4 + in[7] * num5);
	float num9 = in[4] * num2 - in[5] * num4 + in[7] * num6;
	float num10 = -(in[4] * num3 - in[5] * num5 + in[6] * num6);
	float num11 = 1.0f / (in[0] * num7 + in[1] * num8 + in[2] * num9 + in[3] * num10);

	out[0] = num7 * num11;
	out[4] = num8 * num11;
	out[8] = num9 * num11;
	out[12] = num10 * num11;
	out[1] = -(in[1] * num - in[2] * num2 + in[3] * num3) * num11;
	out[5] = (in[0] * num - in[2] * num4 + in[3] * num5) * num11;
	out[9] = -(in[0] * num2 - in[1] * num4 + in[3] * num6) * num11;
	out[13] = (in[0] * num3 - in[1] * num5 + in[2] * num6) * num11;

	float num12 = in[6] * in[15] - in[7] * in[14];
	float num13 = in[5] * in[15] - in[7] * in[13];
	float num14 = in[5] * in[14] - in[6] * in[13];
	float num15 = in[4] * in[15] - in[7] * in[12];
	float num16 = in[4] * in[14] - in[6] * in[12];
	float num17 = in[4] * in[13] - in[5] * in[12];

	out[2] = (in[1] * num12 - in[2] * num13 + in[3] * num14) * num11;
	out[6] = -(in[0] * num12 - in[2] * num15 + in[3] * num16) * num11;
	out[10] = (in[0] * num13 - in[1] * num15 + in[3] * num17) * num11;
	out[14] = -(in[0] * num14 - in[1] * num16 + in[2] * num17) * num11;

	float num18 = in[6] * in[11] - in[7] * in[10];
	float num19 = in[5] * in[11] - in[7] * in[9];
	float num20 = in[5] * in[10] - in[6] * in[9];
	float num21 = in[4] * in[11] - in[7] * in[8];
	float num22 = in[4] * in[10] - in[6] * in[8];
	float num23 = in[4] * in[9] - in[5] * in[8];

	out[3] = -(in[1] * num18 - in[2] * num19 + in[3] * num20) * num11;
	out[7] = (in[0] * num18 - in[2] * num21 + in[3] * num22) * num11;
	out[11] = -(in[0] * num19 - in[1] * num21 + in[3] * num23) * num11;
	out[15] = (in[0] * num20 - in[1] * num22 + in[2] * num23) * num11;
}

rz::matrix &rz::matrix::invert()
{
    float temp[sizeof(M) / sizeof(float)];

	XNAInvert(M, temp);
	memcpy(M, temp, sizeof(M));

	M[ 3] = 0.0f;
	M[ 7] = 0.0f;
	M[11] = 0.0f;
	M[15] = 1.0f;

	return *this;
}

// todo crz: improve this
rz::matrix &rz::matrix::transpose()
{
    float temp[16];

	temp[ 0] = F[ 0];	temp[ 4] = F[ 1];	temp[ 8] = F[ 2];	temp[12] = F[ 3];
	temp[ 1] = F[ 4];	temp[ 5] = F[ 5];	temp[ 9] = F[ 6];	temp[13] = F[ 7];
	temp[ 2] = F[ 8];	temp[ 6] = F[ 9];	temp[10] = F[10];	temp[14] = F[11];
	temp[ 3] = F[12];	temp[ 7] = F[13];	temp[11] = F[14];	temp[15] = F[15];

	memcpy(M, &temp, sizeof(M));

	return *this;
}

rz::matrix &rz::matrix::zero()
{
	memset(F, 0, sizeof(M));

	return *this;
}
