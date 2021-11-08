#include "scenerenderclass.h"
#include "../../Scene/Entity/Components/MeshComponent.h"

SceneRenderClass::SceneRenderClass(D3DClass* Direct3D, HWND hwnd) {

	m_DirectXManager = Direct3D;

	// Create the position object.

	// Set the initial position and rotation.
	//m_Position->SetPosition(-8.0f, 7.0f, -8.0f);
	//m_Position->SetRotation(20.0f, 45.0f, 0.0f);

	// CREATE THE GRID
	//m_Terrain = new TerrainClass;
	//// Initialize the terrain object.
	//if(!m_Terrain->Initialize(Direct3D->GetDevice(), 10, XMFLOAT4(0.5f, 0.5f, 0.5f, 0.0f)))
	//{
	//	MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
	//	exit(-1);
	//}


	//// CREATE THE ARROWS OBJECT
	//m_Arrows = new ArrowsClass;

	//if(!m_Arrows->Initialize(Direct3D->GetDevice()))
	//{
	//	MessageBox(hwnd, L"Could not initialize the xyz arrows object.", L"Error", MB_OK);
	//	exit(-1);
	//}





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
}


bool SceneRenderClass::RenderScene(GameManager* GameManager) {

	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMatrix, staticWorldMatrix;
	bool result;
	
	// start the timer for calculating the prepare scene time
	GameManager->m_Timer->Start();

	// delete the previous message
	//if (GameManager->MessageForConsole)
	//	delete[] GameManager->MessageForConsole;

	m_RenderTexture->SetRenderTarget(m_DirectXManager->GetDeviceContext(), m_DirectXManager->m_depthStencilView);
	m_RenderTexture->ClearRenderTarget(m_DirectXManager->GetDeviceContext(), m_DirectXManager->m_depthStencilView, 0.0f, 0.0f, 0.0f, 1.0f);


	m_DirectXManager->TurnZBufferOn();

	// Generate the view matrix based on the camera's position.

	// FIXXXXXXXXXXXXXXXXXXXXXXXXXX
	GameManager->m_Camera->Render(GameManager->GetEntities()[0]->m_Transform);

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_DirectXManager->GetWorldMatrix(worldMatrix);
	GameManager->m_Camera->GetViewMatrix(viewMatrix);
	m_DirectXManager->GetProjectionMatrix(projectionMatrix);
	GameManager->m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_DirectXManager->GetOrthoMatrix(orthoMatrix);

	// static for sprites
	staticWorldMatrix = worldMatrix;


	vector<Entity*>& entities = GameManager->GetEntities();

	// RENDER MODELS
	for (int i = 0; i < entities.size(); i++)
	{
		for (Component* comp : entities[i]->m_Components) {
			if (MeshComponent* meshComp = dynamic_cast<MeshComponent*>(comp); meshComp)
			{
				if (!meshComp->Render(
					m_DirectXManager->GetDeviceContext(),
					worldMatrix,
					viewMatrix,
					projectionMatrix,
					entities[i]->m_Transform,
					GameManager->GetEntities()[0]->m_Transform,
					GameManager->m_Light))
				{
					GameManager->MessageForConsole = "[error] Error while rendering " + *entities[i]->m_Name;
				}
			}
		}
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


	// stop the timer
	GameManager->m_PrepareSceneTime = GameManager->m_Timer->End();

	// present the rendered scene, and record the time it took
	GameManager->m_Timer->Start();
	m_DirectXManager->PresentScene();
	GameManager->m_PresentSceneTime = GameManager->m_Timer->End();

	return true;
}

ID3D11ShaderResourceView* SceneRenderClass::GetTexture()
{
	return m_RenderTexture->GetShaderResourceView();
}