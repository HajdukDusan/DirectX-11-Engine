#include "zoneclass.h"


ZoneClass::ZoneClass()
{
	m_UserInterface = 0;
	m_Camera = 0;
	m_Position = 0;
	m_Terrain = 0;
	m_Arrows = 0;
	m_PreviousMouseX = 0;
	m_PreviousMouseY = 0;

	m_NormalMapShader = 0;



	m_NormalStrength = 1;
}


ZoneClass::ZoneClass(const ZoneClass& other)
{
}


ZoneClass::~ZoneClass()
{
}


bool ZoneClass::Initialize(D3DClass* Direct3D, HWND hwnd, int screenWidth, int screenHeight, float screenDepth)
{
	bool result;


	m_GUI = new GuiClass(hwnd, Direct3D);

	// Create the user interface object.
	m_UserInterface = new UserInterfaceClass;
	if (!m_UserInterface)
	{
		return false;
	}

	// Initialize the user interface object.
	result = m_UserInterface->Initialize(Direct3D, screenHeight, screenWidth);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the user interface object.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera and build the matrices needed for rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();
	m_Camera->RenderBaseViewMatrix();

	// Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation.
	m_Position->SetPosition(-8.0f, 7.0f, -8.0f);
	m_Position->SetRotation(20.0f, 45.0f, 0.0f);



	// CREATE THE GRID
	m_Terrain = new TerrainClass;
	if (!m_Terrain)
	{
		return false;
	}
	// Initialize the terrain object.
	result = m_Terrain->Initialize(Direct3D->GetDevice(), 10, XMFLOAT4(0.5f, 0.5f, 0.5f, 0.0f));
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}


	// CREATE THE ARROWS OBJECT
	m_Arrows = new ArrowsClass;
	if (!m_Arrows)
	{
		return false;
	}

	result = m_Arrows->Initialize(Direct3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the xyz arrows object.", L"Error", MB_OK);
		return false;
	}
	m_Circle = new BitmapClass;
	if (!m_Circle)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Circle->Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), 200, 200, "../Engine/data/circle.tga", 20, 20);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}


	// Create the Sun :)

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f); //15% of diffuse light
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);	//white
	m_Light->SetDirection(0.2f, -0.2f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);



	//INITIALIZE THE MODELS
	// Create the model objects.
	m_Model = new ModelClass;

	// Initialize the model object.
	vector<XMFLOAT3> instancePos;
	//instancePos.push_back(XMFLOAT3(0.f, 0.f, 0.f));
	//instancePos.push_back(XMFLOAT3(0.f, 2.f, 4.f));

	ModelClass::Transform *tmp = new ModelClass::Transform();

	//result = m_Model->Initialize("Barrel", Direct3D->GetDevice(), Direct3D->GetDeviceContext(), false, "../Engine/data/drum1_base_color.tga",
	//							"../Engine/data/drum1_normal.tga", "../Engine/data/drum1_specular.tga", "../Engine/data/barrel.txt", tmp);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}




	// LOAD MOUSE CURSOR
	// Create the bitmap object.
	m_MousePointer = new BitmapClass;
	if (!m_MousePointer)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_MousePointer->Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, "../Engine/data/mouse.tga", 15, 26);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}





	// RENDER TO TEXTURE

	m_RenderTexture = new RenderTextureClass;
	if (!m_RenderTexture)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_RenderTexture->Initialize(Direct3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		return false;
	}



	// Set the UI to display by default.
	m_displayUI = true;

	return true;
}


void ZoneClass::Shutdown()
{
	if (m_RenderTexture)
	{
		m_RenderTexture->Shutdown();
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}
	if (m_MousePointer)
	{
		m_MousePointer->Shutdown();
		delete m_MousePointer;
		m_MousePointer = 0;
	}
	if (m_NormalMapShader)
	{
		m_NormalMapShader->Shutdown();
		delete m_NormalMapShader;
		m_NormalMapShader = 0;
	}
	if (m_Circle)
	{
		m_Circle->Shutdown();
		delete m_Circle;
		m_Circle = 0;
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

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the user interface object.
	if (m_UserInterface)
	{
		m_UserInterface->Shutdown();
		delete m_UserInterface;
		m_UserInterface = 0;
	}

	return;
}


bool ZoneClass::Frame(D3DClass* Direct3D, InputClass* Input, ShaderManagerClass* ShaderManager, float frameTime, int fps)
{
	bool result;
	float posX, posY, posZ, rotX, rotY, rotZ;
	int mouseX, mouseY;

	// Do the frame input processing.
	HandleMovementInput(Input, frameTime);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// get mouse movement
	Input->GetMouseLocation(mouseX, mouseY);

	// Do the frame processing for the user interface.
	result = m_UserInterface->Frame(Direct3D->GetDeviceContext(), fps, posX, posY, posZ, rotX, rotY, rotZ);
	if (!result)
	{
		return false;
	}

	// Render the graphics.
	result = Render(Direct3D, ShaderManager, mouseX, mouseY, frameTime);
	if (!result)
	{
		return false;
	}

	return true;
}


void ZoneClass::HandleMovementInput(InputClass* Input, float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;


	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = Input->IsLeftArrowPressed();
	m_Position->TurnLeft(keyDown);
	keyDown = Input->IsRightArrowPressed();
	m_Position->TurnRight(keyDown);
	keyDown = Input->IsUpArrowPressed();
	m_Position->TurnUp(keyDown);
	keyDown = Input->IsDownArrowPressed();
	m_Position->TurnDown(keyDown);


	keyDown = Input->IsWPressed();
	m_Position->GoForeward(keyDown);
	keyDown = Input->IsSPressed();
	m_Position->GoBackward(keyDown);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	// Determine if the user interface should be displayed or not.
	if (Input->IsF1Toggled())
	{
		m_displayUI = !m_displayUI;
	}

	return;
}

float i = 0;

bool ZoneClass::Render(D3DClass* Direct3D, ShaderManagerClass* ShaderManager, int mouseX, int mouseY, float frameTime)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMatrix, staticWorldMatrix;
	bool result;


	Direct3D->TurnZBufferOn();

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	Direct3D->GetOrthoMatrix(orthoMatrix);


	// Clear the buffers to begin the scene.
	Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	m_RenderTexture->SetRenderTarget(Direct3D->GetDeviceContext(), Direct3D->m_depthStencilView);


	staticWorldMatrix = worldMatrix;


	
	// MOUSE POINTER NE POKAZUJE DOBRO
	// KORISTITI SISTEMSKI
	//m_GUI->LogInfoMessage(string(std::to_string(mouseX) + " - " + std::to_string(m_PreviousMouseX)).c_str());
	//if (mouseX != m_PreviousMouseX)
	//{
	//	i += (mouseX - m_PreviousMouseX) * 0.01f;
	//	worldMatrix = XMMatrixRotationY(i);
	//}
	//else
	//	i = 0;
	




	// RENDER GRID
	//m_Terrain->Render(Direct3D->GetDeviceContext());
	//result = ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	//if (!result)
	//{
	//	return false;
	//}

	// update model position
	//XMFLOAT3 pos = m_Model->GetInstanceTransform(0);
	//pos.z += 0.001f;
	//m_Model->SetInstanceTransform(0, pos);
	



	// RENDER MODEL
	//m_Model->Render(Direct3D->GetDeviceContext());
	//result = ShaderManager->RenderPBRShader(Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), m_Model->GetInstanceCount(),
	//	worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTextureArray(), m_Model->m_pbrShader->normalStrength, m_Light->GetDirection(), m_Light->GetDiffuseColor(),
	//	m_Model->m_translation, m_Model->m_rotation, m_Model->m_scale);
	//if (!result)
	//{
	//	return false;
	//}



	//START 2D
	Direct3D->TurnZBufferOff();
	Direct3D->TurnOnAlphaBlending();

	// RENDER XYZ ARROWS
	//m_Arrows->Render(Direct3D->GetDeviceContext());
	//result = ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), 18, worldMatrix, viewMatrix, projectionMatrix);
	//if (!result)
	//{
	//	return false;
	//}



	// Render the user interface.
	//if (m_displayUI)
	//{
	//	result = m_UserInterface->Render(Direct3D, ShaderManager, staticWorldMatrix, baseViewMatrix, orthoMatrix);
	//	if (!result)
	//	{
	//		return false;
	//	}
	//}



	// RENDER MOUSE CURSOR
	//result = m_MousePointer->Render(Direct3D->GetDeviceContext(), mouseX, mouseY);  if (!result) { return false; }
	//// Render with font shader and make black pixels transparent
	//result = ShaderManager->RenderFontShader(Direct3D->GetDeviceContext(), m_MousePointer->GetIndexCount(), staticWorldMatrix, baseViewMatrix, orthoMatrix, m_MousePointer->GetTexture(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	//if (!result)
	//{
	//	return false;
	//}


	


	// render the circle
	//result = m_Circle->Render(Direct3D->GetDeviceContext(), tmp.x, tmp.y);  if (!result) { return false; }
	//result = ShaderManager->RenderFontShader(Direct3D->GetDeviceContext(), m_Circle->GetIndexCount(), staticWorldMatrix, baseViewMatrix, orthoMatrix, m_Circle->GetTexture(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	//if (!result)
	//{
	//	return false;
	//}

	Direct3D->TurnOffAlphaBlending();


	

	// IM GUI

	//m_GUI->Finish();




	// Present the rendered scene to the screen.
	Direct3D->PresentScene();

	//m_GUI->Render(m_RenderTexture->GetShaderResourceView(), m_Model, m_Light);

	//update location
	m_PreviousMouseX = mouseX;
	m_PreviousMouseY = mouseY;

	return true;
}


void ZoneClass::RenderImGui() {

	//m_GUI->Render(m_Model, m_Light);

}