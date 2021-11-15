#include "guiclass.h"
#include "ImGui/imgui_internal.h"
#include "../Core/Scene/Entity/Components/MeshComponent.h"
#include "Styles.h"

#define IM_MAX(A, B)            (((A) >= (B)) ? (A) : (B))

GuiClass::GuiClass(HWND hwnd, D3DClass* Direct3D, GameManager* gameManager) 
{
    m_GameManager = gameManager;
    m_DirectX = Direct3D;

    // Initialize the components
    m_AssetPanel = new AssetPanel(m_DirectX);
    m_console = new Console();
    m_ScenePanel = new ScenePanel(m_DirectX, m_GameManager, m_console);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // dont save pass state
    //io.IniFilename = NULL;

    ImGui::StyleColorsDark();
    
    Style::SetStyle(DARK);

    io.Fonts->AddFontFromFileTTF("../Engine/data/font/Roboto-Medium.ttf", 14.0f);
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

    PrintConsole("[info] Initialization Complete..");
}

GuiClass::~GuiClass() {

    // Delete compononets
    delete m_AssetPanel;
    delete m_console;
    delete m_ScenePanel;

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

ImGuiIO& GuiClass::getIO() {

    return ImGui::GetIO();
}


void GuiClass::Render(ID3D11ShaderResourceView* sceneTexture, ID3D11ShaderResourceView* gameTexture) {

    bool t = true;

    vector<Entity*>& entities = m_GameManager->GetEntities();
    vector<Mesh*>& models = m_GameManager->GetMeshes();
    vector<Material*> & materials = m_GameManager->GetMaterials();

    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    DockingAndMenuBar(&t);

    GameWindowVisible = m_ScenePanel->RenderGame(gameTexture);

    SceneWindowVisible = m_ScenePanel->RenderScene(sceneTexture, &SceneWindowActive);

    ShowSceneObjects(entities);

    ShowLightWindow(m_GameManager->m_Light);

    ShowCameraWindow(m_GameManager->m_Camera);

    ImGui::ShowDemoWindow(&t);

    // RENDER COMPONENTS
    m_AssetPanel->Render();

    // console
    if (m_GameManager->MessageForConsole)
        PrintConsole(m_GameManager->MessageForConsole);

    m_console->Render("Console", &t);

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



void GuiClass::ShowSceneObjects(vector<Entity*>& entities)
{
    if (ImGui::Begin("Scene Objects"))
    {
        if (ImGui::IsWindowHovered())
            ImGui::SetWindowFocus();

        // Left
        static int selected = -1;
        {
            ImGui::BeginChild("objectsInScene", ImVec2(150, 0), true);

            for (int i = 0; i < entities.size(); i++)
            {
                ImGui::PushID("SceneGameObjectId-" + i);

                if (ImGui::Selectable(entities[i]->m_Name, selected == i)) {
                    selected = i;
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

                        Entity* entity_ptr = entities[i];
                        entities.erase(entities.begin() + i);
                        PrintConsole("[info] Entity deleted.");
                        delete entity_ptr;
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
            
            if (selected != -1 && entities[selected] != nullptr) {
                ShowInspectorWindow(entities[selected]);
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

static void ShowMeshInspectorSlot(MeshComponent* meshComp)
{
    if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text("Vertices: %d", meshComp->m_Mesh->m_OriginalVertexCount);
        ImGui::Text("Normals:  %d", meshComp->m_Mesh->m_NormalCount);
        ImGui::Text("Faces:  %d", meshComp->m_Mesh->m_FaceCount);
        ImGui::Text("Texture Cords:  %d", meshComp->m_Mesh->m_UVCount);

        ImGui::Separator();

        ImGui::Text("Material: %s", meshComp->m_Material->m_Name);
    }
}

static void ShowCameraInspectorSlot(CameraComponent* camComp)
{
    if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text("Screen Depth");
        ImGui::Text("Screen Near");
        ImGui::Text("VSYNC?");
    }
}

void GuiClass::ShowInspectorWindow(Entity* entity) {

    if (ImGui::Begin("Inspector"))
    {
        if (ImGui::IsWindowHovered())
            ImGui::SetWindowFocus();

        if (entity != nullptr) {

            ShowTransformInspectorSlot(entity->m_Transform);

            for (Component* comp : entity->m_Components)
            {
                if (MeshComponent* meshComp = dynamic_cast<MeshComponent*>(comp); meshComp)
                {
                    ShowMeshInspectorSlot(meshComp);
                }
                if (CameraComponent* camComp = dynamic_cast<CameraComponent*>(comp); camComp)
                {
                    ShowCameraInspectorSlot(camComp);
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
        }
    }
    ImGui::End();
}
void GuiClass::ShowCameraWindow(CameraComponent* camera) {

    
    if (ImGui::Begin("Camera Window"))
    {
        if (ImGui::IsWindowHovered())
            ImGui::SetWindowFocus();
    }
    ImGui::End();
}

void GuiClass::PrintConsole(const char* msg)
{
    m_console->AddLog("%s", msg);
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
            if (ImGui::BeginMenu("Preferences.."))
            {
                if (ImGui::BeginMenu("Style"))
                {
                    if (ImGui::Selectable("Dark"))
                        Style::SetStyle(DARK);
                    if (ImGui::Selectable("Corporate"))
                        Style::SetStyle(CORPORATE);
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) {}
            if (ImGui::MenuItem("Save As..")) {}
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