#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#pragma once
#include <vector>

#include "GameObject.h"
#include "d3dclass.h"
#include "Material.h"
#include "lightclass.h"
#include "cameraclass.h"

#include "PBRShaderMaterial.h"

using namespace std;

class GameManager
{
public:
	GameManager(D3DClass* DirectXManager);
	~GameManager();

	vector<GameObject*>& GetGameObjects();
	vector<Material*>& GetMaterials();


	const char* MessageForConsole;

private:
	vector<GameObject*>	m_GameObjects;
	vector<Material*> m_Materals;

public:
	CameraClass* m_Camera;
	LightClass* m_Light;
};

#endif

