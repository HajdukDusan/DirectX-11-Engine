#ifndef _COLORSHADERCLASS_H_
#define _COLORSHADERCLASS_H_

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <fstream>
using namespace DirectX;
using namespace std;

class ColorShaderClass
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

	struct ColorBufferType
	{
		XMFLOAT4 color;
	};

public:
	ColorShaderClass();
	ColorShaderClass(const ColorShaderClass&);
	~ColorShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, int, XMMATRIX, XMMATRIX, XMMATRIX, float, XMFLOAT3,
		XMFLOAT4, XMMATRIX, XMMATRIX, XMMATRIX, XMFLOAT3, XMFLOAT4, float, XMFLOAT4);

private:
	bool InitializeShader(ID3D11Device*, HWND, const WCHAR*, const WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, const WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, float,
		XMFLOAT3, XMFLOAT4, XMMATRIX, XMMATRIX, XMMATRIX,
		XMFLOAT3, XMFLOAT4, float, XMFLOAT4);
	void RenderShader(ID3D11DeviceContext*, int, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer, * m_lightBuffer, * m_transformBuffer, * m_colorBuffer;

	ID3D11SamplerState* m_sampleState;
};

#endif // !_COLORSHADERCLASS_H_
