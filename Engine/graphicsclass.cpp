#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_Direct3D = 0;
	m_Camera = 0;
	m_Model = 0;

	m_LightShader = 0;
	m_TextureShader = 0;
	m_Light = 0;

	m_Sprite = 0;

	m_ModelList = 0;
	m_Frustum = 0;

	m_ClipPlaneShader = 0;

	m_Bitmap = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, 0.0f);
	//m_Camera->SetRotation(90.0f, 0.0f, 0.0f);



	
	// INITIALIZE THE SHADERS

	// Create the light shader object
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}
	
	// Initialize the light shader object
	result = m_LightShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}
	
	// Create the texture shader object and light shader object?
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the color shader object and light shader object?
	result = m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the clip plane shader object.
	m_ClipPlaneShader = new ClipPlaneShaderClass;
	if (!m_ClipPlaneShader)
	{
		return false;
	}

	// Initialize the clip plane shader object.
	result = m_ClipPlaneShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the clip plane shader object.", L"Error", MB_OK);
		return false;
	}




	// LOAD MOUSE CURSOR
	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, "../Engine/data/mouse.png", 32, 32);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize that the user has not clicked on the screen to try an intersection test yet.
	m_beginCheck = false;






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
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);






	//INITIALIZE THE MODELS

	// Create the model objects.
	m_Model = new ModelClass;

	// Initialize the model object.
	vector<XMFLOAT3> instancePos;
	instancePos.push_back(XMFLOAT3(0.f, 0.f, 4.f));
	//instancePos.push_back(XMFLOAT3(0.f, 2.f, 4.f));
	//result = m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), false, "../Engine/data/img.jpg", "../Engine/data/cube.txt", instancePos);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
	//	return false;
	//}


	// Create the model list object.
	m_ModelList = new ModelListClass;
	if (!m_ModelList)
	{
		return false;
	}

	// Initialize the model list object.
	result = m_ModelList->Initialize(50);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model list object.", L"Error", MB_OK);
		return false;
	}


	// Create the frustum object.
	m_Frustum = new FrustumClass;
	if (!m_Frustum)
	{
		return false;
	}



	// CREATE THE TERRAIN OBJECT
	m_Terrain = new TerrainClass;
	if (!m_Terrain)
	{
		return false;
	}
	result = m_Terrain->Initialize(m_Direct3D->GetDevice(), 10, XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f));
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

	// Initialize the terrain object.
	result = m_Arrows->Initialize(m_Direct3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the arrows object.", L"Error", MB_OK);
		return false;
	}




	// COLOR SHADER
	// Create the color shader object.
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}


	
	// SPRITE OBJECT
	// Create the sprite object.
	//m_Sprite = new SpriteClass;
	//if (!m_Sprite)
	//{
	//	return false;
	//}

	//// Initialize the sprite object.
	//result = m_Sprite->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, L"../Engine/data/img.jpg", 256, 256);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the sprite object.", L"Error", MB_OK);
	//	return false;
	//}





	////Font stuff
	//spriteBatch = make_unique<SpriteBatch>(m_Direct3D->GetDeviceContext());
	//spriteFont = make_unique<SpriteFont>(m_Direct3D->GetDevice(), L"myfile.spritefont");

	//m_fontPos.x = 0.f;//screenWidth / 2.f;
	//m_fontPos.y = 0.f;//screenHeight / 2.f;




	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	//result = m_Text->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Retrieve the video card information.
	//m_Direct3D->GetVideoCardInfo(videoCard, videoMemory);

	//// Set the video card information in the text object.
	//result = m_Text->SetVideoCardInfo(videoCard, videoMemory, m_Direct3D->GetDeviceContext());
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not set video card info in the text object.", L"Error", MB_OK);
	//	return false;
	//}


	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the clip plane shader object.
	if (m_ClipPlaneShader)
	{
		m_ClipPlaneShader->Shutdown();
		delete m_ClipPlaneShader;
		m_ClipPlaneShader = 0;
	}

	// Release the frustum object.
	if (m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
	}

	// Release the model list object.
	if (m_ModelList)
	{
		m_ModelList->Shutdown();
		delete m_ModelList;
		m_ModelList = 0;
	}
	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}
	// Release the sprite object.
	if (m_Sprite)
	{
		m_Sprite->Shutdown();
		delete m_Sprite;
		m_Sprite = 0;
	}
	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
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

	// Release the color shader object.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// Release the D3D object.
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	return;
}


bool GraphicsClass::Frame(bool testIntersection, int mouseX, int mouseY, float rotationX, float rotationY, float posX, float posY, float posZ)
{


	bool result;


	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);

	// Set the rotation of the camera.
	m_Camera->SetRotation(rotationX, rotationY, 0.0f);


	if (testIntersection) {
		TestIntersection(mouseX, mouseY);
	}



	return true;
}

CameraClass* GraphicsClass::GetCamera()
{
	return m_Camera;
}


bool GraphicsClass::Render(int fps, int cpu, float frameTime, int mouseX,int mouseY, HWND hwnd)
{
	XMFLOAT4 clipPlane;
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	int modelCount, renderCount, index;
	float positionX, positionY, positionZ, radius;
	XMFLOAT4 color;
	bool renderModel, result;


	// Setup a clipping plane.
	//clipPlane = XMFLOAT4(0.0f, -1.0f, 0.0f, 0.0f);

	m_Direct3D->TurnZBufferOn();


	// Clear the buffers to begin the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);
	

	// Construct the frustum.
	m_Frustum->ConstructFrustum(SCREEN_DEPTH, projectionMatrix, viewMatrix);

	// Get the number of models that will be rendered.
	modelCount = m_ModelList->GetModelCount();

	// Initialize the count of models that have been rendered.
	renderCount = 0;




	//FRUSTUM RENDER
	// Go through all the models and render them only if they can be seen by the camera view.
	//for (index = 0; index < modelCount; index++)
	//{
	//	// Get the position and color of the sphere model at this index.
	//	m_ModelList->GetData(index, positionX, positionY, positionZ, color);

	//	// Set the radius of the sphere to 1.0 since this is already known.
	//	radius = 1.0f;

	//	// Check if the sphere model is in the view frustum.
	//	renderModel = m_Frustum->CheckCube(positionX, positionY, positionZ, radius);

	//	// If it can be seen then render it, if not skip this model and check the next sphere.
	//	if (renderModel)
	//	{
	//		// Move the model to the location it should be rendered at.
	//		worldMatrix = XMMatrixTranslation(positionX, positionY, positionZ);

	//		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//		m_Model->Render(m_Direct3D->GetDeviceContext());


	//		// Render the model using the light shader.
	//		m_LightShader->Render(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(),1, worldMatrix, viewMatrix, projectionMatrix,
	//			m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor(),
	//			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	//		// Reset to the original world matrix.
	//		m_Direct3D->GetWorldMatrix(worldMatrix);

	//		// Since this model was rendered then increase the count for this frame.
	//		renderCount++;
	//	}
	//}


	// Render the model with the clip plane shader.
	//result = m_ClipPlaneShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix,
	//	projectionMatrix, m_Model->GetTexture(), clipPlane);





	// 3D STUFF

	// RENDER GIZMOS
	m_Arrows->Render(m_Direct3D->GetDeviceContext());

	// Render the model using the color shader.
	//result = m_ColorShader->Render(m_Direct3D->GetDeviceContext(), 6, worldMatrix, viewMatrix, projectionMatrix);
	//if (!result)
	//{
	//	return false;
	//}

	// GRID
	// Render the terrain buffers.
	m_Terrain->Render(m_Direct3D->GetDeviceContext());

	// Render the model using the color shader.
	//result = m_ColorShader->Render(m_Direct3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	//if (!result)
	//{
	//	return false;
	//}


	// RENDER MODEL
	m_Model->Render(m_Direct3D->GetDeviceContext());
	result = m_LightShader->Render(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), m_Model->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}





	//2D STUFF

	// Turn off the Z buffer to begin all 2D rendering.
	m_Direct3D->TurnZBufferOff();

	m_Direct3D->TurnOnAlphaBlending();

	// Render the mouse cursor with the texture shader.
	result = m_Bitmap->Render(m_Direct3D->GetDeviceContext(), mouseX, mouseY);  if (!result) { return false; }
	//result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), 1, worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Sprite->Render(m_Direct3D->GetDeviceContext(), 0, 400);
	if (!result)
	{
		return false;
	}


	m_Direct3D->TurnOffAlphaBlending();


	//IMAGE
	// Render the bitmap with the texture shader.
	//result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Sprite->GetIndexCount(), 1, worldMatrix, viewMatrix, orthoMatrix, m_Sprite->GetTexture());
	//if (!result)
	//{
	//	return false;
	//}


	//Draw font stuff
	/*spriteBatch->Begin();

	wstring mX = L"Mouse X:" + to_wstring(mouseX);
	wstring mY = L"Mouse Y:" + to_wstring(mouseY);
	wstring fpsString = L"FPS: " + to_wstring(fps);
	wstring cpuString = L"CPU: " + to_wstring(cpu) + L"%";
	wstring renderCnt = L"Render count:" + to_wstring(renderCount);

	wstring wsTmp(m_ClickedInfo.begin(), m_ClickedInfo.end());
	wstring clickedInfo = L"Clicked Obj:" + wsTmp;

	spriteFont->DrawString(spriteBatch.get(), mX.c_str(),
		m_fontPos, Colors::White, 0.f);

	spriteFont->DrawString(spriteBatch.get(), mY.c_str(),
		m_fontPos + SimpleMath::Vector2(0, 30), Colors::White, 0.f);

	spriteFont->DrawString(spriteBatch.get(), fpsString.c_str(),
		m_fontPos + SimpleMath::Vector2(0, 60), Colors::White, 0.f);

	spriteFont->DrawString(spriteBatch.get(), cpuString.c_str(),
		m_fontPos + SimpleMath::Vector2(0, 90), Colors::White, 0.f);

	spriteFont->DrawString(spriteBatch.get(), renderCnt.c_str(),
		m_fontPos + SimpleMath::Vector2(0, 120), Colors::White, 0.f);

	spriteFont->DrawString(spriteBatch.get(), clickedInfo.c_str(),
		m_fontPos + SimpleMath::Vector2(0, 150), Colors::White, 0.f);

	spriteBatch->End();*/

	// Present the rendered scene to the screen.
	m_Direct3D->PresentScene();

	return true;
}





void GraphicsClass::TestIntersection(int mouseX, int mouseY)
{
	float pointX, pointY;
	XMMATRIX projectionMatrix, viewMatrix, inverseViewMatrix, worldMatrix, translateMatrix, inverseWorldMatrix;
	XMVECTOR rayOrigin, rayDirection;
	XMFLOAT3 direction, origin;
	bool intersect, result;


	// Move the mouse cursor coordinates into the -1 to +1 range.
	pointX = ((2.0f * (float)mouseX) / (float)m_screenWidth) - 1.0f;
	pointY = (((2.0f * (float)mouseY) / (float)m_screenHeight) - 1.0f) * -1.0f;

	// Adjust the points using the projection matrix to account for the aspect ratio of the viewport.
	m_Direct3D->GetProjectionMatrix(projectionMatrix);



	// treba optimizovati?
	XMFLOAT4X4  tmp;

	XMStoreFloat4x4(&tmp, projectionMatrix);

	pointX = pointX / tmp._11;
	pointY = pointY / tmp._22;



	// Get the inverse of the view matrix.
	m_Camera->GetViewMatrix(viewMatrix);
	inverseViewMatrix = XMMatrixInverse(NULL, viewMatrix);


	XMStoreFloat4x4(&tmp, projectionMatrix);

	// Calculate the direction of the picking ray in view space.
	direction.x = (pointX * tmp._11) + (pointY * tmp._21) + tmp._31;
	direction.y = (pointX * tmp._12) + (pointY * tmp._22) + tmp._32;
	direction.z = (pointX * tmp._13) + (pointY * tmp._23) + tmp._33;

	// Get the origin of the picking ray which is the position of the camera.
	origin = m_Camera->GetPosition();

	// Get the world matrix and translate to the location of the sphere.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	translateMatrix = XMMatrixTranslation(-5.0f, 1.0f, 5.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Now get the inverse of the translated world matrix.
	inverseWorldMatrix = XMMatrixInverse(NULL, worldMatrix);


	// Now transform the ray origin and the ray direction from view space to world space.
	XMVECTOR vecTmp = XMLoadFloat3(&origin);
	rayOrigin = XMVector3TransformCoord(vecTmp, inverseWorldMatrix);

	vecTmp = XMLoadFloat3(&direction);
	rayDirection = XMVector3TransformNormal(vecTmp, inverseWorldMatrix);


	// Normalize the ray direction.
	rayDirection = XMVector3Normalize(rayDirection);



	// Now perform the ray-sphere intersection test.
	XMFLOAT3 rayOriginV3, rayDirectionV3;

	XMStoreFloat3(&rayOriginV3, rayOrigin);
	XMStoreFloat3(&rayDirectionV3, rayDirection);

	intersect = RaySphereIntersect(rayOriginV3, rayDirectionV3, 1.0f);



	if (intersect == true)
	{
		// If it does intersect then set the intersection to "yes" in the text string that is displayed to the screen.
		m_ClickedInfo = "da";
	}
	else
	{
		// If not then set the intersection to "No".
		m_ClickedInfo = "ne";
	}

	return;
}



bool GraphicsClass::RaySphereIntersect(XMFLOAT3 rayOrigin, XMFLOAT3 rayDirection, float radius)
{
	float a, b, c, discriminant;


	// Calculate the a, b, and c coefficients.
	a = (rayDirection.x * rayDirection.x) + (rayDirection.y * rayDirection.y) + (rayDirection.z * rayDirection.z);
	b = ((rayDirection.x * rayOrigin.x) + (rayDirection.y * rayOrigin.y) + (rayDirection.z * rayOrigin.z)) * 2.0f;
	c = ((rayOrigin.x * rayOrigin.x) + (rayOrigin.y * rayOrigin.y) + (rayOrigin.z * rayOrigin.z)) - (radius * radius);

	// Find the discriminant.
	discriminant = (b * b) - (4 * a * c);

	// if discriminant is negative the picking ray missed the sphere, otherwise it intersected the sphere.
	if (discriminant < 0.0f)
	{
		return false;
	}

	return true;
}