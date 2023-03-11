#include "HierarchyTool.h"
#include "Entity.h"
#include "imgui.h"
#include <map>
#include "Vector2D.h"
#include <iostream>
#include "imgui_internal.h"
#include <comdef.h>

Entity* HierarchyTool::m_current_entity = nullptr;

HierarchyTool::HierarchyTool()
{
}

HierarchyTool::~HierarchyTool()
{
}

void HierarchyTool::renderBody()
{
    ImGui::Begin("Hierarchy Tool", &m_is_active_tool, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Entities:");
        ImGui::EndMenuBar();
    }

    ImGui::Separator();
    int i = 0;
    for (auto entity : World::getAllEntities())
    {
        if (ImGui::CollapsingHeader(entity->getName().c_str()))
        {
            if (ImGui::Button(std::to_string(i).c_str()))
            {
                m_current_entity = entity;
                std::cout << entity->getName() << "\n";
            }
            ImGui::Separator();
        }
        i++;
    }
    ImGui::End();
}

void HierarchyTool::setCurrentEntity(Entity* entity)
{
	m_current_entity = entity;
}

Entity* HierarchyTool::getCurrentEntity()
{
	return m_current_entity;
}
