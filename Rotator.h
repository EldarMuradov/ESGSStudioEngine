#pragma once
#include "Quaternion.h"
#include "Matrix4x4.h"

class Rotator 
{
public:
	static void rotate(Matrix4x4& mat, Quaternion q) 
	{
		float x = q.m_x * 2.0;
		float y = q.m_y * 2.0;
		float z = q.m_z * 2.0;
		float xx = q.m_x * x;
		float yy = q.m_y * y;
		float zz = q.m_z * z;
		float xy = q.m_x * y;
		float xz = q.m_x * z;
		float yz = q.m_y * z;
		float wx = q.m_w * x;
		float wy = q.m_w * y;
		float wz = q.m_w * z;

		// Calculate 3x3 matrix from orthonormal basis
		mat.m_mat[0][0] = 1.0f - (yy + zz);
		mat.m_mat[1][0] = xy + wz;
		mat.m_mat[2][0] = xz - wy;
		mat.m_mat[0][1] = xy - wz;
		mat.m_mat[1][1] = 1.0f - (xx + zz);
		mat.m_mat[2][1] = yz + wx;
		mat.m_mat[0][2] = xz + wy;
		mat.m_mat[1][2] = yz - wx;
		mat.m_mat[2][2] = 1.0f - (xx + yy);
		mat.m_mat[3][3] = 1.0f;
	}
};