#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Vector3D.h"
#include "Quaternion.h"
#include "Matrix4x4.h"
#include "Rotator.h"

class CTransform : public Component
{
public:
	CTransform();
	virtual ~CTransform();

	void onUpdate() override;

	void setPosition(const Vector3D& pos);
	Vector3D getPosition();

	void setRotation(const Quaternion& rot);
	Quaternion getRotation();

	void setScale(const Vector3D& scale);
	Vector3D getScale();

	void getWorldMatrix(Matrix4x4& mat);

private:
	void rotate(const Quaternion& q);

protected:
	void updateMatrix();

protected:
	Vector3D m_position = Vector3D(0, 0, 0);

	Vector3D m_scale = Vector3D(1, 1, 1);

	Quaternion m_rotation = Quaternion();

	Matrix4x4 m_matrix;
};