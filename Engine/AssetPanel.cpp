#include "AssetPanel.h"

#include "ImGui/imgui.h"
#include <atomic>
#include <d3d11.h>

const filesystem::path s_AssetsPath = "data";

std::atomic<bool> stop_flag;

ID3D11ShaderResourceView* folder_texture;

AssetPanel::AssetPanel(D3DClass* DirectX)
{
    m_CurrentDirectory = s_AssetsPath;

    // Load the icons


    // load in the textures
    int img_width, img_height;
    DirectX->LoadTexture("../Engine/Resources/AssetPanel/folder.png", &folder_texture, &img_width, &img_height);

    // Start The Thread
    stop_flag = false;
    updateThread = thread(&AssetPanel::UpdateDirectoryFilesLoop, this);

}

AssetPanel::~AssetPanel()
{
    folder_texture->Release();

    // End the update thread
    stop_flag = true;
    updateThread.join();

	for (Asset* asset : m_Assets)
	{
		if (asset)
			delete asset;
	}
	m_Assets.clear();
}

void AssetPanel::UpdateDirectoryFilesLoop()
{
    while (!stop_flag)
    {
        UpdateDirectoryFiles();

        this_thread::sleep_for(chrono::seconds(2));
    }
}

void AssetPanel::UpdateDirectoryFiles()
{
    directoryFiles.clear();
    for (auto& ptr : filesystem::directory_iterator(m_CurrentDirectory))
    {
        directoryFiles.push_back(pair(ptr.path(), ptr.is_directory()));
    }
}

void AssetPanel::Render()
{
    if (ImGui::Begin("Assets"))
    {
        static float thumbnailSize = 64;

        ImGuiStyle& style = ImGui::GetStyle();

        float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

        ImDrawList* draw_list = ImGui::GetWindowDrawList();

        if (m_CurrentDirectory != filesystem::path(s_AssetsPath))
        {
            if (ImGui::Button("<-"))
            {
                m_CurrentDirectory = m_CurrentDirectory.parent_path();
                UpdateDirectoryFiles();
            }
        }

        ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 32, 128);

        for (auto& directoryFileIter : filesystem::directory_iterator(m_CurrentDirectory))
        {
            const auto& path = directoryFileIter.path();
            auto relativePath = filesystem::relative(path, s_AssetsPath);
            string filename = relativePath.filename().string();

            ImGui::BeginGroup();
            ImGui::ImageButton((void*)folder_texture, { thumbnailSize, thumbnailSize });

            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                if (directoryFileIter.is_directory())
                {
                    m_CurrentDirectory /= path.filename();
                    UpdateDirectoryFiles();
                }
                else
                {

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


            // organize layout of items
            float last_button_x2 = ImGui::GetItemRectMax().x;
            float next_button_x2 = last_button_x2 + style.ItemSpacing.x + thumbnailSize;
            //if (i + 1 < gameObjects.size() && next_button_x2 < window_visible_x2)
            if (next_button_x2 < window_visible_x2)
                ImGui::SameLine();
        }
    }
    ImGui::End();
}