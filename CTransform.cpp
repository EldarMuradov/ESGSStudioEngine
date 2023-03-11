#include "CTransform.h"
#include "Quaternion.h"
#include "Matrix4x4.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Prerequisites.h"
#include "ESGSStudioEngine.h"

CTransform::CTransform()
{
}

CTransform::~CTransform()
{
}

const char* CTransform::toStr()
{
	return "Transform";
}

void CTransform::onUpdate()
{

}

void CTransform::setPosition(const Vector3D& pos)
{
	m_position = pos;
	if (is_camera)
		updateCamMatrix();
	else
		updateMatrix();
}

Vector3D CTransform::getPosition()
{
	return m_position;
}

void CTransform::setCamRotation(const Vector2D& rot)
{
	rotateCam(rot);
}

void CTransform::setRotation(const Quaternion& rot)
{
	m_rotation = rot;
	if (is_camera)
		updateCamMatrix();
	else
		updateMatrix();
}

Quaternion CTransform::getRotation()
{
	return m_rotation;
}

Vector3D CTransform::getEulerRotation()
{
	if(m_entity->getComponent<CCamera>() != nullptr)
		return m_euler_rotation * 57.29578f;
	return m_rotation.quaternionToEuler() * 57.29578f;
}

void CTransform::setRotationY(float delta)
{
	m_matrix.setRotationY(delta);
}

void CTransform::setRotationX(float delta)
{
	m_matrix.setRotationX(delta);
}

void CTransform::setScale(const Vector3D& scale)
{
	m_scale = scale;
	if (is_camera)
		updateCamMatrix();
	else
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

Vector3D CTransform::getZDirection()
{
	return m_matrix.getZDirection();
}

Vector3D CTransform::getXDirection()
{
	return m_matrix.getXDirection();
}

void CTransform::isCamera(bool iscam)
{
	is_camera = iscam;
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

void CTransform::rotateCam(const Vector2D& rot)
{
	m_euler_rotation = Vector3D(rot.m_x, rot.m_y, 0);
	updateCamMatrix();
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

void CTransform::updateCamMatrix()
{
	Matrix4x4 temp;

	m_matrix.setIdentity();

	temp.setIdentity();
	temp.setRotationX(m_euler_rotation.m_x);
	m_matrix *= temp;

	temp.setIdentity();
	temp.setRotationY(m_euler_rotation.m_y);
	m_matrix *= temp;

	//temp.rotate(m_rotation);
	//rotate(m_rotation);

	temp.setIdentity();
	temp.setScale(m_scale);
	m_matrix *= temp;

	temp.setIdentity();
	temp.setTranslation(m_position);
	m_matrix *= temp;
}
