#pragma once
#include "Component.h"
#include "Prerequisites.h"
#include "CameraType.h"
#include <Windows.h>
#include "Matrix4x4.h"

class CCamera : public Component
{
public:
	CCamera();
	virtual ~CCamera();

	void getViewMatrix(Matrix4x4& view);

	void getProjection(Matrix4x4& proj);

	void setFarPlane(float far_plane);
	float getFarPlane();

	void setNearPlane(float near_plane);
	float getNearPlane();

	void setFieldOfView(float field);
	float getFieldOfView();

	void setType(const CameraType& type);
	CameraType getType();

	void setScreenArea(const RECT& area);
	RECT getScreenArea();

private:
	void computeProjectionMatrix();

protected:
	virtual void onCreateInternal();

private:
	Matrix4x4 m_projection;

	float m_near_plane = 0.1f;
	float m_far_plane = 5000.0f;
	float m_field_of_view = 1.3f;

	CameraType m_type = CameraType::Perspective;

	RECT m_screen_area;
};