#include "Engine.h"

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
}

bool Engine::Render()
{
	// Update Input States
	//m_GameInputHandler->Frame();

	

	// Scripts That Affect Game Objects Go Here
	MoveCamera((Transform*)m_GameManager->m_Camera, m_GUI->GetInputHandler());

	// Render Game Scene To GUI Texture
	if (!m_GameScene->RenderScene(m_GameManager)) {
		return false;
	}

	// Setup rendering for gui
	m_DirectXManager->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Render the gui, pass the rendered game frame
	m_GUI->Render(m_GameScene->GetTexture());

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
	delete m_GameScene;
	delete m_GameManager;
	delete m_GUI;
	m_DirectXManager->Shutdown();
}
