#include "CCamera.h"
#include "Entity.h"
#include "CTransform.h"
#include "World.h"
#include "GraphicsEngine.h"

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
	GraphicsEngine::get()->removeComponent(this);
}

void CCamera::getViewMatrix(Matrix4x4& view)
{
	m_entity->getTransform()->getWorldMatrix(view);
	view.inverse();
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
