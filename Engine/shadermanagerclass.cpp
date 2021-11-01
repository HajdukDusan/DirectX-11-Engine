
#include "shadermanagerclass.h"


ShaderManagerClass::ShaderManagerClass()
{
	m_ColorShader = 0;
	m_FontShader = 0;
	m_LightShader = 0;
	m_TextureShader = 0;
}


ShaderManagerClass::ShaderManagerClass(const ShaderManagerClass& other)
{
}


ShaderManagerClass::~ShaderManagerClass()
{
}


bool ShaderManagerClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;


	// Create the color shader object.
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the font shader object.
	m_FontShader = new FontShaderClass;
	if (!m_FontShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_FontShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}


	// Create the light shader object
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object
	result = m_LightShader->Initialize(device, hwnd);
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
	result = m_TextureShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}


	// Create the normal map shader object.
	m_PBRShader = new PBRShaderClass;
	if (!m_PBRShader)
	{
		return false;
	}

	// Initialize the normal map shader object.
	result = m_PBRShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the normal map shader object.", L"Error", MB_OK);
		return false;
	}


	return true;
}


void ShaderManagerClass::Shutdown()
{
	if (m_PBRShader)
	{
		m_PBRShader->Shutdown();
		delete m_PBRShader;
		m_PBRShader = 0;
	}
	if (m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	return;
}


bool ShaderManagerClass::RenderColorShader(ID3D11DeviceContext* deviceContext, int indexCount, int instanceCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, float normalStrength, XMFLOAT3 lightDirection,
	XMFLOAT4 diffuseColor, XMMATRIX translate, XMMATRIX rotate, XMMATRIX scale, XMFLOAT3 camPos, float specularColor, float specularPower,
	XMFLOAT4 color)
{
	return m_ColorShader->Render(deviceContext, indexCount, instanceCount, worldMatrix, viewMatrix, projectionMatrix, normalStrength, lightDirection, diffuseColor,
		translate, rotate, scale, camPos, XMFLOAT4(specularColor, specularColor, specularColor, 1), specularPower, color);
}


bool ShaderManagerClass::RenderFontShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, XMFLOAT4 color)
{
	return m_FontShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, color);
}


bool ShaderManagerClass::RenderLightShader(ID3D11Device* device, ID3D11DeviceContext* deviceContext,
	int indexCount, int instanceCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture,
	XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor, XMFLOAT4 ambientColor,
	XMFLOAT3 cameraPosition, XMFLOAT4 specularColor, float specularPower)
{
	return m_LightShader->Render(device, deviceContext, indexCount, instanceCount,
		worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, diffuseColor, ambientColor,
		cameraPosition, specularColor, specularPower);
}


bool ShaderManagerClass::RenderTextureShader(ID3D11DeviceContext* deviceContext,
	int indexCount, int instanceCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture)
{
	return m_TextureShader->Render(deviceContext, indexCount, instanceCount, worldMatrix, viewMatrix, projectionMatrix, texture);
}

bool ShaderManagerClass::RenderShaderBasedOnMaterial(
	ID3D11DeviceContext* deviceContext,
	XMMATRIX worldMatrix,
	XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix,
	CameraClass* camera,
	ModelClass* model,
	Material* material,
	LightClass* lightr)
{
	if (m_PBRShader->Render(deviceContext, worldMatrix, viewMatrix, projectionMatrix, camera, model, material, lightr))
		return true;

	return false;
}