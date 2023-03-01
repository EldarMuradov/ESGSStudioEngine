#include "CTransform.h"
#include "Quaternion.h"
#include "Matrix4x4.h"

#include "Vector3D.h"
#include "Prerequisites.h"
#include "ESGSStudioEngine.h"

CTransform::CTransform()
{
	m_position = Vector3D();
	m_rotation = Quaternion();
}

CTransform::~CTransform()
{
}

void CTransform::onUpdate()
{

}

void CTransform::setPosition(const Vector3D& pos)
{
	m_position = pos;
	updateMatrix();
}

Vector3D CTransform::getPosition()
{
	return m_position;
}

void CTransform::setRotation(const Quaternion& rot)
{
	m_rotation = rot;
	updateMatrix();
}

Quaternion CTransform::getRotation()
{
	return m_rotation;
}

void CTransform::setScale(const Vector3D& scale)
{
	m_scale = scale;
	updateMatrix();
}

Vector3D CTransform::getScale()
{
	return m_scale;
}

void CTransform::getWorldMatrix(Matrix4x4& mat)
{
	mat.setMatrix(m_matrix);
}

void CTransform::rotate(const Quaternion& q)
{
	// Precalculate coordinate products
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
	m_matrix.m_mat[0][0] = 1.0f - (yy + zz);
	m_matrix.m_mat[1][0] = xy + wz;
	m_matrix.m_mat[2][0] = xz - wy;
	m_matrix.m_mat[0][1] = xy - wz;
	m_matrix.m_mat[1][1] = 1.0f - (xx + zz);
	m_matrix.m_mat[2][1] = yz + wx;
	m_matrix.m_mat[0][2] = xz + wy;
	m_matrix.m_mat[1][2] = yz - wx;
	m_matrix.m_mat[2][2] = 1.0f - (xx + yy);
	m_matrix.m_mat[3][3] = 1.0f;
}

void CTransform::updateMatrix()
{
	Matrix4x4 temp;

	m_matrix.setIdentity();

	//temp.setIdentity();
	//temp.rotate(m_rotation);
	rotate(m_rotation);

	temp.setIdentity();
	temp.setScale(m_scale);
	m_matrix *= temp;

	temp.setIdentity();
	temp.setTranslation(m_position);
	m_matrix *= temp;
}
