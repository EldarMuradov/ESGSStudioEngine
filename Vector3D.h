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

	Vector3D cross(const Vector3D& rhs)
	{
		return Vector3D(
			m_y * rhs.m_z - m_z * rhs.m_y,
			m_z * rhs.m_x - m_x * rhs.m_z,
			m_x * rhs.m_y - m_y * rhs.m_x);
	}

	float magnitude() 
	{ 
		return (float)sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
	}

	void normalize()
	{
		float mag = magnitude();
		if (mag > 0.00001f)
		{
			m_x /= mag;
			m_y /= mag;
			m_z /= mag;
		}
		else
		{
			m_x = 0; 
			m_y = 0;
			m_z = 0;
		}
	}

	Vector3D normalize(Vector3D value)
	{
		float mag = value.magnitude();
		if (mag > 0.00001f)
		{
			value.m_x /= mag;
			value.m_y /= mag;
			value.m_z /= mag;
		}
		else
		{
			value.m_x = 0;
			value.m_y = 0;
			value.m_z = 0;
		}
		return Vector3D(value.m_x, value.m_y, value.m_z);
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