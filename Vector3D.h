#pragma once
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>

class Vector3D
{
public:
	Vector3D() : m_x(0), m_y(0), m_z(0)
	{
	}

	Vector3D(float x, float y, float z) : m_x(x), m_y(y), m_z(z)
	{
	}

	Vector3D(const Vector3D& vector) : m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z)
	{
	}

	Vector3D(const physx::PxVec3& vector) : m_x(vector.x), m_y(vector.y), m_z(vector.z)
	{
	}

	static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta)
	{
		Vector3D v;
		v.m_x = start.m_x * (1.0f - delta) + end.m_x * (delta);
		v.m_y = start.m_y * (1.0f - delta) + end.m_y * (delta);
		v.m_z = start.m_z * (1.0f - delta) + end.m_z * (delta);
		return v;
	}

	Vector3D operator *(float num)
	{
		return Vector3D(m_x * num, m_y * num, m_z * num);
	}

	Vector3D operator +(const Vector3D& vec)
	{
		return Vector3D(m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z);
	}

	Vector3D operator +(const physx::PxVec3& vec)
	{
		return Vector3D(m_x + vec.x, m_y + vec.y, m_z + vec.z);
	}

	~Vector3D()
	{
	}

public:
	float m_x = 0;
	float m_y = 0;
	float m_z = 0;
};