#include "Debug.h"
#include "imgui.h"
#include "imgui_internal.h"

std::string Debug::m_log = "0";

Debug::Debug()
{
}

Debug::~Debug()
{
}

void Debug::renderBody()
{
    ImGui::Begin("Console Tool", &m_is_active_tool, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Console:");
        ImGui::EndMenuBar();
    }

    ImGui::Text(m_log.c_str());

    if (m_log.size() > 5000)
        m_log = "";

    ImGui::End();
}

void Debug::Log(std::string log)
{
	m_log += log + "\n";
}

void Debug::Log(std::string log, float val)
{
    m_log += log + std::to_string(val) + "\n";
}
