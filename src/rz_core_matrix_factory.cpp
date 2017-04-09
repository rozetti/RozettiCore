/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core_matrix_factory.h"
#include "rz_core_vector3_factory.h"

rz::matrix const rz::matrix_factory::identity(rz::matrix_factory::create_identity());

rz::matrix rz::matrix_factory::create_identity()
{
	rz::matrix m;
	return m.identity();
}

rz::matrix rz::matrix_factory::create_zero()
{
	rz::matrix m;
	return m.zero();
}

rz::matrix rz::matrix_factory::create_rotation(rz::vector3 const &axis, float radians)
{
	rz::matrix m;

	float c = std::cos(radians);
	float s = std::sin(radians);
	float t = 1.0f - c;

	m.M11((t * axis.x() * axis.x()) + c);
	m.M12((t * axis.x() * axis.y()) - (s * axis.z()));
	m.M13((t * axis.x() * axis.z()) + (s * axis.y()));

	m.M21((t * axis.x() * axis.y()) + (s * axis.z()));
	m.M22((t * axis.y() * axis.y()) + c);
	m.M23((t * axis.y() * axis.z()) - (s * axis.x()));

	m.M31((t * axis.x() * axis.z()) - (s * axis.y()));
	m.M32((t * axis.y() * axis.z()) + (s * axis.x()));
	m.M33((t * axis.z() * axis.z()) + c);

	return m;
}

rz::matrix rz::matrix_factory::create_rotation_around_x(float radians) 
{ 
	return rz::matrix_factory::create_rotation(rz::vector3_factory::right, radians); 
}

rz::matrix rz::matrix_factory::create_rotation_around_y(float radians) 
{ 
	return rz::matrix_factory::create_rotation(rz::vector3_factory::up, radians); 
}

rz::matrix rz::matrix_factory::create_rotation_around_z(float radians) 
{ 
	return rz::matrix_factory::create_rotation(rz::vector3_factory::back, radians); 
}

rz::matrix rz::matrix_factory::create_scaling(rz::vector3 const &scale)
{
	rz::matrix m;
	m.zero();

	m.M11(scale.x());
	m.M22(scale.y());
	m.M33(scale.z());
	m.M44(1.0f);

	return m;
}

rz::matrix rz::matrix_factory::create_translation(rz::vector3 const &translation)
{
	rz::matrix m;
	
	m.M41(translation.x());
	m.M42(translation.y());
	m.M43(translation.z());

	return m;
}

// todo crz: nothing below here is tested

rz::matrix rz::matrix_factory::create(rz::vector3 const &rotation, rz::vector3 const &scale, rz::vector3 const &translation)
{
	rz::matrix m;

	float cx = cosf(rotation.x());
	float sx = sinf(rotation.x());

	float cy = cosf(rotation.y());
	float sy = sinf(rotation.y());

	float cz = cosf(rotation.z());
	float sz = sinf(rotation.z());

	m.M11(cy * cz * scale.x());
	m.M12(-cy * sz * scale.y());
	m.M13(sy * scale.z());

	m.M21(sx * sy * cz + cx * sz * scale.x());
	m.M22(-sx * sy * sz + cx * cz * scale.y());
	m.M23(-sx * cy * scale.z());

	m.M31(-cx * sy * cz + sx * sz * scale.x());
	m.M32(cx * sy * sz + sx * cz * scale.y());
	m.M33(cx * cy * scale.z());

	m.M41(translation.x());
	m.M42(translation.y());
	m.M43(translation.z());

	return m;
}

rz::matrix rz::matrix_factory::create_rotation_from_pitch_yaw_roll(rz::vector3 const &pyr)
{
	return rz::matrix_factory::create(pyr, rz::vector3_factory::one, rz::vector3_factory::zero);
}

rz::matrix rz::matrix_factory::create_look_at(rz::vector3 const &eye_position, rz::vector3 const &eye_target, rz::vector3 const &eye_up)
{
	rz::matrix m;

	rz::vector3 eye_direction = eye_target - eye_position;
	eye_direction.normalise();

	rz::vector3 up = eye_up;
	up.normalise();

    rz::vector3 s = rz::vector3(eye_direction).cross(up);
    rz::vector3 u = rz::vector3::cross(s, eye_direction);

	m.M11(s.x());
	m.M12(u.x());
	m.M13(-eye_direction.x());

	m.M21(s.y());
	m.M22(u.y());
	m.M23(-eye_direction.y());

	m.M31(s.z());
	m.M32(u.z());
	m.M33(-eye_direction.z());

	m.M41(eye_position.x() * -m.M11() + eye_position.y() * -m.M21() + eye_position.z() * -m.M31());
	m.M42(eye_position.x() * -m.M12() + eye_position.y() * -m.M22() + eye_position.z() * -m.M32());
	m.M43(eye_position.x() * -m.M13() + eye_position.y() * -m.M23() + eye_position.z() * -m.M33());

	return m;
}

rz::matrix rz::matrix_factory::create_orthographic_projection(float left, float right, float top, float bottom, float _near, float _far)
{
	rz::matrix m;
	m.zero();

	m.M11(2.0f / (right - left));

	m.M22(2.0f / (top - bottom));

	m.M33(-2.0f / (_far - _near));

	m.M41((left + right) / (left -right));
	m.M42((bottom + top) / (bottom - top));
	m.M43((_near + _far) / (_near - _far));
	m.M44(1);

	return m;
}

rz::matrix rz::matrix_factory::create_perspective_projection(float fov, float aspect_ratio, float _near, float _far)
{
	rz::matrix m;
	m.zero();

	float f = 1.0f / (float)std::tan(fov * 0.5f);
	float n = 1.0f / (_near - _far);

	m.M11(f / aspect_ratio);

	m.M22(f);

	m.M33((_far + _near) * n);

	m.M43((2.0f * _far * _near) * n);
	m.M44(1);

	return m;
}

