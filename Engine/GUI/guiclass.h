#ifndef _GUICLASS_H_
#define _GUICLASS_H_

#include <limits>

#include "../../Core/Renderer/DirectX/d3dclass.h"
#include "../Core/Renderer/Utils/Mesh.h"
#include "../../Core/Scene/Entity/Components/Light/lightclass.h"
#include "../../Core/Renderer/Controllers/scenerenderclass.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"
#include "../../Core/Scene/Controllers/GameManager.h"
#include "../../GUI/Components/AssetPanel.h"
#include "Components/Console.h"
#include "Components/ScenePanel.h"


class GuiClass
{
public:

    struct Log
    {
        ImGuiTextBuffer     Buf;
        ImGuiTextFilter     Filter;
        ImVector<int>       LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
        bool                AutoScroll;  // Keep scrolling if already at the bottom.

        Log()
        {
            AutoScroll = true;
            Clear();
        }

        void Clear()
        {
            Buf.clear();
            LineOffsets.clear();
            LineOffsets.push_back(0);
        }

        void AddLog(const char* fmt, ...) IM_FMTARGS(2)
        {
            int old_size = Buf.size();
            va_list args;
            va_start(args, fmt);
            Buf.appendfv(fmt, args);
            va_end(args);
            for (int new_size = Buf.size(); old_size < new_size; old_size++)
                if (Buf[old_size] == '\n')
                    LineOffsets.push_back(old_size + 1);
        }

        void Draw(const char* title, bool* p_open = NULL)
        {
            if (!ImGui::Begin(title, p_open))
            {
                ImGui::End();
                return;
            }

            // Options menu
            if (ImGui::BeginPopup("Options"))
            {
                ImGui::Checkbox("Auto-scroll", &AutoScroll);
                ImGui::EndPopup();
            }

            // Main window
            if (ImGui::Button("Options"))
                ImGui::OpenPopup("Options");
            ImGui::SameLine();
            bool clear = ImGui::Button("Clear");
            ImGui::SameLine();
            bool copy = ImGui::Button("Copy");
            ImGui::SameLine();
            Filter.Draw("Filter", -100.0f);

            ImGui::Separator();
            ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

            if (clear)
                Clear();
            if (copy)
                ImGui::LogToClipboard();

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
            const char* buf = Buf.begin();
            const char* buf_end = Buf.end();
            if (Filter.IsActive())
            {
                // In this example we don't use the clipper when Filter is enabled.
                // This is because we don't have a random access on the result on our filter.
                // A real application processing logs with ten of thousands of entries may want to store the result of
                // search/filter.. especially if the filtering function is not trivial (e.g. reg-exp).
                for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
                {
                    const char* line_start = buf + LineOffsets[line_no];
                    const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                    if (Filter.PassFilter(line_start, line_end))
                        ImGui::TextUnformatted(line_start, line_end);
                }
            }
            else
            {
                // The simplest and easy way to display the entire buffer:
                //   ImGui::TextUnformatted(buf_begin, buf_end);
                // And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward
                // to skip non-visible lines. Here we instead demonstrate using the clipper to only process lines that are
                // within the visible area.
                // If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them
                // on your side is recommended. Using ImGuiListClipper requires
                // - A) random access into your data
                // - B) items all being the  same height,
                // both of which we can handle since we an array pointing to the beginning of each line of text.
                // When using the filter (in the block of code above) we don't have random access into the data to display
                // anymore, which is why we don't use the clipper. Storing or skimming through the search result would make
                // it possible (and would be recommended if you want to search through tens of thousands of entries).
                ImGuiListClipper clipper;
                clipper.Begin(LineOffsets.Size);
                while (clipper.Step())
                {
                    for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
                    {
                        const char* line_start = buf + LineOffsets[line_no];
                        const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                        //if (line_start[0] == 'e') {
                        //    line_start++;
                        //    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), line_start, line_end);
                        //}
                        //else if (line_start[0] == 'w') {
                        //    line_start++;
                        //    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), line_start, line_end);
                        //}
                        //else {
                        //    ImGui::TextUnformatted(line_start, line_end);
                        //}

                        ImGui::TextUnformatted(line_start, line_end);
                    }
                }
                clipper.End();
            }
            ImGui::PopStyleVar();

            if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                ImGui::SetScrollHereY(1.0f);

            ImGui::EndChild();
            ImGui::End();
        }
    };


public:
    GuiClass(HWND, D3DClass*, GameManager*);
    ~GuiClass();

    void Render(ID3D11ShaderResourceView* SceneTexture, ID3D11ShaderResourceView* GameTexture);

    ImGuiIO& getIO();

    // console messages
    void PrintConsole(const char*);

    ImGuiIO* GetInputHandler();

private:

    GameManager* m_GameManager;

    void ShowInspectorWindow(Entity*);
    void ShowCameraWindow(CameraComponent* camera);

    void ShowStatOverlay(bool*);
    void ShowSceneWindow(ID3D11ShaderResourceView* sceneView);

    void ShowLightWindow(LightClass*);
    void ShowLog(bool*);
    void ShowMenuBar();
    void ShowSceneObjects(vector<Entity*>& gameObjects);
    void ShowAssetsWindow();
    void ShowConsole(bool*);
    void DockingAndMenuBar(bool*);



    D3DClass* m_DirectX;

    // GUI COMPONENTS
    AssetPanel* m_AssetPanel;
    ScenePanel* m_ScenePanel;
    Console* m_console;


};
#endif // !_GUICLASS_H_
