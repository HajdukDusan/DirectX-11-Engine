#ifndef _SHADERMANAGERCLASS_H_
#define _SHADERMANAGERCLASS_H_

#include "d3dclass.h"
#include "colorshaderclass.h"
#include "fontshaderclass.h"
#include "lightshaderclass.h"
#include "textureshaderclass.h"
#include "PBRshaderclass.h"



class ShaderManagerClass
{
public:
	ShaderManagerClass();
	ShaderManagerClass(const ShaderManagerClass&);
	~ShaderManagerClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	bool RenderShaderBasedOnMaterial(
		ID3D11DeviceContext* deviceContext,
		XMMATRIX worldMatrix,
		XMMATRIX viewMatrix,
		XMMATRIX projectionMatrix,
		CameraClass* camera,
		ModelClass* model,
		Material* material,
		LightClass* lightr);

	bool RenderColorShader(ID3D11DeviceContext*, int, int, XMMATRIX, XMMATRIX,
		XMMATRIX, float, XMFLOAT3,
		XMFLOAT4, XMMATRIX, XMMATRIX, XMMATRIX, XMFLOAT3, float, float, XMFLOAT4);

	bool RenderFontShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT4);

	bool RenderLightShader(ID3D11Device*, ID3D11DeviceContext*, int, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4, XMFLOAT4, XMFLOAT3, XMFLOAT4, float);
	bool RenderTextureShader(ID3D11DeviceContext*, int, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*);

private:
	ColorShaderClass* m_ColorShader;
	FontShaderClass* m_FontShader;
	LightShaderClass* m_LightShader;
	TextureShaderClass* m_TextureShader;
	PBRShaderClass* m_PBRShader;


	vector<Shader*> m_Shaders;
};

#endif