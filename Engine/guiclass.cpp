#include "guiclass.h"
#include "ImGui/imgui_internal.h"

#define IM_MAX(A, B)            (((A) >= (B)) ? (A) : (B))

GuiClass::GuiClass(HWND hwnd, D3DClass* Direct3D, GameManager* gameManager) {
    // Setup the gameObject manager
    m_GameManager = gameManager;

    // Initialize the components
    m_AssetPanel = new AssetPanel(Direct3D);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // dont save pass state
    //io.IniFilename = NULL;

    ImGui::StyleColorsDark();
    
    // set the "corporate" style
    SetStyle();

    io.Fonts->AddFontFromFileTTF("../Engine/data/font/Roboto-Medium.ttf", 16.0f);
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.WantCaptureKeyboard = true;

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(Direct3D->GetDevice(), Direct3D->GetDeviceContext());

    m_DirectX = Direct3D;

    PrintConsole("[info] Initialization Complete..");
}

GuiClass::~GuiClass() {

    // Delete compononets
    delete m_AssetPanel;

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

ImGuiIO& GuiClass::getIO() {

    return ImGui::GetIO();
}

void GuiClass::SetStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    /// 0 = FLAT APPEARENCE
    /// 1 = MORE "3D" LOOK
    int is3D = 1;

    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.12f, 0.12f, 0.12f, 0.71f);
    colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.42f, 0.42f, 0.42f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.42f, 0.42f, 0.42f, 0.40f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.67f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.17f, 0.17f, 0.17f, 0.90f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.335f, 0.335f, 0.335f, 1.000f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.24f, 0.24f, 0.24f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.54f, 0.54f, 0.54f, 0.35f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.52f, 0.52f, 0.52f, 0.59f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.76f, 0.76f, 0.76f, 0.77f);
    colors[ImGuiCol_Separator] = ImVec4(0.000f, 0.000f, 0.000f, 0.137f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.700f, 0.671f, 0.600f, 0.290f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.702f, 0.671f, 0.600f, 0.674f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.73f, 0.73f, 0.73f, 0.35f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);

    style.PopupRounding = 3;

    style.WindowPadding = ImVec2(4, 4);
    style.FramePadding = ImVec2(6, 4);
    style.ItemSpacing = ImVec2(6, 2);

    style.ScrollbarSize = 18;

    style.WindowBorderSize = 1;
    style.ChildBorderSize = 1;
    style.PopupBorderSize = 1;
    style.FrameBorderSize = is3D;

    style.WindowRounding = 3;
    style.ChildRounding = 3;
    style.FrameRounding = 3;
    style.ScrollbarRounding = 2;
    style.GrabRounding = 3;

    style.ColorButtonPosition = 0;

#ifdef IMGUI_HAS_DOCK 
    style.TabBorderSize = is3D;
    style.TabRounding = 3;

    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
    colors[ImGuiCol_DockingPreview] = ImVec4(0.85f, 0.85f, 0.85f, 0.28f);

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
#endif
}


void GuiClass::Render(ID3D11ShaderResourceView* gameSceneTexture) {

    bool t = true;

    vector<Transform*>& gameObjects = m_GameManager->GetGameObjects();
    vector<ModelClass*>& models = m_GameManager->GetModels();
    vector<Material*> & materials = m_GameManager->GetMaterials();

    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // uses a lot of fps
    DockingAndMenuBar(&t);

    ShowSceneWindow(gameSceneTexture);

    ShowSceneObjects(gameObjects);

    ShowLightWindow(m_GameManager->m_Light);

    ShowCameraWindow(m_GameManager->m_Camera);

    ImGui::ShowDemoWindow(&t);

    // RENDER COMPONENTS
    m_AssetPanel->Render();

    // console
    if (m_GameManager->MessageForConsole)
        PrintConsole(m_GameManager->MessageForConsole);
    ShowConsole(&t);

    ImGui::Render();

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

ImGuiIO* GuiClass::GetInputHandler()
{
    return &ImGui::GetIO();
}

void GuiClass::ShowAssetsWindow()
{
    
}


void GuiClass::ShowConsole(bool* p_open)
{
    console.Draw("Console", p_open);
}

void GuiClass::ShowSceneWindow(ID3D11ShaderResourceView* sceneView)
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
                PrintConsole("[info] Wireframe enabled.");
                //m_DirectX->EnableWireframe();
            }
            else {
                PrintConsole("[info] Wireframe disabled.");
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

void GuiClass::ShowSceneObjects(vector<Transform*>& gameObjects)
{
    if (ImGui::Begin("Scene Objects"))
    {
        // Left
        static int selected = -1;
        {
            ImGui::BeginChild("objectsInScene", ImVec2(150, 0), true);

            for (int i = 0; i < gameObjects.size(); i++)
            {
                ImGui::PushID("SceneGameObjectId-" + i);
                if (GameObject* go_ptr = dynamic_cast<GameObject*>(gameObjects[i]); go_ptr)
                {
                    if (ImGui::Selectable(go_ptr->m_Name, selected == i)) {
                        selected = i;
                    }
                }
                else if (CameraClass* cam_ptr = dynamic_cast<CameraClass*>(gameObjects[i]); cam_ptr)
                {
                    if (ImGui::Selectable("Camera", selected == i)) {
                        selected = i;
                    }
                }
                
                //if (ImGui::Button("File Menu.."))
                //    ImGui::OpenPopup("my_file_popup");
                //if (ImGui::BeginPopup("my_file_popup"))
                //{
                //    ShowExampleMenuFile();
                //    ImGui::EndPopup();
                //}


                if (ImGui::BeginPopupContextItem())
                {
                    // get item with i
                    
                    ImGui::MenuItem("(demo menu)", NULL, false, false);
                    if (ImGui::MenuItem("New")) {}
                    if (ImGui::MenuItem("Open", "Ctrl+O")) {}
                    if (ImGui::BeginMenu("Open Recent"))
                    {
                        ImGui::MenuItem("fish_hat.c");
                        ImGui::MenuItem("fish_hat.inl");
                        ImGui::MenuItem("fish_hat.h");
                        if (ImGui::BeginMenu("More.."))
                        {
                            ImGui::MenuItem("Hello");
                            ImGui::MenuItem("Sailor");
                            if (ImGui::BeginMenu("Recurse.."))
                            {
                                ImGui::EndMenu();
                            }
                            ImGui::EndMenu();
                        }
                        ImGui::EndMenu();
                    }
                    if (ImGui::MenuItem("Save", "Ctrl+S")) {}
                    if (ImGui::MenuItem("Save As..")) {}

                    ImGui::Separator();
                    if (ImGui::BeginMenu("Options"))
                    {
                        static bool enabled = true;
                        ImGui::MenuItem("Enabled", "", &enabled);
                        ImGui::BeginChild("child", ImVec2(0, 60), true);
                        for (int i = 0; i < 10; i++)
                            ImGui::Text("Scrolling Text %d", i);
                        ImGui::EndChild();
                        static float f = 0.5f;
                        static int n = 0;
                        ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
                        ImGui::InputFloat("Input", &f, 0.1f);
                        ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
                        ImGui::EndMenu();
                    }

                    if (ImGui::BeginMenu("Colors"))
                    {
                        float sz = ImGui::GetTextLineHeight();
                        for (int i = 0; i < ImGuiCol_COUNT; i++)
                        {
                            const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
                            ImVec2 p = ImGui::GetCursorScreenPos();
                            ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
                            ImGui::Dummy(ImVec2(sz, sz));
                            ImGui::SameLine();
                            ImGui::MenuItem(name);
                        }
                        ImGui::EndMenu();
                    }

                    // Here we demonstrate appending again to the "Options" menu (which we already created above)
                    // Of course in this demo it is a little bit silly that this function calls BeginMenu("Options") twice.
                    // In a real code-base using it would make senses to use this feature from very different code locations.
                    if (ImGui::BeginMenu("Options")) // <-- Append!
                    {
                        static bool b = true;
                        ImGui::Checkbox("SomeOption", &b);
                        ImGui::EndMenu();
                    }

                    if (ImGui::BeginMenu("Disabled", false)) // Disabled
                    {
                        IM_ASSERT(0);
                    }
                    if (ImGui::MenuItem("Checked", NULL, true)) {}
                    if (ImGui::MenuItem("Remove", "Del")) {
                        
                        if (selected == i) selected = -1;

                        Transform* go_ptr = gameObjects[i];
                        gameObjects.erase(gameObjects.begin() + i);
                        PrintConsole("[info] Object deleted.");
                        delete go_ptr;
                    }

                    // CHANGE NAME
                    //static char name[200];
                    //strcpy_s(name, sizeof(name), gameObjects[i]->m_Name);

                    //ImGui::InputText("##edit", name, IM_ARRAYSIZE(name));
                    //if (ImGui::Button("Save"))
                    //{
                    //    ImGui::CloseCurrentPopup();
                    //    //delete[] gameObjects[i]->m_Name;
                    //    gameObjects[i]->m_Name = name;
                    //}
                    ImGui::EndPopup();
                }

                ImGui::PopID();

            }
            
            if (selected != -1 && gameObjects[selected] != nullptr) {
                ShowInspectorWindow(gameObjects[selected]);
            }
            else
                ShowInspectorWindow(nullptr);
               


            ImGui::EndChild();
        }
        ImGui::SameLine();
    }
    ImGui::End();
}

void GuiClass::ShowLightWindow(LightClass* Light)
{
    ImGui::Begin("Light Window");

    ImGui::PushID("ambientColor");
    ImGui::Text("Ambient Color");
    ImGui::ColorEdit3("", (float*)&Light->GetAmbientColor());
    ImGui::PopID();

    ImGui::Separator();

    ImGui::PushID("diffuseColor");
    ImGui::Text("Diffuse Color");
    ImGui::ColorEdit3("", (float*)&Light->GetDiffuseColor());
    ImGui::PopID();

    ImGui::Separator();

    ImGui::PushID("specularColor");
    ImGui::Text("Specular Color");
    ImGui::ColorEdit3("", (float*)&Light->GetSpecularColor());
    ImGui::PopID();


    ImGui::Separator();

    float* tmp = (float*)&Light->GetDirection();

    ImGui::Text("Direction");
    ImGui::PushID("dx");
    ImGui::PushItemWidth(100.f);
    ImGui::Text("X"); ImGui::SameLine();
    ImGui::DragFloat("", &tmp[0], 0.01f, -1.f, 1.f);
    ImGui::PopID();
    ImGui::SameLine();
    ImGui::PushID("dy");
    ImGui::PushItemWidth(100.f);
    ImGui::Text("Y"); ImGui::SameLine();
    ImGui::DragFloat("", &tmp[1], 0.01f, -1.f, 1.f);
    ImGui::PopID();
    ImGui::SameLine();
    ImGui::PushID("dz");
    ImGui::PushItemWidth(100.f);
    ImGui::Text("Z"); ImGui::SameLine();
    ImGui::DragFloat("", &tmp[2], 0.01f, -1.f, 1.f);
    ImGui::PopID();

    ImGui::End();
}


float oneThirdWidth = 100.0f;

static void ShowTransformInspectorSlot(Transform* transform)
{
    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
    {
        //ImGui::Checkbox("Is Static", &gameObject->m_Model->Static);
        //ImGui::Separator();

        ImGui::Text("Position");
        ImGui::PushID("px");
        ImGui::PushItemWidth(oneThirdWidth);
        ImGui::Text("X"); ImGui::SameLine();
        ImGui::DragFloat("", &transform->translation.x, 0.01f);
        ImGui::PopID();
        ImGui::SameLine();
        ImGui::PushID("py");
        ImGui::PushItemWidth(oneThirdWidth);
        ImGui::Text("Y"); ImGui::SameLine();
        ImGui::DragFloat("", &transform->translation.y, 0.01f);
        ImGui::PopID();
        ImGui::SameLine();
        ImGui::PushID("pz");
        ImGui::PushItemWidth(oneThirdWidth);
        ImGui::Text("Z"); ImGui::SameLine();
        ImGui::DragFloat("", &transform->translation.z, 0.01f);
        ImGui::PopID();

        ImGui::Separator();

        ImGui::Text("Rotation");
        ImGui::PushID("rx");
        ImGui::PushItemWidth(oneThirdWidth);
        ImGui::Text("X"); ImGui::SameLine();
        ImGui::DragFloat("", &transform->rotation.x, 0.01f);
        ImGui::PopID();
        ImGui::SameLine();
        ImGui::PushID("ry");
        ImGui::PushItemWidth(oneThirdWidth);
        ImGui::Text("Y"); ImGui::SameLine();
        ImGui::DragFloat("", &transform->rotation.y, 0.01f);
        ImGui::PopID();
        ImGui::SameLine();
        ImGui::PushID("rz");
        ImGui::PushItemWidth(oneThirdWidth);
        ImGui::Text("Z"); ImGui::SameLine();
        ImGui::DragFloat("", &transform->rotation.z, 0.01f);
        ImGui::PopID();

        ImGui::Separator();

        // Dont show size if it upcasts to camera
        if (CameraClass* cam_ptr = dynamic_cast<CameraClass*>(transform); !cam_ptr)
        {
            ImGui::Text("Scale");
            ImGui::PushID("sx");
            ImGui::PushItemWidth(oneThirdWidth);
            ImGui::Text("X"); ImGui::SameLine();
            ImGui::DragFloat("", &transform->scale.x, 0.01f, 0.0f, 100000.0f);

            ImGui::PopID();
            ImGui::SameLine();
            ImGui::PushID("sy");
            ImGui::PushItemWidth(oneThirdWidth);
            ImGui::Text("Y"); ImGui::SameLine();
            ImGui::DragFloat("", &transform->scale.y, 0.01f, 0.0f, 100000.0f);
            ImGui::PopID();
            ImGui::SameLine();
            ImGui::PushID("sz");
            ImGui::PushItemWidth(oneThirdWidth);
            ImGui::Text("Z"); ImGui::SameLine();
            ImGui::DragFloat("", &transform->scale.z, 0.01f, 0.0f, 100000.0f);
            ImGui::PopID();
        }
    }
}

static void ShowMaterialInspectorSlot(Material* material)
{
    if (PBRShaderMaterial* pbr = dynamic_cast<PBRShaderMaterial*>(material); pbr) {
        if (ImGui::CollapsingHeader("PBR Material", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Normal Map:");
            ImGui::PushID("normal_map_strength");
            //ImGui::Text("Strength"); ImGui::SameLine();
            ImGui::LabelText("", "Strength"); ImGui::SameLine();
            ImGui::SliderFloat("", &pbr->normalStrength, 0.0f, 3.0f);
            ImGui::PopID();
            ImGui::Separator();


            ImGui::Text("Specular Map:");
            ImGui::PushID("specular_map_focus");
            //ImGui::Text("Focus"); ImGui::SameLine();
            ImGui::LabelText("", "Focus"); ImGui::SameLine();
            ImGui::SliderFloat("", &pbr->specularFocus, 0.0f, 10.0f);
            ImGui::PopID();
            ImGui::PushID("specular_map_strength");
            //ImGui::Text("Strength"); ImGui::SameLine();
            ImGui::LabelText("", "Strength"); ImGui::SameLine();
            ImGui::SliderFloat("", &pbr->specularStrenght, 0.0f, 2.0f);
            ImGui::PopID();
        }
    }
    else {

    }
}

static void ShowModelInspectorSlot(ModelClass* model)
{
    if (ImGui::CollapsingHeader("Model", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text("Vertices: %d", model->m_OriginalVertexCount);
        ImGui::Text("Normals:  %d", model->m_NormalCount);
        ImGui::Text("Faces:  %d", model->m_FaceCount);
        ImGui::Text("Texture Cords:  %d", model->m_UVCount);
    }
}

void GuiClass::ShowInspectorWindow(Transform* transform) {

    ImGui::Begin("Inspector");

    if (transform != nullptr) {

        ShowTransformInspectorSlot(transform);

        if (GameObject* gameObject = dynamic_cast<GameObject*>(transform); gameObject)
        {
            ShowMaterialInspectorSlot(gameObject->m_Material);
            ShowModelInspectorSlot(gameObject->m_Model);
        }



        //if (Model->m_colorShader) {
        //    if (ImGui::CollapsingHeader("Color Shader", ImGuiTreeNodeFlags_DefaultOpen))
        //    {
        //        ImGui::Text("Color:");
        //        ImGui::PushID("object_color");
        //        ImGui::PushItemWidth(oneThirdWidth * 3);
        //        ImGui::ColorEdit3("", (float*)&Model->m_colorShader->color);
        //        ImGui::PopID();
        //    }
        //}

    }
    ImGui::End();
}
void GuiClass::ShowCameraWindow(CameraClass* camera) {

    
    if (ImGui::Begin("Camera Window"))
    {

    }
    ImGui::End();
}

void GuiClass::ShowStatOverlay(bool* p_open)
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

void GuiClass::PrintConsole(const char* msg)
{
    console.AddLog("%s", msg);
}

void GuiClass::ShowLog(bool* p_open)
{
    static GuiClass::Log log;
    // For the demo: add a debug button _BEFORE_ the normal log window contents
    // We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
    // Most of the contents of the window will be added by the log.Draw() call.
    ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
    ImGui::Begin("Log", p_open);
    if (ImGui::SmallButton("[Debug] Add 5 entries"))
    {
        static int counter = 0;
        const char* categories[3] = { "info", "warn", "error" };
        const char* words[] = { "Bumfuzzled", "Cattywampus", "Snickersnee", "Abibliophobia", "Absquatulate", "Nincompoop", "Pauciloquent" };
        for (int n = 0; n < 5; n++)
        {
            const char* category = categories[counter % IM_ARRAYSIZE(categories)];
            const char* word = words[counter % IM_ARRAYSIZE(words)];
            log.AddLog("[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
                ImGui::GetFrameCount(), category, ImGui::GetTime(), word);
            counter++;
        }
    }
    ImGui::End();

    // Actually call in the regular Log helper (which will Begin() into the same window as we just did)
    log.Draw("Log", p_open);
}


void GuiClass::DockingAndMenuBar(bool* p_open) {

    //ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiDockNodeFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    
    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("DockSpace", p_open, window_flags);
    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    else
    {
        //ShowDockingDisabledMessage();
    }
    ShowMenuBar();

    ImGui::End();
}


void GuiClass::ShowMenuBar()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("(demo menu)", NULL, false, false);
            if (ImGui::MenuItem("New")) {}
            if (ImGui::MenuItem("Open", "Ctrl+O")) {}
            if (ImGui::BeginMenu("Open Recent"))
            {
                ImGui::MenuItem("fish_hat.c");
                ImGui::MenuItem("fish_hat.inl");
                ImGui::MenuItem("fish_hat.h");
                if (ImGui::BeginMenu("More.."))
                {
                    ImGui::MenuItem("Hello");
                    ImGui::MenuItem("Sailor");
                    if (ImGui::BeginMenu("Recurse.."))
                    {
                        ImGui::EndMenu();
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) {}
            if (ImGui::MenuItem("Save As..")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }


        if (ImGui::BeginMenu("Scene")) {
            if (ImGui::MenuItem("Save")) { PrintConsole("[info] Scene saved."); }

            ImGui::EndMenu();
        }



        if (ImGui::BeginMenu("Object")) {
            if (ImGui::BeginMenu("Add..")) {

                if (ImGui::MenuItem("Empty")) { PrintConsole("[info] Added empty object to the scene."); }

                //if (ImGui::MenuItem("Cube")) {
                //    if (!m_GameManager->LoadObject("cube.txt")) { PrintConsole("[error] Could not load the cube object."); }
                //    else { PrintConsole("[info] Added cube object to the scene."); }
                //};

                //if (ImGui::MenuItem("Sphere")) {
                //    if (!m_GameManager->LoadObject("sphere.txt")) { PrintConsole("[error] Could not load the sphere object."); }
                //    else { PrintConsole("[info] Added sphere object to the scene."); }
                //};

                //if (ImGui::MenuItem("Plane")) {
                //    if (!m_GameManager->LoadObject("plane.txt")) { PrintConsole("[error] Could not load the plane object."); }
                //    else { PrintConsole("[info] Added plane object to the scene."); }
                //}

                ImGui::EndMenu();
            }


            
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}