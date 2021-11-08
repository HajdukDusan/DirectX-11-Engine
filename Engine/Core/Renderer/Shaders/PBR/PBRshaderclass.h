#ifndef _PBRSHADERCLASS_H_
#define _PBRSHADERCLASS_H_


#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h> //<d3dx11async.h>
#include <fstream>
#include "../Shader.h"

using namespace std;
using namespace DirectX;

class PBRShaderClass : public Shader
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct LightBufferType
	{
		XMFLOAT4 diffuseColor;
		XMFLOAT3 lightDirection;
		float NormalMapEffect;
		XMFLOAT4 specularColor;
		float specularPower;

		XMFLOAT3 padding;
	};

	struct CameraBufferType
	{
		XMFLOAT3 cameraPosition;
		float padding;
	};

	struct TransformBufferType
	{
		XMMATRIX transform;
	};

public:
	PBRShaderClass();
	PBRShaderClass(const PBRShaderClass&);
	~PBRShaderClass() override;

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	bool Render(ID3D11DeviceContext* deviceContext,
		XMMATRIX worldMatrix,
		XMMATRIX viewMatrix,
		XMMATRIX projectionMatrix,
		Transform* transform,
		Mesh* model,
		Material* material,
		LightClass* light)
		override;

private:
	bool InitializeShader(ID3D11Device*, HWND, const WCHAR*, const WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, const WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView**, float,
		XMFLOAT3, XMFLOAT4, XMMATRIX, XMMATRIX, XMMATRIX,
		XMFLOAT3, XMFLOAT4, float);
	void RenderShader(ID3D11DeviceContext*, int, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer, * m_lightBuffer, * m_transformBuffer, * m_cameraBuffer;

	ID3D11SamplerState* m_sampleState;
};

#endif