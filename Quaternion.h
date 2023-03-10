#pragma once
#include "Vector3D.h"
#include <cmath>
#include "Matrix4x4.h"
#define MIN(a, b) ((a) < (b) ? (a) : (b))

class Quaternion 
{
public:
	Quaternion(float x, float y, float z, float w) 
	{
		m_x = x;
		m_y = y;
		m_z = z;
		m_w = w;
	}

	Quaternion()
	{
		m_x = 0;
		m_y = 0;
		m_z = 0;
		m_w = 1;
	}

	void set(float x, float y, float z, float w)
	{
		m_x = x;
		m_y = y;
		m_z = z;
		m_w = w;
	}

	void set(Quaternion q)
	{
		m_x = q.m_x;
		m_y = q.m_y;
		m_z = q.m_z;
		m_w = q.m_w;
	}

	Quaternion inverse(Quaternion q)
	{
		return Quaternion(-q.m_x, -q.m_y, -q.m_z, q.m_w);
	}

	static Quaternion identity() 
	{
		return Quaternion(0, 0, 0, 1);
	}

	Quaternion operator *(Quaternion rhs)
	{
		return Quaternion(
			m_w * rhs.m_x + m_x * rhs.m_w + m_y * rhs.m_z - m_z * rhs.m_y,
			m_w * rhs.m_y + m_y * rhs.m_w + m_z * rhs.m_x - m_x * rhs.m_z,
			m_w * rhs.m_z + m_z * rhs.m_w + m_x * rhs.m_y - m_y * rhs.m_x,
			m_w * rhs.m_w - m_x * rhs.m_x - m_y * rhs.m_y - m_z * rhs.m_z);
	}

	Quaternion operator *(float num)
	{
		return Quaternion(m_x * num, m_y * num, m_z * num, m_w * num);
	}

	Quaternion operator /(float num)
	{
		return Quaternion(m_x / num, m_y / num, m_z / num, m_w / num);
	}

	Vector3D operator *(Vector3D point)
	{
		float x = m_x * 2;
		float y = m_y * 2;
		float z = m_z * 2;
		float xx = m_x * x;
		float yy = m_y * y;
		float zz = m_z * z;
		float xy = m_x * y;
		float xz = m_x * z;
		float yz = m_y * z;
		float wx = m_w * x;
		float wy = m_w * y;
		float wz = m_w * z;

		Vector3D res;
		res.m_x = (1 - (yy + zz)) * point.m_x + (xy - wz) * point.m_y + (xz + wy) * point.m_z;
		res.m_y = (xy + wz) * point.m_x + (1 - (xx + zz)) * point.m_y + (yz - wx) * point.m_z;
		res.m_z = (xz - wy) * point.m_x + (yz + wx) * point.m_y + (1 - (xx + yy)) * point.m_z;
		return res;
	}

	bool isEqualUsingDot(float dot)
	{
		// Returns false in the presence of NaN values.
		return dot > 1.0f - m_epsilon;
	}

	bool operator==(const Quaternion& rhs)
	{
		return isEqualUsingDot(dot(rhs));
	}

	bool operator!=(const Quaternion& rhs)
	{
		// Returns true in the presence of NaN values.
		return !(*this == rhs);
	}

	float dot(const Quaternion& a)
	{
		return a.m_x * m_x + a.m_y * m_y + a.m_z * m_z + a.m_w * m_w;
	}

	float angle(const Quaternion& a)
	{
		float d = MIN(abs(dot(a)), 1.0f);
		return isEqualUsingDot(d) ? 0.0f : acos(d) * 2.0f * m_rad2deg;
	}

	static Vector3D internalMakePositive(Vector3D euler)
	{
		float negativeFlip = -0.0001f * 57.29578f;
		float positiveFlip = 360.0f + negativeFlip;

		if (euler.m_x < negativeFlip)
			euler.m_x += 360.0f;
		else if (euler.m_x > positiveFlip)
			euler.m_x -= 360.0f;

		if (euler.m_y < negativeFlip)
			euler.m_y += 360.0f;
		else if (euler.m_y > positiveFlip)
			euler.m_y -= 360.0f;

		if (euler.m_z < negativeFlip)
			euler.m_z += 360.0f;
		else if (euler.m_z > positiveFlip)
			euler.m_z -= 360.0f;

		return euler;
	}

	Quaternion rotateTowards(const Quaternion& to, float maxDegreesDelta)
	{
		float ang = angle(to);
		if (ang == 0.0f) 
			return to;
		return slerp(to, MIN(1.0f, maxDegreesDelta / ang));
	}

	void setLookRotation(Vector3D view)
	{
		Vector3D up = Vector3D(0, 1, 0);
		setLookRotation(view, up);
	}

	void setLookRotation(Vector3D view, Vector3D up)
	{
		Quaternion q = lookRotation(view, up);
		set(q);
	}

	Quaternion slerp(Quaternion q, float t)
	{
		Quaternion ret;

		float fCos = dot(q);

		if ((1.0f + fCos) > 0.00001f)
		{
			float fCoeff0, fCoeff1;

			if ((1.0f - fCos) > 0.00001f)
			{
				float omega = acos(fCos);
				float invSin = 1.0f / sin(omega);
				fCoeff0 = sin((1.0f - t) * omega) * invSin;
				fCoeff1 = sin(t * omega) * invSin;
			}
			else
			{
				fCoeff0 = 1.0f - t;
				fCoeff1 = t;
			}

			ret.m_x = fCoeff0 * m_x + fCoeff1 * q.m_x;
			ret.m_y = fCoeff0 * m_y + fCoeff1 * q.m_y;
			ret.m_z = fCoeff0 * m_z + fCoeff1 * q.m_z;
			ret.m_w = fCoeff0 * m_w + fCoeff1 * q.m_w;
		}
		else
		{
			float fCoeff0 = sin((1.0f - t) * m_pi * 0.5f);
			float fCoeff1 = sin(t * m_pi * 0.5f);

			ret.m_x = fCoeff0 * m_x - fCoeff1 * m_y;
			ret.m_y = fCoeff0 * m_y + fCoeff1 * m_x;
			ret.m_z = fCoeff0 * m_z - fCoeff1 * m_w;
			ret.m_w = m_z;
		}

		return ret;
	}

	Quaternion lookRotation(Vector3D forward, Vector3D up)
	{
		forward.normalize();

		Vector3D vector = forward.normalize(forward);
		Vector3D vector2 = up.normalize(up.cross(vector));
		Vector3D vector3 = vector.cross(vector2);
		float m00 = vector2.m_x;
		float m01 = vector2.m_y;
		float m02 = vector2.m_z;
		float m10 = vector3.m_x;
		float m11 = vector3.m_y;
		float m12 = vector3.m_z;
		float m20 = vector.m_x;
		float m21 = vector.m_y;
		float m22 = vector.m_z;

		float num8 = (m00 + m11) + m22;
		Quaternion quaternion = Quaternion();
		if (num8 > 0)
		{
			float num = (float)sqrt(num8 + 1);
			quaternion.m_w = num * 0.5f;
			num = 0.5f / num;
			quaternion.m_x = (m12 - m21) * num;
			quaternion.m_y = (m20 - m02) * num;
			quaternion.m_z = (m01 - m10) * num;
			return quaternion;
		}
		if ((m00 >= m11) && (m00 >= m22))
		{
			float num7 = (float)sqrt(((1 + m00) - m11) - m22);
			float num4 = 0.5f / num7;
			quaternion.m_x = 0.5f * num7;
			quaternion.m_y = (m01 + m10) * num4;
			quaternion.m_z = (m02 + m20) * num4;
			quaternion.m_w = (m12 - m21) * num4;
			return quaternion;
		}
		if (m11 > m22)
		{
			float num6 = (float)sqrt(((1 + m11) - m00) - m22);
			float num3 = 0.5f / num6;
			quaternion.m_x = (m10 + m01) * num3;
			quaternion.m_y = 0.5f * num6;
			quaternion.m_z = (m21 + m12) * num3;
			quaternion.m_w = (m20 - m02) * num3;
			return quaternion;
		}
		float num5 = (float)sqrt(((1 + m22) - m00) - m11);
		float num2 = 0.5f / num5;
		quaternion.m_x = (m20 + m02) * num2;
		quaternion.m_y = (m21 + m12) * num2;
		quaternion.m_z = 0.5f * num5;
		quaternion.m_w = (m01 - m10) * num2;
		return quaternion;
	}

	static Quaternion eulerToQuaternion(Vector3D someEulerAngles)
	{
		float cX = (cos(someEulerAngles.m_x / 2.0f));
		float sX = (sin(someEulerAngles.m_x / 2.0f));

		float cY = (cos(someEulerAngles.m_y / 2.0f));
		float sY = (sin(someEulerAngles.m_y / 2.0f));

		float cZ = (cos(someEulerAngles.m_z / 2.0f));
		float sZ = (sin(someEulerAngles.m_z / 2.0f));

		Quaternion qX = Quaternion(sX, 0.0f, 0.0f, cX);
		Quaternion qY = Quaternion(0.0f, sY, 0.0f, cY);
		Quaternion qZ = Quaternion(0.0f, 0.0f, sZ, cZ);

		Quaternion q = (qY * qX) * qZ;
		return q;
	}

	static Quaternion euler(Vector3D euler) 
	{ 
		return fromEulerRad(euler * 0.01745329251f);
	}

	Quaternion normalizeSafe(Quaternion q)
	{
		float mag = magnitude(q);
		if (mag < 0.00001f)
			return Quaternion::identity();
		else
			return q / mag;
	}

	float magnitude(Quaternion q)
	{
		return sqrt(sqrMagnitude(q));
	}

	float sqrMagnitude(Quaternion q)
	{
		return q.dot(q);
	}

	static Quaternion euler(float x, float y, float z)
	{
		return fromEulerRad(Vector3D(x, y, z) * 0.01745329251f);
	}

	static Quaternion fromEulerRad(Vector3D euler) 
	{
		return eulerToQuaternion(euler);
	}

	Vector3D quaternionToEuler()
	{
		float sqw = m_w * m_w;
		float sqx = m_x * m_x;
		float sqy = m_y * m_y;
		float sqz = m_z * m_z;
		float unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
		float test = m_x * m_w - m_y * m_z;
		Vector3D v;

		if (test > 0.4995f * unit) 
		{ 
			// singularity at north pole
			v.m_y = 2 * atan2(m_y, m_x);
			v.m_x = m_pi / 2;
			v.m_z = 0;
			return normalizeAngles(v * m_rad2deg);
		}
		if (test < -0.4995f * unit) 
		{ 
			// singularity at south pole
			v.m_y = -2 * atan2(m_y, m_x);
			v.m_x = -m_pi / 2;
			v.m_z = 0;
			return normalizeAngles(v * m_rad2deg);
		}
		Quaternion q = Quaternion(m_w, m_z, m_x, m_y);
		v.m_y = (float)atan2(2 * q.m_x * q.m_w + 2 * q.m_y * q.m_z, 1 - 2 * (q.m_z * q.m_z + q.m_w * q.m_w));  // Yaw
		v.m_x = (float)asin(2 * (q.m_x * q.m_z - q.m_w * q.m_y));  // Pitch
		v.m_z = (float)atan2(2 * q.m_x * q.m_y + 2 * q.m_z * q.m_w, 1 - 2 * (q.m_y * q.m_y + q.m_z * q.m_z));  // Roll
		return normalizeAngles(v * m_deg2rad);
	}

	static Vector3D normalizeAngles(Vector3D angles)
	{
		angles.m_x = normalizeAngle(angles.m_x * 57.29578f);
		angles.m_y = normalizeAngle(angles.m_y * 57.29578f);
		angles.m_z = normalizeAngle(angles.m_z * 57.29578f);

		return angles;
	}

	static float normalizeAngle(float angle)
	{
		while (angle > 360)
			angle -= 360;
		while (angle < 0)
			angle += 360;
		return angle;
	}

public:
	//Don't update unless you don't know quaternial math
	float m_x;
	//Don't update unless you don't know quaternial math
	float m_y;
	//Don't update unless you don't know quaternial math
	float m_z;
	//Don't update unless you don't know quaternial math
	float m_w;

private:
    double m_epsilon = 0.000001f;
	double m_rad2deg = 57.29578f;
	double m_deg2rad = 0.01745329251f;
	double m_pi = 3.1415926535f;
};