/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core_quaternion.h"
#include "rz_core_matrix.h"
#include "rz_core_vector3.h"

#include "rz_core_math_templates.h"
#include "rz_core_macros.h"

// crz: based on Physics for Game Developers and possibly Noodles, so worry. No tests. Fix.

rz::quaternion::quaternion() :
	x(0.0f), y(0.0f), z(0.0f), w(1.0f)
{
}

rz::quaternion::quaternion(float x, float y, float z, float w) :
	x(x), y(y), z(z), w(w)
{

}

void rz::quaternion::identity()
{
	x = 0;
	y = 0;
	z = 0;
	w = 1;
}

rz::quaternion rz::quaternion::create_identity()
{
	rz::quaternion q;
	q.identity();
	return q;
}

rz::quaternion rz::quaternion::create_rotation_axis(rz::vector3 const &vec, float angle)
{
	rz::quaternion q;
	q.rotation_axis(vec, angle);
	return q;
}

rz::quaternion rz::quaternion::create_from_euler(rz::vector3 const &vec)
{
	rz::quaternion q;

	auto cyaw = cosf(0.5f * vec.z());
	auto cpitch = cosf(0.5f * vec.y());
	auto croll = cosf(0.5f * vec.x());
	auto syaw = sinf(0.5f * vec.z());
	auto spitch = sinf(0.5f * vec.y());
	auto sroll = sinf(0.5f * vec.x());

	q.w = cyaw * cpitch * croll + syaw * spitch * sroll;
	q.x = cyaw * cpitch * sroll - syaw * spitch * croll; 
	q.y = cyaw * spitch * croll + syaw * cpitch * sroll;
	q.z = syaw * cpitch * croll - cyaw * spitch * sroll;

	return q;
}

rz::quaternion rz::quaternion::create_from_points(vector3 const &from, rz::vector3 const &to)
{
	rz::quaternion q;
	rz::vector3 f(from);
	f.normalise();
	rz::vector3 t(to);
	t.normalise();

	rz::vector3 axis;

	auto dot = f.dot(t);

	// if pointing in opposite directions
	if (dot <= -1.0f)
	{
		axis = rz::vector3(1.0f, 0.0f, 0.0f);
		axis.cross(f);

		if (axis.length_squared() == 0.0f)
		{
			// try y
			axis = rz::vector3(0.0f, 1.0f, 0.0f);
			axis.cross(f);
		}

		// rotate 180
		axis.normalise();
		q = rz::quaternion::create_rotation_axis(axis, rz::PI_f);
	}
	// if -1 < dot < 1
	else if (dot < 1.0f)
	{
		// axis is cross, angle is acos(dot)
		f.cross(t);
		f.normalise();
		q = rz::quaternion::create_rotation_axis(f, acosf(dot));
	}
	else
	{
		q.identity(); // = new rz::quaternion();
	}
	return q;
}

void rz::quaternion::normalise()
{
	float	magnitude;
	double	temp;

	// Compute quaternion magnitude
	temp = w * w + x * x + y * y + z * z;
	magnitude = (float)sqrt(temp);

	// Divide each quaternion component by this magnitude
	if (magnitude != 0.0f)
	{
		magnitude = 1.0f / magnitude;
		x *= magnitude;
		y *= magnitude;
		z *= magnitude;
		w *= magnitude;
	}
}

void rz::quaternion::rotation_axis(vector3 const &vec, float angle)
{
	auto half_angle = angle / 2.0f;

	auto s = sinf(half_angle);
	x = vec.x() * s;
	y = vec.y() * s;
	z = vec.z() * s;
	w = cosf(half_angle);

	normalise();
}

void rz::quaternion::to_axis_angle(rz::vector3 &vec, float &angle) const
{
	float fCosAngle;
	float fSinAngle;
	double temp;

	fCosAngle = x;
	temp = 1.0f - fCosAngle * fCosAngle;
	angle = acosf(fCosAngle) * 2.0f;
	fSinAngle = (float)sqrt(temp);

	// This is to avoid a division by zero
	if (fabs(fSinAngle)<0.0005f)
	{
		fSinAngle = 1.0f;
	}

	vec = rz::vector3(x / fSinAngle, y / fSinAngle, z / fSinAngle);
}

rz::matrix rz::quaternion::to_matrix() const
{
	rz::matrix m;

	m.M11(1.0f - 2.0f * y * y - 2.0f * y * y);
	m.M12(2.0f * x * y - 2.0f * z * w);
	m.M13(2.0f * x * z + 2.0f * y * w);

	m.M21(2.0f * x * y + 2.0f * z * w);
	m.M22(1.0f - 2.0f * x * x - 2.0f * z * z);
	m.M23(2.0f * y * z - 2.0f * x * w);

	m.M31(2.0f * x * z - 2 * y * w);
	m.M32(2.0f * y * z + 2.0f * x * w);
	m.M33(1.0f - 2.0f * x * x - 2 * y * y);

	return m;
}

rz::vector3 rz::quaternion::to_euler() const
{
	auto w_squared = w * w;
	auto x_squared = x * x;
	auto y_squared = y * y;
	auto z_squared = z * z;

	auto r11 = w_squared + x_squared - y_squared - z_squared;
	auto r12 = 0.0f;
	auto r13 = 0.0f;
	auto r21 = 2 * (x * x + w * x);
	auto r31 = 2 * (y * y - w * y);
	auto r32 = 2 * (z * z + w * z);
	auto r33 = w_squared - x_squared - y_squared + z_squared;

	auto a = fabs(r31);
	if (a > 1.0f - rz::ONE_FLT_EPSILON)
	{
		r12 = 2 * (x * y - w * z);
		r13 = 2 * (x * z + w * y);

		return rz::vector3(0.0f, -rz::PI_OVER_TWO_f * r31 / a, atan2f(-r12, -r31*r13));
	}

	return rz::vector3(atan2f(r32, r33), asinf(-r31), atan2f(r21, r11));
}

void rz::quaternion::slerp(rz::quaternion &qIn, rz::quaternion const &q1, rz::quaternion const &q2, float t)
{
	float fCosine;
	float fAngle;
	float A;
	float B;

	if (t<0.0f || t>1.0f)
	{
		qIn.x = 0.0f;
		qIn.y = 0.0f;
		qIn.z = 0.0f;
		qIn.w = 1.0f;
	}

	// Find sine of Angle between rz::quaternion A and B (dot product between quaternion A and B)
	fCosine = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;

	if (fCosine < 0)
	{
		rz::quaternion qi;
		
		// <http://www.magic-software.com/Documentation/Quaternions.pdf>

		// "It is important to note that the quaternions q and -q represent
		// the same rotation... while either quaternion will do, the
		// interpolation methods require choosing one over the other.

		// "Although q1 and -q1 represent the same rotation, the values of
		// Slerp(t; q0, q1) and Slerp(t; q0,-q1) are not the same. It is
		// customary to choose the sign... on q1 so that... the angle
		// between q0 and q1 is acute. This choice avoids extra
		// spinning caused by the interpolated rotations."

		qi.x = -q2.x;
		qi.y = -q2.y;
		qi.z = -q2.z;
		qi.w = -q2.w;

		slerp(qIn, q1, qi, t);
		return;
	}

	fCosine = rz::min(fCosine, 1.0f);
	fAngle = acosf(fCosine);

	if (fabs(fAngle)<0.0005f)
	{
		qIn.x = q1.x;
		qIn.y = q1.y;
		qIn.z = q1.z;
		qIn.w = q1.w;
		return;
	}

	A = (float)(sinf((1.0f - t) * fAngle) / sinf(fAngle));
	B = (float)(sinf(t * fAngle) / sinf(fAngle));

	// Compute resulting quaternion
	qIn.x = A * q1.x + B * q2.x;
	qIn.y = A * q1.y + B * q2.y;
	qIn.z = A * q1.z + B * q2.z;
	qIn.w = A * q1.w + B * q2.w;

	qIn.normalise();
}

rz::quaternion rz::quaternion::slerp(rz::quaternion const &q1, rz::quaternion const &q2, float t)
{
	rz::quaternion q;
	slerp(q, q1, q2, t);
	return q;
}

rz::quaternion rz::quaternion::multiply(rz::quaternion const &q1, rz::quaternion const &q2)
{
	auto scalar = (q1.w * q2.w) - (q1.x * q2.x + q1.y * q2.y + q1.z * q2.z);

	auto cross = rz::vector3(q1.y * q2.z - q1.z * q2.y,
		q1.z * q2.x - q1.x * q2.z,
		q1.x * q2.y - q1.y * q2.x);

	auto x = (q1.w * q2.x) + (q2.w * q1.x) + cross.x();
	auto y = (q1.w * q2.y) + (q2.w * q1.y) + cross.y();
	auto z = (q1.w * q2.z) + (q2.w * q1.z) + cross.z();

	rz::quaternion q(x, y, z, scalar);
	q.normalise();
	
	return q;
}

