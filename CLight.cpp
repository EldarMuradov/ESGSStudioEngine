#include "CLight.h"
#include "Entity.h"
#include "GraphicsEngine.h"
#include "constant.h"
#include <iostream>

CLight::CLight()
{
    constant cc;

    cc.light.direction = Vector3D();
    cc.light.color = Vector4D();
    m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(cc));
}

CLight::~CLight()
{
    GraphicsEngine::get()->removeComponent(this);
}

void CLight::setColor(const Vector4D& color)
{
    m_color = color;
}

Vector4D CLight::getColor()
{
    return m_color;
}

void CLight::setLightType(LightType type)
{
    m_light_type = type;
}

LightType CLight::getLightType()
{
    return m_light_type;
}

void CLight::updateLight(void* data)
{
    m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), data);
}

void CLight::onCreateInternal()
{
    GraphicsEngine::get()->addComponent(this);
}
