#include "scenerenderclass.h"

SceneRenderClass::SceneRenderClass(D3DClass* Direct3D, HWND hwnd) {

	m_DirectXManager = Direct3D;

	// Create the position object.
	m_Position = new PositionClass;

	// Set the initial position and rotation.
	//m_Position->SetPosition(-8.0f, 7.0f, -8.0f);
	//m_Position->SetRotation(20.0f, 45.0f, 0.0f);

	// CREATE THE GRID
	m_Terrain = new TerrainClass;
	// Initialize the terrain object.
	if(!m_Terrain->Initialize(Direct3D->GetDevice(), 10, XMFLOAT4(0.5f, 0.5f, 0.5f, 0.0f)))
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		exit(-1);
	}


	// CREATE THE ARROWS OBJECT
	m_Arrows = new ArrowsClass;

	if(!m_Arrows->Initialize(Direct3D->GetDevice()))
	{
		MessageBox(hwnd, L"Could not initialize the xyz arrows object.", L"Error", MB_OK);
		exit(-1);
	}





	// CREATE THE SHADER MANAGER OBJECT
	m_ShaderManager = new ShaderManagerClass;
	// Initialize the shader manager object.
	if(!m_ShaderManager->Initialize(Direct3D->GetDevice(), hwnd))
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		exit(-1);
	}

	// RENDER TO TEXTURE
	m_RenderTexture = new RenderTextureClass;

	// Initialize the render to texture object.
	if(!m_RenderTexture->Initialize(Direct3D->GetDevice(), 1920, 1080))
	{
		MessageBox(hwnd, L"Could not render the scene to texture.", L"Error", MB_OK);
		exit(-1);
	}

}

bool SceneRenderClass::LoadObject(const char* filename) {

	//m_Models.push_back(new ModelClass);

	//string stmp("../Engine/data/SimpleObjects/");
	//stmp += filename;

	//int newSize = strlen(filename) - 4;
	//char* name = new char[newSize];
	//strncpy_s(name, sizeof(name), filename, newSize);
	//
	//m_ColorMaterials.push_back(new ColorShaderMaterial(m_DirectX->GetDevice(), m_DirectX->GetDeviceContext(), stmp.c_str(), XMFLOAT4(1, 1, 1, 1)));
	//m_Models[m_Models.size() - 1]->SetColorShader(m_ColorMaterials[m_ColorMaterials.size() - 1]);

	//if (!m_Models[m_Models.size() - 1]->Initialize(name, m_DirectX->GetDevice(), m_DirectX->GetDeviceContext(), false, stmp.c_str(), new ModelClass::Transform()))
	//{
	//	return false;
	//}

	return true;
}

void SceneRenderClass::SaveScene()
{

}

SceneRenderClass::~SceneRenderClass() {

	if (m_RenderTexture)
	{
		m_RenderTexture->Shutdown();
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}

	if (m_Arrows)
	{
		m_Arrows->Shutdown();
		delete m_Arrows;
		m_Arrows = 0;
	}
	// Release the terrain object.
	if (m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}

	if (m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	for (ColorShaderMaterial* m : m_ColorMaterials) {
		delete m;
	}
	m_ColorMaterials.clear();
}


bool SceneRenderClass::RenderScene(GameManager* GameManager) {

	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMatrix, staticWorldMatrix;
	bool result;
	
	// delete the previous message
	delete[] GameManager->MessageForConsole;

	m_RenderTexture->SetRenderTarget(m_DirectXManager->GetDeviceContext(), m_DirectXManager->m_depthStencilView);
	m_RenderTexture->ClearRenderTarget(m_DirectXManager->GetDeviceContext(), m_DirectXManager->m_depthStencilView, 0.0f, 0.0f, 0.0f, 1.0f);
	

	// Horizontal Camera Rotation Around World Origin
	//if (mouseInput[MOUSE_SCROLL_CLICK]) {
	//	if (mouseInput[MOUSE_POS_X] != m_pastMouseX)
	//	{
	//		float angle = -(mouseInput[MOUSE_POS_X] - m_pastMouseX) * 0.01f;
	//		float x = m_Camera->m_positionX;
	//		float z = m_Camera->m_positionZ;

	//		//move cam
	//		m_Camera->m_positionX = x * cos(angle) - z * sin(angle);
	//		m_Camera->m_positionZ = z * cos(angle) + x * sin(angle);

	//		//rotate cam
	//		m_Camera->m_rotationY -= angle * 180 / XM_PI;
	//	}
	//}


	m_DirectXManager->TurnZBufferOn();

	// Generate the view matrix based on the camera's position.
	GameManager->m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_DirectXManager->GetWorldMatrix(worldMatrix);
	GameManager->m_Camera->GetViewMatrix(viewMatrix);
	m_DirectXManager->GetProjectionMatrix(projectionMatrix);
	GameManager->m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_DirectXManager->GetOrthoMatrix(orthoMatrix);

	// static for sprites
	staticWorldMatrix = worldMatrix;


	vector<GameObject*>& gameObjects = GameManager->GetGameObjects();

	// RENDER MODELS
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (!gameObjects[i]->Render(
			m_DirectXManager->GetDeviceContext(),
			worldMatrix,
			viewMatrix,
			projectionMatrix,
			GameManager->m_Camera,
			GameManager->m_Light)) 
		{
			GameManager->MessageForConsole = "[error] Error loading PBR model shader - " + *gameObjects[i]->m_Name;
		}
		//else if (m_Models[i]->m_colorShader) {
		//	result = m_ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_Models[i]->GetIndexCount(), m_Models[i]->GetInstanceCount(),
		//		worldMatrix, viewMatrix, projectionMatrix, 1, m_Light->GetDirection(), m_Light->GetDiffuseColor(),
		//		m_Models[i]->m_translation, m_Models[i]->m_rotation, m_Models[i]->m_scale, m_Camera->GetPosition(), 10,
		//		1, m_Models[i]->m_colorShader->color);
		//	if (!result)
		//	{
		//		MessageForConsole = "[error] Error loading color model shader - " + *m_Models[i]->Name;
		//		return false;
		//	}
		//}
		//else {
		//	GameManager->MessageForConsole = "[error] Error object has no shader - " + *gameObjects[i]->Name;
		//	return false;
		//}
	}
	


	m_DirectXManager->TurnZBufferOff();

	// RENDER XYZ ARROWS
	//m_Arrows->Render(Direct3D->GetDeviceContext());
	//result = m_ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), 18, worldMatrix, viewMatrix, projectionMatrix);
	//if (!result)
	//{
	//	MessageForConsole = "[error] Error Loading Arrows.";
	//	return false;
	//}

	m_DirectXManager->SetBackBufferRenderTarget();



	//m_pastMouseX = mouseInput[MOUSE_POS_X];
	//m_pastMouseY = mouseInput[MOUSE_POS_Y];

	return true;
}

ID3D11ShaderResourceView* SceneRenderClass::GetTexture()
{
	return m_RenderTexture->GetShaderResourceView();
}