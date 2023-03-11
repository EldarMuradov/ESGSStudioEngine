#pragma once
#include "Tool.h"
#include "Entity.h"

class InspectorTool : public Tool
{
public:
	InspectorTool();
	~InspectorTool();

	virtual void renderBody() override;

	static void setCurrentEntity(Entity* entity);
 	static Entity* getCurrentEntity();

	static void setCurrentCam(CCamera* cam);
	static CCamera* getCurrentCam();

public:
	static Entity* m_current_entity;

	static CCamera* m_cam;

	bool m_is_active_tool = true;
};