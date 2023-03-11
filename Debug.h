#pragma once
#include "Tool.h"
#include <string>

class Debug : public Tool
{
public:
	Debug();
	~Debug();

	virtual void renderBody() override;

	static void Log(std::string log);
	static void Log(std::string log, float val);

private:
	static std::string m_log;

	bool m_is_active_tool = true;
};