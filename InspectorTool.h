#pragma once
#include "Tool.h"
#include "Entity.h"

class InspectorTool : public Tool
{
public:
	InspectorTool();
	~InspectorTool();

	virtual void renderBody() override;

	static void setCurrentCam(CCamera* cam);
	static CCamera* getCurrentCam();

private:
	static CCamera* m_cam;

	bool m_is_active_tool = true;
};