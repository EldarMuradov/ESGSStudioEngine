#include "CCamera.h"
#include "Entity.h"
#include "CTransform.h"
#include "World.h"
#include "GraphicsEngine.h"
#include "WorldToScreenPoint.h"
#include "Vector2D.h"

CCamera::CCamera()
{
	m_view.setIdentity();
	m_projection.setIdentity();
}

CCamera::~CCamera()
{
	GraphicsEngine::get()->removeComponent(this);
}

const char* CCamera::toStr()
{
	return "Camera";
}

void CCamera::getViewMatrix(Matrix4x4& view)
{
	m_entity->getTransform()->getWorldMatrix(view);
	view.inverse();

	m_view.setIdentity();
	m_view.setMatrix(view);
}

void CCamera::getProjection(Matrix4x4& proj)
{
	proj = m_projection;
}

void CCamera::setFarPlane(float far_plane)
{
	m_far_plane = far_plane;
	computeProjectionMatrix();
}

float CCamera::getFarPlane()
{
	return m_far_plane;
}

void CCamera::setNearPlane(float near_plane)
{
	m_near_plane = near_plane;
	computeProjectionMatrix();
}

float CCamera::getNearPlane()
{
	return m_near_plane;
}

void CCamera::setFieldOfView(float field)
{
	m_field_of_view = field;
	computeProjectionMatrix();
}

float CCamera::getFieldOfView()
{
	return m_field_of_view;
}

void CCamera::setType(const CameraType& type)
{
	m_type = type;
	computeProjectionMatrix();
}

CameraType CCamera::getType()
{
	return m_type;
}

void CCamera::setScreenArea(const RECT& area)
{
	m_screen_area = area;
	computeProjectionMatrix();
}

RECT CCamera::getScreenArea()
{
	return m_screen_area;
}

bool f = false;

Vector2D CCamera::worldPointToScreen(const Vector3D& point)
{
	if (f)
	{
		Vector4D clipSpacePos = WorldToScreenPoint::multipleOverMatrix4x4(m_view, Vector4D(point));

		Vector3D ndcSpacePos = Vector3D(clipSpacePos.m_x / clipSpacePos.m_w, clipSpacePos.m_y / clipSpacePos.m_w, clipSpacePos.m_z / clipSpacePos.m_w);
		Vector2D windowSpacePos = (Vector2D(ndcSpacePos.m_x + 1, ndcSpacePos.m_y + 1) * 0.5f)
			* Vector2D(m_screen_area.left - m_screen_area.right, m_screen_area.bottom - m_screen_area.top);
		return windowSpacePos;
	}

	f = true;

	return Vector2D(0, 0);
}

void CCamera::computeProjectionMatrix()
{
	if (m_type == CameraType::Perspective)
		m_projection.setPerspectiveFovLH(m_field_of_view, 
			(float)(m_screen_area.right - m_screen_area.left) / (float)(m_screen_area.bottom - m_screen_area.top), m_near_plane, m_far_plane);
	else if (m_type == CameraType::Orthogonal)
		m_projection.setOrthoLH((float)(m_screen_area.right - m_screen_area.left), (float)(m_screen_area.bottom - m_screen_area.top), m_near_plane, m_far_plane);
}

void CCamera::onCreateInternal()
{
	GraphicsEngine::get()->addComponent(this);
}
