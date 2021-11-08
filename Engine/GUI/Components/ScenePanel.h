#ifndef _SCENEPANEL_H_
#define _SCENEPANEL_H_

#pragma once
#include "../ImGui/imgui.h"
#include <d3d11.h>
#include "Console.h"
#include "../../Core/Renderer/DirectX/d3dclass.h"
#include "../../Core/Scene/Controllers/GameManager.h"


class ScenePanel
{
public:

    D3DClass* m_DirectX;
    Console* m_console;
    GameManager* m_GameManager;

    ScenePanel(D3DClass* directX, GameManager* gameManager, Console* console)
    {
        m_DirectX = directX;
        m_console = console;
        m_GameManager = gameManager;
    }

    void Render(ID3D11ShaderResourceView* sceneView)
    {
        ShowSceneWindow(sceneView);
    }

private:
    void ShowStatOverlay(bool* p_open)
    {
        const float PAD = 10.0f;
        static int corner = 0;
        ImGuiIO& io = ImGui::GetIO();
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
        if (corner != -1)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            //ImVec2 work_pos = ImGui::GetWindowPos();
            ImVec2 work_size = viewport->Size;
            ImVec2 window_pos = ImGui::GetWindowPos();
            ImVec2 window_pos_pivot;
            // window_pos.x = (corner & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
            // window_pos.y = (corner & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD + 80);
            window_pos.x += PAD;
            window_pos.y += PAD + 50;

            window_pos_pivot.x = (corner & 1) ? 1.0f : 0.0f;
            window_pos_pivot.y = (corner & 2) ? 1.0f : 0.0f;
            ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
            window_flags |= ImGuiWindowFlags_NoMove;
        }
        ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
        if (ImGui::Begin("stat overlay", p_open, window_flags))
        {
            //if (ImGui::IsMousePosValid())
            //    ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
            //else
            //    ImGui::Text("Mouse Position: <invalid>");
            //ImGui::Separator();

            // GPU STATS
            ImGui::Text("GPU: %s", m_DirectX->m_videoCardDescription);
            ImGui::Text("Dedicated Memory: %d Mb", m_DirectX->m_videoCardMemory);

            ImGui::Text("");

            // FRAME TIMES
            ImGui::Text("Frame Rate: %.0f FPS", ImGui::GetIO().Framerate);
            ImGui::Text("Frame Time: %.3f ms", 1000.0f / ImGui::GetIO().Framerate);

            ImGui::Text("");

            ImGui::Text("Scene Rendering:");
            ImGui::Text("Material Update: %.3f ms", 0);
            ImGui::Text("Prepare Time: %.3f ms", m_GameManager->m_PrepareSceneTime);
            ImGui::Text("Present Time: %.3f ms", m_GameManager->m_PresentSceneTime);

            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
                if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
                if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
                if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
                if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
                if (p_open && ImGui::MenuItem("Close")) *p_open = false;
                ImGui::EndPopup();
            }
        }
        ImGui::End();
    }

    void ShowSceneWindow(ID3D11ShaderResourceView* sceneView)
    {
        static bool t = true;

        if (ImGui::Begin("Scene"))
        {
            static bool wireframe = false;
            static bool past_state = false;
            ImGui::Checkbox("Wireframe", &wireframe);

            // if state changed
            if (wireframe != past_state) {
                if (wireframe) {
                    m_console->AddLog("[info] Wireframe enabled.");
                    //m_DirectX->EnableWireframe();
                }
                else {
                    m_console->AddLog("[info] Wireframe disabled.");
                    //m_DirectX->DisableWireframe();
                }
                past_state = wireframe;
            }

            ImVec2 size = ImGui::GetWindowSize();
            ImVec2 pos = ImGui::GetCursorScreenPos();
            pos.x -= 5;
            // subtract the panel height
            size.y -= ImGui::GetItemRectSize().y * 2 + 8;
            static ImVec2 maxPos;
            if (size.y * 1.7777 >= size.x) {
                maxPos = ImVec2(pos.x + size.x, pos.y + size.x * 0.5625);
            }
            else {
                maxPos = ImVec2(pos.x + size.y * 1.7777, pos.y + size.y);
            }

            // show the image
            ImGui::GetWindowDrawList()->AddImage((void*)sceneView, pos, ImVec2(maxPos));

            //fps and rest
            ShowStatOverlay(&t);

        }
        ImGui::End();
    }
};

#endif