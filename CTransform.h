#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Vector3D.h"
#include "Quaternion.h"
#include "Matrix4x4.h"
#include "Rotator.h"
#include "Vector2D.h"

class CTransform : public Component
{
public:
	CTransform();
	virtual ~CTransform();

	void onUpdate() override;

	void setPosition(const Vector3D& pos);
	Vector3D getPosition();

	void setCamRotation(const Vector2D& rot);
	void setRotation(const Quaternion& rot);
	Quaternion getRotation();

	void setRotationY(float delta);
	void setRotationX(float delta);

	void setScale(const Vector3D& scale);
	Vector3D getScale();

	void getWorldMatrix(Matrix4x4& mat);

private:
	void rotate(const Quaternion& q);
	void rotateCam(const Vector2D& rot);

protected:
	void updateMatrix();
	void updateCamMatrix();

protected:
	Vector3D m_position = Vector3D(0, 0, 0);

	Vector3D m_scale = Vector3D(1, 1, 1);

	Vector3D m_euler_rotation = Vector3D(0, 0, 0);

	Quaternion m_rotation = Quaternion();

	Matrix4x4 m_matrix;
};