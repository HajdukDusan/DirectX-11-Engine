#pragma once
#include "Core/Renderer/Controllers/scenerenderclass.h"
#include "GUI/guiclass.h"
#include "Core/Utils/system/inputclass.h"
#include "Core/Scene/Controllers/GameManager.h"
#include <vector>


const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = false;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class Engine
{
public:
	Engine();
	bool Initialize(HINSTANCE hInstance, WNDCLASSEX wc, HWND hwnd, int ScreenHeight, int ScreenWidth);
	bool Render();
	~Engine();

	D3DClass* getDirectXManager();

private:
	D3DClass*			m_DirectXManager;
	SceneRenderClass*	m_GameScene;
	GuiClass*			m_GUI;
	InputClass*			m_GameInputHandler;
	GameManager*		m_GameManager;

	Camera*					m_SceneCamera;
	Transform*				m_CameraTransform;
	std::vector<Camera*>	m_GameCameras;

	RenderTextureClass* m_SceneViewTexture;
	RenderTextureClass* m_GameViewTexture;
};

