#include "scenerenderclass.h"

SceneRenderClass::SceneRenderClass(D3DClass* Direct3D, HWND hwnd) {


//	m_SceneLoader = new SceneLoader(Direct3D, "../Engine/data/MyScene.scene", m_Models, m_PbrMaterials, m_ColorMaterials);



	m_DirectX = Direct3D;

	// Create the camera object.
	m_Camera = new CameraClass;
	// Set the initial position of the camera and build the matrices needed for rendering.
	m_Camera->SetPosition(-8.0f, 7.0f, -8.0f);
	m_Camera->SetRotation(20.0f, 45.0f, 0.0f);
	//m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	//m_Camera->SetRotation(0.0f, 0.0f, 0.0f);
	m_Camera->Render();
	m_Camera->RenderBaseViewMatrix();


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


	// CREATE THE GLOBAL LIGHT
	m_Light = new LightClass;
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f); //15% of diffuse light
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);	//white
	m_Light->SetDirection(0.430f, -0.8f, 0.710f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);


	// CREATE THE SHADER MANAGER OBJECT
	m_ShaderManager = new ShaderManagerClass;
	// Initialize the shader manager object.
	if(!m_ShaderManager->Initialize(Direct3D->GetDevice(), hwnd))
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		exit(-1);
	}


	//INITIALIZE THE MODELS
	// Create the model objects.

	//BARREL
	m_Models.push_back(new ModelClass);
	m_PbrMaterials.push_back(new PBRShaderMaterial(Direct3D->GetDevice(), Direct3D->GetDeviceContext(),
		"BarrelMaterial",
		"../Engine/data/drum1_base_color.tga",
		"../Engine/data/drum1_normal.tga",
		"../Engine/data/drum1_specular.tga",
		2, 10, 2));
	m_Models[0]->SetPbrShader(m_PbrMaterials[0]);

	if (!m_Models[0]->Initialize("Barrel", Direct3D->GetDevice(), Direct3D->GetDeviceContext(), false, "../Engine/data/barrel.txt",
		new ModelClass::Transform(XMFLOAT3(-3.210, 0, 4.130), XMFLOAT3(0, 3.620, 0), XMFLOAT3(0.5, 0.5, 0.5))))
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
	};

	//GASS TANK
	m_Models.push_back(new ModelClass);
	m_PbrMaterials.push_back(new PBRShaderMaterial(Direct3D->GetDevice(), Direct3D->GetDeviceContext(),
		"GassTankMaterial",
		"../Engine/data/Gass Tank/gasTank_color.tga",
		"../Engine/data/Gass Tank/gasTank_normal.tga",
		"../Engine/data/Gass Tank/gasTank_specular.tga"));
	m_Models[1]->SetPbrShader(m_PbrMaterials[1]);

	if (!m_Models[1]->Initialize("Gass Tank", Direct3D->GetDevice(), Direct3D->GetDeviceContext(), false, "../Engine/data/Gass Tank/gass_tank.txt", 
		new ModelClass::Transform(XMFLOAT3(0, 2, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(2, 2, 2))))
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
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

	m_Models.push_back(new ModelClass);

	string stmp("../Engine/data/SimpleObjects/");
	stmp += filename;

	int newSize = strlen(filename) - 4;
	char* name = new char[newSize];
	strncpy_s(name, sizeof(name), filename, newSize);
	
	m_ColorMaterials.push_back(new ColorShaderMaterial(m_DirectX->GetDevice(), m_DirectX->GetDeviceContext(), stmp.c_str(), XMFLOAT4(1, 1, 1, 1)));
	m_Models[m_Models.size() - 1]->SetColorShader(m_ColorMaterials[m_ColorMaterials.size() - 1]);

	if (!m_Models[m_Models.size() - 1]->Initialize(name, m_DirectX->GetDevice(), m_DirectX->GetDeviceContext(), false, stmp.c_str(), new ModelClass::Transform()))
	{
		return false;
	}

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

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}
	if (m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}
	
	// delete the materials
	for (PBRShaderMaterial* m : m_PbrMaterials) {
		delete m;
	}
	m_PbrMaterials.clear();

	for (ColorShaderMaterial* m : m_ColorMaterials) {
		delete m;
	}
	m_ColorMaterials.clear();

	// delete the models
	for (ModelClass* m : m_Models) {
		delete m;
	}
	m_Models.clear();
}


bool SceneRenderClass::RenderScene(D3DClass* Direct3D, int* mouseInput) {


	MessageForConsole = "";

	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMatrix, staticWorldMatrix;
	bool result;

	m_RenderTexture->SetRenderTarget(Direct3D->GetDeviceContext(), Direct3D->m_depthStencilView);
	m_RenderTexture->ClearRenderTarget(Direct3D->GetDeviceContext(), Direct3D->m_depthStencilView, 0.0f, 0.0f, 0.0f, 1.0f);
	

	if (mouseInput[MOUSE_SCROLL_CLICK]) {


		//// vertical movement
		//if (mouseInput[MOUSE_POS_Y] != m_pastMouseY || mouseInput[MOUSE_POS_X] != m_pastMouseX)
		//{

		//	float angle = -m_Camera->m_rotationY * XM_PI / 180;
		//	float x_tmp = m_Camera->m_positionX;
		//	float z_tmp = m_Camera->m_positionZ;
		//	//move cam
		//	m_Camera->m_positionX = x_tmp * cos(angle) - z_tmp *sin(angle);
		//	m_Camera->m_positionZ = z_tmp * cos(angle) + x_tmp * sin(angle);
		//	

		//	//m_Camera->m_rotationY = ;

		//	//float angleX = (mouseInput[MOUSE_POS_Y] - m_pastMouseY) * 0.005f;

		//	//float x = m_Camera->m_positionX;
		//	//float y = m_Camera->m_positionY;

		//	//m_Camera->m_positionX = x * cos(angleX) - y * sin(angleX);
		//	//m_Camera->m_positionY = y * cos(angleX) + x * sin(angleX);

		//	//m_Camera->m_rotationX -= angleX * 180 / XM_PI;


		//	float x = (mouseInput[MOUSE_POS_Y] - m_pastMouseY) * 0.005f;
		//	float y = 0;
		//	float z = 0;

		//	// load translation matrix
		//	XMMATRIX translation = XMMATRIX(
		//		1.0f, 0.0f, 0.0f, 0.0f,
		//		0.0f, 1.0f, 0.0f, 0.0f,
		//		0.0f, 0.0f, 1.0f, 0.0f,
		//		0.0f, 0.0f, 0.0f, 1.0f
		//	);

		//	XMMATRIX rotation = XMMATRIX(
		//		cos(y) * cos(z), cos(y) * sin(z), -sin(y), 0.0f,
		//		sin(x) * sin(y) * cos(z) - cos(x) * sin(z), sin(x) * sin(y) * sin(z) + cos(x) * cos(z), sin(x) * cos(y), 0.0f,
		//		cos(x) * sin(y) * cos(z) + sin(x) * sin(z), cos(x) * sin(y) * sin(z) - sin(x) * cos(z), cos(x) * cos(y), 0.0f,
		//		0.0f, 0.0f, 0.0f, 1.0f
		//	);

		//	XMFLOAT4 f(0, m_Camera->m_positionY, m_Camera->m_positionZ, 1.0f);


		//	rotation = XMMatrixMultiply(rotation, translation);

		//	XMVECTOR pos = XMVector3Transform(XMLoadFloat4(&f), rotation);

		//	XMStoreFloat4(&f, pos);

		//	//m_Camera->m_positionX = f.x;
		//	m_Camera->m_positionY = f.y;
		//	m_Camera->m_positionZ = f.z;



		//	////m_Camera->m_rotationY += (mouseInput[MOUSE_POS_X] - m_pastMouseX) * 0.01f * 180 / XM_PI;

		//	angle = -angle;

		//	x_tmp = m_Camera->m_positionX;
		//	z_tmp = m_Camera->m_positionZ;

		//	m_Camera->m_positionX = x_tmp * cos(angle) - z_tmp * sin(angle);
		//	m_Camera->m_positionZ = z_tmp * cos(angle) + x_tmp * sin(angle);

		//	//m_Camera->m_rotationY += angle * 180 / XM_PI;
		//}

		if (mouseInput[MOUSE_POS_X] != m_pastMouseX)
		{
			float angle = -(mouseInput[MOUSE_POS_X] - m_pastMouseX) * 0.01f;
			float x = m_Camera->m_positionX;
			float z = m_Camera->m_positionZ;

			//move cam
			m_Camera->m_positionX = x * cos(angle) - z * sin(angle);
			m_Camera->m_positionZ = z * cos(angle) + x * sin(angle);

			//rotate cam
			m_Camera->m_rotationY -= angle * 180 / XM_PI;
		}

	}





	Direct3D->TurnZBufferOn();

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	Direct3D->GetOrthoMatrix(orthoMatrix);

	// static for sprites
	staticWorldMatrix = worldMatrix;



	// world angle
	//worldMatrix = XMMatrixRotationY(worldAngle);
	

	// RENDER GRID
	//m_Terrain->Render(Direct3D->GetDeviceContext());
	//result = m_ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	//if (!result)
	//{
	//	MessageForConsole = "[error] Error Loading Grid.";
	//	return false;
	//}


	// RENDER MODELS
	for (int i = 0; i < m_Models.size(); i++)
	{
		m_Models[i]->Render(Direct3D->GetDeviceContext());

		if (m_Models[i]->m_pbrShader) {
			result = m_ShaderManager->RenderPBRShader(Direct3D->GetDeviceContext(), m_Models[i]->GetIndexCount(), m_Models[i]->GetInstanceCount(),
				worldMatrix, viewMatrix, projectionMatrix, m_Models[i]->GetTextureArray(), m_Models[i]->m_pbrShader->normalStrength, m_Light->GetDirection(), m_Light->GetDiffuseColor(),
				m_Models[i]->m_translation, m_Models[i]->m_rotation, m_Models[i]->m_scale, m_Camera->GetPosition(), m_Models[i]->m_pbrShader->specularStrenght,
				m_Models[i]->m_pbrShader->specularFocus);
			if (!result)
			{
				MessageForConsole = "[error] Error loading PBR model shader - " + *m_Models[i]->Name;
				return false;
			}
		}
		else if (m_Models[i]->m_colorShader) {
			result = m_ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_Models[i]->GetIndexCount(), m_Models[i]->GetInstanceCount(),
				worldMatrix, viewMatrix, projectionMatrix, 1, m_Light->GetDirection(), m_Light->GetDiffuseColor(),
				m_Models[i]->m_translation, m_Models[i]->m_rotation, m_Models[i]->m_scale, m_Camera->GetPosition(), 10,
				1, m_Models[i]->m_colorShader->color);
			if (!result)
			{
				MessageForConsole = "[error] Error loading color model shader - " + *m_Models[i]->Name;
				return false;
			}
		}
		else {
			MessageForConsole = "[error] Error object has no shader - " + *m_Models[i]->Name;
			return false;
		}
	}
	


	Direct3D->TurnZBufferOff();

	// RENDER XYZ ARROWS
	//m_Arrows->Render(Direct3D->GetDeviceContext());
	//result = m_ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), 18, worldMatrix, viewMatrix, projectionMatrix);
	//if (!result)
	//{
	//	MessageForConsole = "[error] Error Loading Arrows.";
	//	return false;
	//}

	Direct3D->SetBackBufferRenderTarget();



	m_pastMouseX = mouseInput[MOUSE_POS_X];
	m_pastMouseY = mouseInput[MOUSE_POS_Y];

	return true;
}

ID3D11ShaderResourceView* SceneRenderClass::GetTexture()
{
	return m_RenderTexture->GetShaderResourceView();
}