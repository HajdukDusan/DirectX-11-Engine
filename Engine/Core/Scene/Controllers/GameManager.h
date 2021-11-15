#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#pragma once
#include <vector>

#include "../Entity/Entity.h"
#include "../../Core/Renderer/DirectX/d3dclass.h"
#include "../../Core/Renderer/Shaders/PBR/PBRshaderclass.h"
#include "../Entity/Components/CameraComponent.h"
#include "../Entity/Components/Light/lightclass.h"

#include "../Materials/PBRShaderMaterial.h"
#include "../Materials/Material.h"
#include "../../Core/Utils/system/timerclass.h"
#include "../../Renderer/Utils/Mesh.h"

using namespace std;

class GameManager
{
public:
	GameManager(D3DClass* DirectXManager, HWND hwnd);
	~GameManager();

	vector<Entity*>& GetEntities();
	vector<Mesh*>& GetMeshes();
	vector<Material*>& GetMaterials();

	const char* MessageForConsole;

private:
	vector<Entity*>	m_Entities;
	vector<Mesh*> m_Meshes;
	vector<Material*> m_Materals;
public:
	Camera* m_selectedCamera;

	PBRShaderClass* m_PBRShader;

	CameraComponent* m_Camera;
	LightClass* m_Light;

	TimerClass* m_Timer;
	float m_PrepareSceneTime;
	float m_PresentSceneTime;

};

#endif

