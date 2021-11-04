#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#pragma once
#include <vector>

#include "GameObject.h"
#include "d3dclass.h"
#include "Material.h"
#include "lightclass.h"
#include "cameraclass.h"

#include "shadermanagerclass.h"
#include "PBRShaderMaterial.h"

using namespace std;

class GameManager
{
public:
	GameManager(D3DClass* DirectXManager, HWND hwnd);
	~GameManager();

	vector<GameObject*>& GetGameObjects();
	vector<ModelClass*>& GetModels();
	vector<Material*>& GetMaterials();


	const char* MessageForConsole;

private:
	vector<GameObject*>	m_GameObjects;
	vector<ModelClass*> m_Models;
	vector<Material*> m_Materals;
public:
	ShaderManagerClass* m_ShaderManager;

	CameraClass* m_Camera;
	LightClass* m_Light;

};

#endif

