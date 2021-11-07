#ifndef _ARROWSCLASS_H_
#define _ARROWSCLASS_H_

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class ArrowsClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	ArrowsClass();
	ArrowsClass(const ArrowsClass&);
	~ArrowsClass();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
};

#endif