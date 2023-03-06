#pragma once
#include "Entity.h"

class PlayerController : public Entity
{
public:
	PlayerController();
	virtual ~PlayerController();

	virtual void onCreate() override;
	virtual void onUpdate() override;

private:
	float m_rot_y = 0;
	float m_rot_x = 0;

	float m_delta_x = 0;
	float m_delta_y = 0;
};

