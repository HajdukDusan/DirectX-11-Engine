#include "GameManager.h"


GameManager::GameManager(D3DClass* DirectXManager)
{
	//CAMERA
	m_Camera = new CameraClass;
	// Set the initial position of the camera and build the matrices needed for rendering.
	m_Camera->SetPosition(-8.0f, 7.0f, -8.0f);
	m_Camera->SetRotation(20.0f, 45.0f, 0.0f);
	//m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	//m_Camera->SetRotation(0.0f, 0.0f, 0.0f);
	m_Camera->Render();
	m_Camera->RenderBaseViewMatrix();

	//LIGHT
	m_Light = new LightClass;
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f); //15% of diffuse light
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);	//white
	m_Light->SetDirection(0.430f, -0.8f, 0.710f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	//BARREL
	ModelClass* barrelModel = new ModelClass();
	if (!barrelModel->Initialize(DirectXManager->GetDevice(), DirectXManager->GetDeviceContext(), false, "../Engine/data/barrel.txt"))
	{
		MessageForConsole = "[error] Could not initialize the model object.";
	};

	Material* barrelMaterial = (Material*) new PBRShaderMaterial(
		DirectXManager->GetDevice(),
		DirectXManager->GetDeviceContext(),
		"BarrelMaterial",
		"../Engine/data/drum1_base_color.tga",
		"../Engine/data/drum1_normal.tga",
		"../Engine/data/drum1_specular.tga",
		2, 10, 2);

	m_GameObjects.push_back(new GameObject(
		"My Barrel",
		barrelModel,
		barrelMaterial
	));


	//GASS TANK
	ModelClass* gassTankModel = new ModelClass();
	if (!gassTankModel->Initialize(DirectXManager->GetDevice(), DirectXManager->GetDeviceContext(), false, "../Engine/data/Gass Tank/gass_tank.txt"))
	{
		MessageForConsole = "[error] Could not initialize the model object.";
	};

	Material* gassTankMaterial = (Material*) new PBRShaderMaterial(
		DirectXManager->GetDevice(),
		DirectXManager->GetDeviceContext(),
		"GassTankMaterial",
		"../Engine/data/Gass Tank/gasTank_color.tga",
		"../Engine/data/Gass Tank/gasTank_normal.tga",
		"../Engine/data/Gass Tank/gasTank_specular.tga");

	m_GameObjects.push_back(new GameObject(
		"My Gass Tank",
		gassTankModel,
		gassTankMaterial
	));
}

vector<GameObject*>& GameManager::GetGameObjects() {
	return m_GameObjects;
}
vector<Material*>& GameManager::GetMaterials() {
	return m_Materals;
}

GameManager::~GameManager()
{
	delete[] MessageForConsole;

	delete m_Camera;
	delete m_Light;

	// delete the materials
	for (Material *object : m_Materals) {
		delete object;
	}
	m_Materals.clear();
	// delete the game objects
	for (GameObject* object : m_GameObjects) {
		delete object;
	}
	m_GameObjects.clear();
}