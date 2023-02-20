#pragma once
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>

class Vector2D
{
public:
	Vector2D() : m_x(0), m_y(0)
	{
	}

	Vector2D(float x, float y) : m_x(x), m_y(y)
	{
	}

	Vector2D(const Vector2D& vector) : m_x(vector.m_x), m_y(vector.m_y)
	{
	}

	Vector2D(const physx::PxVec2& vector) : m_x(vector.x), m_y(vector.y)
	{
	}

	Vector2D operator *(float num)
	{
		return Vector2D(m_x * num, m_y * num);
	}

	Vector2D operator +(const Vector2D& vec) 
	{
		return Vector2D(m_x + vec.m_x, m_y + vec.m_y);
	}

	Vector2D operator +(const physx::PxVec2& vec)
	{
		return Vector2D(m_x + vec.x, m_y + vec.y);
	}

	~Vector2D()
	{
	}

public:
	float m_x = 0;
	float m_y = 0;
};