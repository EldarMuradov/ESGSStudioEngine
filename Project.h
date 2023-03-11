#pragma once
#include "Tool.h"

class Project : public Tool
{
public:
	Project();
	~Project();

	virtual void renderBody() override;

private:
	bool m_is_active_tool = true;
};