#include "GUIManager.h"
#include "imgui.h"
#include "AppWindow.h"
#include <string>

GUIManager::GUIManager()
{

}

GUIManager::~GUIManager()
{

}

std::string fps = "FPS: ";
bool is_tool_active = true;

void GUIManager::update()
{
    ImGui::Begin("Debug", 0);  
    ImGui::Text("Debug during play mode");

    std::string fps_c = fps + std::to_string((int)(1.0f / AppWindow::getDeltaTime()));
    ImGui::Text(fps_c.c_str());
    ImGui::End();

    ImGui::Begin("Debug Tool", &is_tool_active, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Console"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
            if (ImGui::MenuItem("Close", "Ctrl+W")) { is_tool_active = false; }
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
}
