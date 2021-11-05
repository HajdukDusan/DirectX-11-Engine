#include "GameManager.h"


GameManager::GameManager(D3DClass* DirectXManager, HWND hwnd)
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


	// INIT SHADERS
	m_ShaderManager = new ShaderManagerClass;
	// Initialize the shader manager object.
	if (!m_ShaderManager->Initialize(DirectXManager->GetDevice(), hwnd))
	{
		MessageForConsole = "[error] Could not initialize the shader manager.";
	}


	// PUSH CAMERA TO BE THE FIRST GAMEOBJECT
	m_GameObjects.push_back(m_Camera);

	//BARREL
	ModelClass* barrelModel = new ModelClass();
	if (!barrelModel->Initialize(DirectXManager->GetDevice(), DirectXManager->GetDeviceContext(), false, "../Engine/data/barrel.obj"))
	{
		MessageForConsole = "[error] Could not initialize the model object.";
	};

	Material* barrelMaterial = (Material*) new PBRShaderMaterial(
		m_ShaderManager->getPBRShader(),
		DirectXManager->GetDevice(),
		DirectXManager->GetDeviceContext(),
		"BarrelMaterial",
		"../Engine/data/drum1_base_color.tga",
		"../Engine/data/drum1_normal.tga",
		"../Engine/data/drum1_specular.tga");

	m_GameObjects.push_back(new GameObject(
		"MyBarrel",
		barrelModel,
		barrelMaterial
	));
	m_Models.push_back(barrelModel);
	m_Materals.push_back(barrelMaterial);


	//GASS TANK
	ModelClass* gassTankModel = new ModelClass();
	if (!gassTankModel->Initialize(DirectXManager->GetDevice(), DirectXManager->GetDeviceContext(), false, "../Engine/data/Gass Tank/gass_tank.obj"))
	{
		MessageForConsole = "[error] Could not initialize the model object.";
	};

	Material* gassTankMaterial = (Material*) new PBRShaderMaterial(
		m_ShaderManager->getPBRShader(),
		DirectXManager->GetDevice(),
		DirectXManager->GetDeviceContext(),
		"GassTankMaterial",
		"../Engine/data/Gass Tank/gasTank_color.tga",
		"../Engine/data/Gass Tank/gasTank_normal.tga",
		"../Engine/data/Gass Tank/gasTank_specular.tga");

	m_GameObjects.push_back(new GameObject(
		"MyGassTank",
		gassTankModel,
		gassTankMaterial
	));
	m_Models.push_back(gassTankModel);
	m_Materals.push_back(gassTankMaterial);


	// Setup The Timer Class
	m_Timer = new TimerClass();
	if (!m_Timer->Initialize())
	{
		MessageForConsole = "[error] Could not initialize the timer.";
	}
}

vector<Transform*>& GameManager::GetGameObjects() {
	return m_GameObjects;
}
vector<ModelClass*>& GameManager::GetModels() {
	return m_Models;
}
vector<Material*>& GameManager::GetMaterials() {
	return m_Materals;
}

GameManager::~GameManager()
{
	delete[] MessageForConsole;

	delete m_Timer;

	//delete m_Camera;
	delete m_Light;

	// delete the game objects
	for (Transform* object : m_GameObjects) {
		if (object)
			delete object;
	}
	m_GameObjects.clear();


	// delete the models
	for (ModelClass* object : m_Models) {
		if (object)
			delete object;
	}
	m_Models.clear();

	// delete the materials
	for (Material* object : m_Materals) {
		if (object)
			delete object;
	}
	m_Materals.clear();

	// delete all the shaders
	m_ShaderManager->Shutdown();
}