#include "arrowsclass.h"

ArrowsClass::ArrowsClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

ArrowsClass::ArrowsClass(const ArrowsClass& other)
{
}

ArrowsClass::~ArrowsClass()
{
}

bool ArrowsClass::Initialize(ID3D11Device* device)
{
	bool result;

	// Initialize the vertex and index buffer that hold the geometry for the terrain.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	return true;
}

void ArrowsClass::Shutdown()
{
	// Release the vertex and index buffer.
	ShutdownBuffers();

	return;
}

void ArrowsClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}

bool ArrowsClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	int index;
	float positionX, positionZ;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Create the vertex array.
	vertices = new VertexType[12];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[18];
	if (!indices)
	{
		return false;
	}


	// X
	vertices[0].position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertices[0].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f);
	vertices[1].position = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertices[1].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f);
	vertices[2].position = XMFLOAT3(0.95f, 0.0f, 0.05f);
	vertices[2].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f);
	vertices[3].position = XMFLOAT3(0.95f, 0.0f, -0.05f);
	vertices[3].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 1;
	indices[3] = 3;
	indices[4] = 1;
	indices[5] = 2;

	// Y
	vertices[4].position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertices[4].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);
	vertices[5].position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertices[5].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);
	vertices[6].position = XMFLOAT3(0.05f, 0.95f, 0.0f);
	vertices[6].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);
	vertices[7].position = XMFLOAT3(-0.05f, 0.95f, 0.0f);
	vertices[7].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);

	indices[6] = 4;
	indices[7] = 5;
	indices[8] = 5;
	indices[9] = 6;
	indices[10] = 5;
	indices[11] = 7;

	// Z
	vertices[8].position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertices[8].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f);
	vertices[9].position = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertices[9].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f);
	vertices[10].position = XMFLOAT3(0.05f, 0.0f, 0.95f);
	vertices[10].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f);
	vertices[11].position = XMFLOAT3(-0.05f, 0.0f, 0.95f);
	vertices[11].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f);

	indices[12] = 8;
	indices[13] = 9;
	indices[14] = 9;
	indices[15] = 10;
	indices[16] = 9;
	indices[17] = 11;
	

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * 12;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * 18;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void ArrowsClass::ShutdownBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

void ArrowsClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case a line list.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	return;
}