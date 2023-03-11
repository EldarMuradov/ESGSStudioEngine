#include "InspectorTool.h"
#include "Entity.h"
#include "imgui.h"
#include <map>
#include "Vector2D.h"
#include <iostream>
#include "imgui_internal.h"
#include <comdef.h>
#include "HierarchyTool.h"

CCamera* InspectorTool::m_cam = nullptr;

InspectorTool::InspectorTool()
{
}

InspectorTool::~InspectorTool()
{
}

void InspectorTool::renderBody()
{
	if (HierarchyTool::m_current_entity != nullptr)
	{
        ImGui::Begin("Inspector Tool", &m_is_active_tool, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMenuBar())
        {
            ImGui::TextColored(ImVec4(1, 1, 0, 1), HierarchyTool::m_current_entity->getName().c_str());
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Components:");
            ImGui::EndMenuBar();
        }

        ImGui::Text("Tag:");
        ImGui::BulletText(HierarchyTool::m_current_entity->getTag());
        ImGui::Separator();

        for (auto c : HierarchyTool::m_current_entity->getAllComponentsFromEntity())
        {
            if (c->toStr() == "Transform")
            {
                if (ImGui::CollapsingHeader("Transform"))
                {
                    CTransform* transform = (CTransform*)c;
                    std::string pos = "X: " + std::to_string((int)transform->getPosition().m_x)
                        + "   Y: " + std::to_string((int)transform->getPosition().m_y)
                        + "   Z: " + std::to_string((int)transform->getPosition().m_z);

                    std::string rot = "X: " + std::to_string(-(int)transform->getEulerRotation().m_x)
                        + "   Y: " + std::to_string((int)transform->getEulerRotation().m_y)
                        + "   Z: " + std::to_string((int)transform->getEulerRotation().m_z);

                    std::string scale = "X: " + std::to_string((int)transform->getScale().m_x)
                        + "   Y: " + std::to_string((int)transform->getScale().m_y)
                        + "   Z: " + std::to_string((int)transform->getScale().m_z);

                    ImGui::Text("Position:");
                    ImGui::BulletText(pos.c_str());
                    ImGui::Separator();

                    ImGui::Text("Rotation:");
                    ImGui::BulletText(rot.c_str());
                    ImGui::Separator();

                    ImGui::Text("Scale: ");
                    ImGui::BulletText(scale.c_str());
                    ImGui::Separator();
                }
            }
            else if (c->toStr() == "MeshRenderer")
            {
                if (ImGui::CollapsingHeader("MeshRenderer"))
                {
                    CMesh* mesh = (CMesh*)c;
                    std::string str = "Count: " + std::to_string(mesh->m_materials.size());

                    std::string str2 = "Count: " + std::to_string(mesh->m_mesh->getIndexBuffer()->getSizeIndexList());
                
                    ImGui::Text("Mesh:");

                    ImGui::Text("Indices:");
                    ImGui::BulletText(str2.c_str());
                    ImGui::Separator();

                    ImGui::Text("Materials:");

                    ImGui::BulletText(str.c_str());
                    ImGui::Separator();
                }
            }
            else if (c->toStr() == "Camera")
            {
                if (ImGui::CollapsingHeader("Camera"))
                {
                    CCamera* cam = (CCamera*)c;

                    const char* type = "";

                    if((int)cam->getType() == 0)
                        type = "Orthogonal";
                    else if ((int)cam->getType() == 1)
                        type = "Perspective";

                    ImGui::Text("Camera type:");
                    ImGui::BulletText(type);
                    ImGui::Separator();

                    std::string fov = std::to_string((int)cam->getFieldOfView());

                    ImGui::Text("Field of view:");
                    ImGui::BulletText(fov.c_str());
                    ImGui::Separator();

                    std::string fp = std::to_string((int)cam->getFarPlane());

                    ImGui::Text("Far plane:");
                    ImGui::BulletText(fp.c_str());
                    ImGui::Separator();

                    std::string np = std::to_string((int)cam->getNearPlane());

                    ImGui::Text("Near plane:");
                    ImGui::BulletText(np.c_str());
                    ImGui::Separator();

                    RECT rc = cam->getScreenArea();

                    int x = rc.right - rc.left;
                    int y = rc.bottom - rc.top;

                    std::string rect = "X: " + std::to_string(x) + "   Y: " + std::to_string(y);

                    ImGui::Text("Screen area");
                    ImGui::BulletText(rect.c_str());
                    ImGui::Separator();
                }
            }
            else if (c->toStr() == "Light")
            {
                if (ImGui::CollapsingHeader("Light"))
                {
                    CLight* light = (CLight*)c;
                    std::string color = "R: " + std::to_string(light->getColor().m_x)
                        + "   G: " + std::to_string(light->getColor().m_y)
                        + "   B: " + std::to_string(light->getColor().m_z);

                    ImGui::Text("Color:");
                    ImGui::BulletText(color.c_str());
                    ImGui::Separator();

                    const char* type = "";

                    if ((int)light->getLightType() == 0)
                        type = "Directional";
                    else if ((int)light->getLightType() == 1)
                        type = "Point";
                    else if ((int)light->getLightType() == 2)
                        type = "Spot";
                    else if ((int)light->getLightType() == 3)
                        type = "Area";

                    ImGui::Text("Light type:");
                    ImGui::BulletText(type);
                    ImGui::Separator();
                }
            }
        }
        ImGui::End();
	}
	else 
	{
        ImGui::Begin("Inspector Tool", &m_is_active_tool, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMenuBar())
        {
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Select an entity");
            ImGui::EndMenuBar();
        }
        ImGui::End();
	}

    //auto cam = m_cam;

    //Vector2D pos = cam->worldPointToScreen(m_current_entity->getTransform()->getPosition());

    //auto v = AppWindow::getRect();

    //ImGui::GetBackgroundDrawList()->AddRect(ImVec2(pos.m_x, pos.m_y), ImVec2(pos.m_x + 600, pos.m_y + 600), ImGui::GetColorU32(ImVec4(1, 1, 1, 1)));
    
    //ImGui::GetBackgroundDrawList()->AddLine(ImVec2(-pos.m_x, -pos.m_y), ImVec2(v.m_x / 2, v.m_y / 2), ImGui::GetColorU32(ImVec4(1, 1, 1, 1)), 2);

    //std::cout << pos.m_x << " " << pos.m_y << "\n";
}

void InspectorTool::setCurrentCam(CCamera* cam)
{
    m_cam = cam;
}

CCamera* InspectorTool::getCurrentCam()
{
    return m_cam;
}
