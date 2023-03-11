#include "GUIManager.h"
#include "imgui.h"
#include "AppWindow.h"
#include <string>
#include "InspectorTool.h"

GUIManager::GUIManager()
{

}

GUIManager::~GUIManager()
{

}

InspectorTool inspector = InspectorTool();

std::string fps = "FPS: ";
bool is_tool_active = true;

void GUIManager::update()
{
    ImGui::Begin("Debug", 0);  
    ImGui::Text("Debug during play mode");

    std::string fps_c = fps + std::to_string((int)(1.0f / AppWindow::getDeltaTime()));
    ImGui::Text(fps_c.c_str());
    ImGui::End();

    inspector.renderBody();

    /*
    ImGui::Begin("Debug Tool", &is_tool_active, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Console"))
        {
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    // Generate samples and plot them
    float samples[150];
    for (int n = 0; n < 150; n++)
        samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
    ImGui::PlotLines("Samples", samples, 150);

    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Output:");
    ImGui::Text("Success");
    ImGui::Text("Console>");
    ImGui::End();

    ImGui::Begin("Hierarchy Tool", &is_tool_active, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Entities"))
        {
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Global:");
    ImGui::Text("-> PlayerController");
    ImGui::Text("DirectionalLight");
    ImGui::Text("Terrain");
    ImGui::Text("Box");
    ImGui::Text("House (5)");
    ImGui::Text("Building (2)");
    ImGui::End();

    ImGui::Begin("Inspector Tool", &is_tool_active, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Components"))
        {
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Entity: PlayerController");
    ImGui::Text("Transform");
    ImGui::Text("MeshRenderer");
    ImGui::Text("Rigidbody");
    ImGui::Text("Camera");
    ImGui::Text("Light (Point)");
    ImGui::End();
    */

}
