#pragma once
#include "Tool.h"
#include "Entity.h"

class HierarchyTool : public Tool
{
public:
	HierarchyTool();
	~HierarchyTool();

	virtual void renderBody() override;

	static void setCurrentEntity(Entity* entity);
	static Entity* getCurrentEntity();

private:
	static Entity* m_current_entity;

	bool m_is_active_tool = true;

	friend class InspectorTool;
};

