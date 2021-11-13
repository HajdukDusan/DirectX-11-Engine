#include "GameManager.h"
#include "../Entity/Components/MeshComponent.h"


GameManager::GameManager(D3DClass* DirectXManager, HWND hwnd)
{


	// CAMERA
	// Set the initial position of the camera and build the matrices needed for rendering.
	Transform* cameraTransform = new Transform(
		XMFLOAT3(-8.0f, 8.0f, 0.0f),
		XMFLOAT3(45.0f, 90.0f, 0.0f),
		XMFLOAT3(1.0f, 1.0f, 1.0f));

	Entity* CameraEntity = new Entity("Camera", cameraTransform);
	m_Camera = new CameraComponent(cameraTransform);
	//m_Camera->Render(CameraEntity->m_Transform);

	CameraEntity->m_Components.insert(m_Camera);
	m_Entities.push_back(CameraEntity);


	// PBR SHADER INIT
	m_PBRShader = new PBRShaderClass();
	if (!m_PBRShader->Initialize(DirectXManager->GetDevice(), hwnd))
	{
		MessageForConsole = "[error] Could not initialize the PBR shader.";
	}


	// MATERIALS
	Material* barrelMaterial = (Material*) new PBRShaderMaterial(
		m_PBRShader,
		DirectXManager->GetDevice(),
		DirectXManager->GetDeviceContext(),
		"BarrelMaterial",
		"../Engine/Assets/drum1_base_color.tga",
		"../Engine/Assets/drum1_normal.tga",
		"../Engine/Assets/drum1_specular.tga");

	Material* gassTankMaterial = (Material*) new PBRShaderMaterial(
		m_PBRShader,
		DirectXManager->GetDevice(),
		DirectXManager->GetDeviceContext(),
		"GassTankMaterial",
		"../Engine/Assets/Gass Tank/gasTank_color.tga",
		"../Engine/Assets/Gass Tank/gasTank_normal.tga",
		"../Engine/Assets/Gass Tank/gasTank_specular.tga");
	m_Materals.push_back(barrelMaterial);
	m_Materals.push_back(gassTankMaterial);

	// MESHES
	Mesh* barrelMesh = new Mesh();
	if (!barrelMesh->Initialize(DirectXManager->GetDevice(), DirectXManager->GetDeviceContext(), false, "../Engine/Assets/barrel.obj"))
	{
		MessageForConsole = "[error] Could not initialize the mesh component.";
	};

	Mesh* gassTankMesh = new Mesh();
	if (!gassTankMesh->Initialize(DirectXManager->GetDevice(), DirectXManager->GetDeviceContext(), false, "../Engine/Assets/Gass Tank/gass_tank.obj"))
	{
		MessageForConsole = "[error] Could not initialize the mesh component.";
	};
	m_Meshes.push_back(barrelMesh);
	m_Meshes.push_back(gassTankMesh);

	// BARREL
	Entity* BarrelEntity = new Entity("Barrel", new Transform());
	MeshComponent* barrelMeshComponent = new MeshComponent(barrelMesh, barrelMaterial);
	BarrelEntity->m_Components.insert(barrelMeshComponent);
	m_Entities.push_back(BarrelEntity);

	// GASS TANK
	Entity* GassTankEntity = new Entity("Gass Tank", new Transform());
	MeshComponent* gassTankMeshComponent = new MeshComponent(gassTankMesh, gassTankMaterial);
	GassTankEntity->m_Components.insert(gassTankMeshComponent);
	m_Entities.push_back(GassTankEntity);


	// Setup The Timer Class
	m_Timer = new TimerClass();
	if (!m_Timer->Initialize())
	{
		MessageForConsole = "[error] Could not initialize the timer.";
	}

	//LIGHT
	m_Light = new LightClass;
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f); //15% of diffuse light
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);	//white
	m_Light->SetDirection(0.430f, -0.8f, 0.710f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);
}

vector<Entity*>& GameManager::GetEntities() {
	return m_Entities;
}
vector<Mesh*>& GameManager::GetMeshes() {
	return m_Meshes;
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
	for (Entity* object : m_Entities) {
		delete object;
	}
	m_Entities.clear();


	// delete the models
	for (Mesh* object : m_Meshes) {
		if (object)
			delete object;
	}
	m_Meshes.clear();

	// delete the materials
	for (Material* object : m_Materals) {
		if (object)
			delete object;
	}
	m_Materals.clear();

	// delete all the shaders
	m_PBRShader->Shutdown();
}