#ifndef _SPRITECLASS_H_
#define _SPRITECLASS_H_

#include <d3d11.h>

#include "../../Core/Renderer/Utils/textureclass.h"
#include <DirectXMath.h>

using namespace DirectX;

class SpriteClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	SpriteClass();
	SpriteClass(const SpriteClass&);
	~SpriteClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, int, int, const char*, int, int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, int);
	
	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext*, int, int);
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext* ,const char*);
	void ReleaseTexture();

private:
	ID3D11Buffer* m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;

	int m_screenWidth, m_screenHeight;
	int m_spriteWidth, m_spriteHeight;
	int m_previousPosX, m_previousPosY;
};

#endif