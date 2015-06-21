/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include "rz_core_vector3.h"
#include <vector>

// todo crz: policy for create zero'd or identity

namespace rz
{
	class matrix
	{
	public:
        enum { _11 = 0, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44 };
        
		float M[16];
		float *F;

	public:
		rz::matrix();
		rz::matrix(float f[9]);
		rz::matrix(rz::matrix const &other);

        inline void M11(float f) { M[_11] = f; }
        inline void M12(float f) { M[_12] = f; }
        inline void M13(float f) { M[_13] = f; }
        inline void M14(float f) { M[_14] = f; }
        inline void M21(float f) { M[_21] = f; }
        inline void M22(float f) { M[_22] = f; }
        inline void M23(float f) { M[_23] = f; }
        inline void M24(float f) { M[_24] = f; }
        inline void M31(float f) { M[_31] = f; }
        inline void M32(float f) { M[_32] = f; }
        inline void M33(float f) { M[_33] = f; }
        inline void M34(float f) { M[_34] = f; }
        inline void M41(float f) { M[_41] = f; }
        inline void M42(float f) { M[_42] = f; }
        inline void M43(float f) { M[_43] = f; }
        inline void M44(float f) { M[_44] = f; }

        inline float M11() const { return M[_11]; }
        inline float M12() const { return M[_12]; }
        inline float M13() const { return M[_13]; }
        inline float M14() const { return M[_14]; }
        inline float M21() const { return M[_21]; }
        inline float M22() const { return M[_22]; }
        inline float M23() const { return M[_23]; }
        inline float M24() const { return M[_24]; }
        inline float M31() const { return M[_31]; }
        inline float M32() const { return M[_32]; }
        inline float M33() const { return M[_33]; }
        inline float M34() const { return M[_34]; }
        inline float M41() const { return M[_41]; }
        inline float M42() const { return M[_42]; }
        inline float M43() const { return M[_43]; }
        inline float M44() const { return M[_44]; }
            
		rz::matrix const &operator=(rz::matrix const &other);
		bool operator==(rz::matrix const &other) const { return equals(other); }
		bool operator!=(rz::matrix const &other) const { return !equals(other); }
		
		rz::matrix const operator*(rz::matrix const &other) const { return rz::matrix(*this).multiply(other); }
		rz::vector3 const operator*(rz::vector3 const &other) const { return multiply(other); }
		rz::matrix const operator*(float f) const { return rz::matrix(*this).multiply(f); }
		
		rz::vector3 up() const { return rz::vector3(M[_12], M[_22], M[_32]); }
		rz::vector3 down() const { return rz::vector3(-M[_12], -M[_22], -M[_32]); }
		rz::vector3 right() const { return rz::vector3(M[_11], M[_21], M[_31]); }
		rz::vector3 left() const { return rz::vector3(-M[_11], -M[_21], -M[_31]); }
		rz::vector3 back() const { return rz::vector3(M[_13], M[_23], M[_33]); }
		rz::vector3 forward() const { return rz::vector3(-M[_13], -M[_23], -M[_33]); }

		rz::matrix &identity();
		rz::matrix &zero();

		rz::matrix &multiply(rz::matrix const &other);
		rz::vector3 multiply(rz::vector3 const &v) const;
		rz::matrix &multiply(float f);
		rz::matrix &invert();
		rz::matrix &transpose();

	private:
		bool equals(rz::matrix const &other) const;
	};
}
