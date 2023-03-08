#pragma once
#include "Component.h"
#include "Vector4D.h"
#include "LightType.h"

class CLight : public Component
{
public:
	CLight();
	virtual ~CLight();

	void setColor(const Vector4D& color);
	Vector4D getColor();

	void setLightType(LightType type);
	LightType getLightType();

private:
	void updateLight(void* data);

protected:
	virtual void onCreateInternal();

private:
	Vector4D m_color = Vector4D(1, 1, 1, 1);

	ConstantBufferPtr m_cb;

	LightType m_light_type = LightType::Directional;

	friend class AppWindow;
};