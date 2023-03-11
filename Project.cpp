#include "Project.h"
#include "imgui.h"
#include "imgui_internal.h"

Project::Project()
{
}

Project::~Project()
{
}

void Project::renderBody()
{
    ImGui::Begin("Project Tool", &m_is_active_tool, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Assets:");
        ImGui::EndMenuBar();
    }

    ImGui::Text("");


    ImGui::End();
}
