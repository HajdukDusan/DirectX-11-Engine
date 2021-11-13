#include "Engine.h"
#include "Core/Utils/SceneCameraNavigation.h"

Engine::Engine()
{

}

bool Engine::Initialize(HINSTANCE hInstance, WNDCLASSEX wc, HWND hwnd, int ScreenWidth, int ScreenHeight)
{
	// Setup DirectX
	m_DirectXManager = new D3DClass;
	if (!m_DirectXManager->Initialize(ScreenWidth, ScreenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR)) {
		m_DirectXManager->Shutdown();
		::UnregisterClass(wc.lpszClassName, wc.hInstance);
		MessageBox(hwnd, L"Failed to initialize DirectX 11.", L"Error", MB_ICONERROR);
		return false;
	}

	// Setup Scene Renderer
	m_GameScene = new SceneRenderClass(m_DirectXManager, hwnd);

	// Setup Game Input Handler
	//m_GameInputHandler = new InputClass();
	//if (!m_GameInputHandler->Initialize(hInstance, hwnd, ScreenWidth, ScreenHeight)) {
	//	MessageBox(hwnd, L"Cant initialize Game Input Handler.", L"Error", MB_OK);
	//	return false;
	//}

	// Setup The Game Manager
	m_GameManager = new GameManager(m_DirectXManager, hwnd);

	// Setup Engine GUI
	m_GUI = new GuiClass(hwnd, m_DirectXManager, m_GameManager);


	// Setup Scene Camera
	m_CameraTransform = new Transform(
		XMFLOAT3(-8.0f, 8.0f, 0.0f),
		XMFLOAT3(45.0f, 90.0f, 0.0f),
		XMFLOAT3(1.0f, 1.0f, 1.0f)
	);
	m_SceneCamera = new Camera(m_CameraTransform);
	
	// Setup The Textures We Will Render To
	m_SceneViewTexture = new RenderTextureClass;
	if (!m_SceneViewTexture->Initialize(m_DirectXManager->GetDevice(), 1920, 1080))
	{
		MessageBox(hwnd, L"Could not initialize the render texture class.", L"Error", MB_OK);
		return false;
	}
	m_GameViewTexture = new RenderTextureClass;
	if (!m_GameViewTexture->Initialize(m_DirectXManager->GetDevice(), 1920, 1080))
	{
		MessageBox(hwnd, L"Could not initialize the render texture class.", L"Error", MB_OK);
		return false;
	}


	// On Start Get All Cameras From The Camera Components
	for (Entity* entity : m_GameManager->GetEntities())
	{
		for (Component* comp : entity->m_Components)
		{
			if (CameraComponent* camComp = dynamic_cast<CameraComponent*>(comp); camComp)
			{
				m_GameCameras.push_back(camComp->m_Camera);
			}
		}

	}

	return true;
}

bool Engine::Render()
{
	// Update Input States
	//m_GameInputHandler->Frame();

	

	// Scripts That Affect Game Objects Go Here
	if (m_GUI->SceneWindowActive)
		MoveCamera(m_SceneCamera->m_Transform, m_GUI->GetInputHandler());

	// Render Scene View To Texture
	if (!m_GameScene->RenderScene(m_GameManager, m_SceneCamera, m_SceneViewTexture)) {
		return false;
	}

	// Render Game View To Texture
	if (!m_GameScene->RenderScene(m_GameManager, m_GameCameras[0], m_GameViewTexture)) {
		return false;
	}

	// Setup rendering for gui
	m_DirectXManager->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Render the gui, pass the rendered images
	m_GUI->Render(
		m_SceneViewTexture->GetShaderResourceView(),
		m_GameViewTexture->GetShaderResourceView()
	);

	// Present everything
	m_DirectXManager->PresentScene();

	return true;
}

D3DClass* Engine::getDirectXManager() {
	return m_DirectXManager;
}

Engine::~Engine()
{
	//delete m_GameInputHandler;
	delete m_GameViewTexture;
	delete m_SceneViewTexture;

	delete m_CameraTransform;
	delete m_SceneCamera;

	delete m_GameScene;
	delete m_GameManager;
	delete m_GUI;
	m_DirectXManager->Shutdown();
}
