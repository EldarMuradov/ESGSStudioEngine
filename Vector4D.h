#pragma once
#include "Vector3D.h"
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>

class Vector4D
{
public:
	Vector4D() : m_x(0), m_y(0), m_z(0), m_w(0)
	{
	}

	Vector4D(float x, float y, float z,float w) : m_x(x), m_y(y), m_z(z), m_w(w)
	{
	}

	Vector4D(const Vector4D& vector) : m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z), m_w(vector.m_w)
	{
	}

	Vector4D(const physx::PxVec4& vector) : m_x(vector.x), m_y(vector.y), m_z(vector.z), m_w(vector.w)
	{
	}

	Vector4D(const Vector3D& vector) : m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z), m_w(1.0)
	{
	}

	Vector4D(const physx::PxVec3& vector) : m_x(vector.x), m_y(vector.y), m_z(vector.z), m_w(1.0)
	{
	}

	void cross(Vector4D& v1, Vector4D& v2, Vector4D& v3)
	{
		this->m_x = v1.m_y * (v2.m_z * v3.m_w - v3.m_z * v2.m_w) - v1.m_z * (v2.m_y * v3.m_w - v3.m_y * v2.m_w) + v1.m_w * (v2.m_y * v3.m_z - v2.m_z * v3.m_y);
		this->m_y = -(v1.m_x * (v2.m_z * v3.m_w - v3.m_z * v2.m_w) - v1.m_z * (v2.m_x * v3.m_w - v3.m_x * v2.m_w) + v1.m_w * (v2.m_x * v3.m_z - v3.m_x * v2.m_z));
		this->m_z = v1.m_x * (v2.m_y * v3.m_w - v3.m_y * v2.m_w) - v1.m_y * (v2.m_x * v3.m_w - v3.m_x * v2.m_w) + v1.m_w * (v2.m_x * v3.m_y - v3.m_x * v2.m_y);
		this->m_w = -(v1.m_x * (v2.m_y * v3.m_z - v3.m_y * v2.m_z) - v1.m_y * (v2.m_x * v3.m_z - v3.m_x * v2.m_z) + v1.m_z * (v2.m_x * v3.m_y - v3.m_x * v2.m_y));
	}

	/*Vector4D multipleByMatrix4x4(Matrix4x4& matrix)
	{
		float x, y, z, w;

		x = m_x * matrix.m_mat[0][0] +
			m_y * matrix.m_mat[0][1] +
			m_z * matrix.m_mat[0][2] +
			m_w * matrix.m_mat[0][3];

		y = m_x * matrix.m_mat[1][0] +
			m_y * matrix.m_mat[1][1] +
			m_z * matrix.m_mat[1][2] +
			m_w * matrix.m_mat[1][3];

		z = m_x * matrix.m_mat[2][0] +
			m_y * matrix.m_mat[2][1] +
			m_z * matrix.m_mat[2][2] +
			m_w * matrix.m_mat[2][3];

		w = m_x * matrix.m_mat[3][0] +
			m_y * matrix.m_mat[3][1] +
			m_z * matrix.m_mat[3][2] +
			m_w * matrix.m_mat[3][3];

		return Vector4D(x, y, z, w);
	}*/
	
	~Vector4D()
	{
	}

public:
	float m_x = 0;
	float m_y = 0;
	float m_z = 0;
	float m_w = 0;
};