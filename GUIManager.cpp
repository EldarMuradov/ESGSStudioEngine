#include "GUIManager.h"
#include "imgui.h"
#include "AppWindow.h"
#include <string>
#include "InspectorTool.h"
#include "HierarchyTool.h"
#include "Debug.h"
#include "Project.h"

GUIManager::GUIManager()
{

}

GUIManager::~GUIManager()
{

}

InspectorTool inspector = InspectorTool();
HierarchyTool hierarchy = HierarchyTool();
Debug debug = Debug();
Project project = Project();

std::string fps = "FPS: ";
bool is_tool_active = true;
bool play = false;

void GUIManager::update()
{
    ImGui::Begin("Debug", 0);
    if (!play)
    {
        if (ImGui::Button("Start"))
        {
            play = !play;
            AppWindow::setPlayState(play);
        }
    }
    else
    {
        if (ImGui::Button("Stop"))
        {
            play = !play;
            AppWindow::setPlayState(play);
        }
    }

    ImGui::Text("Debug during play mode");

    std::string fps_c = fps + std::to_string((int)(1.0f / AppWindow::getDeltaTime()));
    ImGui::Text(fps_c.c_str());
    ImGui::End();

    inspector.renderBody();

    hierarchy.renderBody();

    debug.renderBody();

    project.renderBody();
}