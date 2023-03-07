#pragma once
#include "Component.h"
#include "Vector4D.h"

class CLight : public Component
{
public:
	CLight();
	virtual ~CLight();

	void setColor(const Vector4D& color);
	Vector4D getColor();

private:
	void updateLight(void* data);

protected:
	virtual void onCreateInternal();

private:
	Vector4D m_color = Vector4D(1, 1, 1, 1);

	ConstantBufferPtr m_cb;

	friend class AppWindow;
};