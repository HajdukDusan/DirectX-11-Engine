#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#pragma once
#include <vector>

#include "../GameObjects/Components/Model/GameObject.h"
#include "../../Core/Renderer/DirectX/d3dclass.h"
#include "../../Core/Renderer/Shaders/PBR/PBRshaderclass.h"
#include "../GameObjects/Components/Camera/cameraclass.h"
#include "../GameObjects/Components/Light/lightclass.h"

#include "../Materials/PBRShaderMaterial.h"
#include "../Materials/Material.h"
#include "../../Core/Utils/system/timerclass.h"

using namespace std;

class GameManager
{
public:
	GameManager(D3DClass* DirectXManager, HWND hwnd);
	~GameManager();

	vector<Transform*>& GetGameObjects();
	vector<ModelClass*>& GetModels();
	vector<Material*>& GetMaterials();


	const char* MessageForConsole;

private:
	vector<Transform*>	m_GameObjects;
	vector<ModelClass*> m_Models;
	vector<Material*> m_Materals;
public:

	PBRShaderClass* m_PBRShader;

	CameraClass* m_Camera;
	LightClass* m_Light;

	TimerClass* m_Timer;
	float m_PrepareSceneTime;
	float m_PresentSceneTime;

};

#endif

