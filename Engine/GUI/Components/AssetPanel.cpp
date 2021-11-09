#include "AssetPanel.h"

#include "../../GUI/ImGui/imgui.h"
#include <atomic>
#include <d3d11.h>

const filesystem::path s_AssetsPath = "Assets";

ID3D11ShaderResourceView* folder_texture;
ID3D11ShaderResourceView* document_texture;
ID3D11ShaderResourceView* object_texture;
ID3D11ShaderResourceView* text_texture;
ID3D11ShaderResourceView* file_texture;

AssetPanel::AssetPanel(D3DClass* DirectX)
{
    m_CurrentDirectory = s_AssetsPath;

    // load in the textures
    int img_width, img_height;
    DirectX->LoadTexture("../Engine/Resources/AssetPanel/folder.png", &folder_texture, &img_width, &img_height);
    DirectX->LoadTexture("../Engine/Resources/AssetPanel/document.png", &document_texture, &img_width, &img_height);
    DirectX->LoadTexture("../Engine/Resources/AssetPanel/object.png", &object_texture, &img_width, &img_height);
    DirectX->LoadTexture("../Engine/Resources/AssetPanel/text.png", &text_texture, &img_width, &img_height);
    DirectX->LoadTexture("../Engine/Resources/AssetPanel/file.png", &file_texture, &img_width, &img_height);

    UpdateDirectoryFiles();
}

AssetPanel::~AssetPanel()
{
    folder_texture->Release();
    document_texture->Release();
    object_texture->Release();
    text_texture->Release();
    file_texture->Release();
}


void AssetPanel::UpdateDirectoryFiles()
{
    directoryFiles.clear();
    for (auto &p : filesystem::directory_iterator(m_CurrentDirectory))
    {
        directoryFiles.push_back(p);
    }
}

void AssetItemMenu()
{
    if (ImGui::BeginPopupContextItem())
    {
        ImGui::MenuItem("(demo menu)", NULL, false, false);
        if (ImGui::MenuItem("New")) {}
        if (ImGui::MenuItem("Open", "Ctrl+O")) {}

        ImGui::EndPopup();
    }
}

void AssetPanel::Render()
{
    ImGui::Begin("Assets");
    {
        if (ImGui::Button(u8"®"))
        {
            UpdateDirectoryFiles();
        }
        ImGui::SameLine();

        static char buf[32] = "Search";
        ImGui::PushItemWidth(200);
        ImGui::InputText("", buf, IM_ARRAYSIZE(buf));

        if (ImGui::IsItemClicked())
        {
            if (strcmp(buf, "Search") == 0)
            {
                //buf[0] = 'X';
                memset(&buf, 0, sizeof(buf));
            }
        }

        ImGui::SameLine();
        ImGui::Text(m_CurrentDirectory.string().c_str());

        ImGui::Separator();


        ImGui::BeginChild("AssetPanelPopupMenu");
        if (ImGui::BeginPopupContextItem())
        {
            ImGui::MenuItem("TEST", NULL, false, false);

            ImGui::EndPopup();
        }


        ImVec4& bg_col = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
        static float thumbnailSize = 88;
        static int frame_padding = 1;

        if (m_CurrentDirectory != filesystem::path(s_AssetsPath))
        {
            if (ImGui::ArrowButton("##left", ImGuiDir_Left))
            {
                m_CurrentDirectory = m_CurrentDirectory.parent_path();
                UpdateDirectoryFiles();
            }
        }

        for (int i = 0; i < directoryFiles.size(); i++)
        {
            const auto& path = directoryFiles[i].path();
            auto relativePath = filesystem::relative(path, s_AssetsPath);
            string filename = relativePath.filename().string();

            ImGui::PushID("SceneGameObjectId-" + i);
            ImGui::BeginGroup();
            
            ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));

            if (directoryFiles[i].is_directory())
            {
                ImGui::ImageButton((void*)folder_texture, { thumbnailSize, thumbnailSize }, { 0,0 }, { 1,1 }, frame_padding, bg_col);
            }
            else if (path.extension()==".obj")
            {
                ImGui::ImageButton((void*)object_texture, { thumbnailSize, thumbnailSize }, { 0,0 }, { 1,1 }, frame_padding, bg_col);

            }
            else if (path.extension() == ".txt")
            {
                ImGui::ImageButton((void*)text_texture, { thumbnailSize, thumbnailSize }, { 0,0 }, { 1,1 }, frame_padding, bg_col);
            }
            else
            {
                ImGui::ImageButton((void*)file_texture, { thumbnailSize, thumbnailSize }, { 0,0 }, { 1,1 }, frame_padding, bg_col);
            }

            AssetItemMenu();

            ImGui::PopStyleColor();

            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                if (directoryFiles[i].is_directory())
                {
                    m_CurrentDirectory /= path.filename();
                    UpdateDirectoryFiles();
                }
                else
                {
                    // open file in the default program
                    ShellExecute(0, 0, path.wstring().c_str(), 0, 0, SW_SHOW);
                }
            }

            ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + thumbnailSize);
            ImGui::Text(filename.c_str());

            float textWidth = ImGui::CalcTextSize(filename.c_str()).x;
            ImGui::SetNextItemWidth(textWidth);

            // ADD ... IF NAME IS TO LARGE
            //if (textWidth > thumbnailSize)
            //{
            //    ImGui::SetNextItemWidth(thumbnailSize);
            //    const char* tmp = "...";
            //    ImGui::LabelText(tmp, filename.c_str());
            //}
            //else
            //{
            //    ImGui::Text(filename.c_str());
            //}

            ImGui::EndGroup();
            ImGui::PopID();

            // organize layout of items
            float last_button_x2 = ImGui::GetItemRectMax().x;
            float next_button_x2 = last_button_x2 + ImGui::GetStyle().ItemSpacing.x + thumbnailSize;
            //if (i + 1 < gameObjects.size() && next_button_x2 < window_visible_x2)
            if (next_button_x2 < ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x)
                ImGui::SameLine();
        }

        ImGui::EndChild();
    }

    ImGui::End();
}