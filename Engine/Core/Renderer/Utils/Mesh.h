#ifndef _MESH_H_
#define _MESH_H_


#include <d3d11.h>
#include <directxmath.h>

#include <vector>
#include <fstream>

using namespace std;
using namespace DirectX;

#include "../../Core/Renderer/Utils/textureclass.h"
#include "../../Core/Renderer/Utils/texturearrayclass.h"
#include "../../Scene/Entity/Transform.h"


class Mesh
{
public:
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
		float tx, ty, tz;
		float bx, by, bz;
	};

private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
		XMFLOAT3 tangent;
		XMFLOAT3 binormal;
	};

	// the following two structures are used to calculate the tangent and binormal
	struct TempVertexType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};
	struct VectorType
	{
		float x, y, z;
	};


	//here we hold instance information
	struct InstanceType
	{
		//XMMATRIX translation;
		//XMMATRIX rotation;
		//XMMATRIX scale;
		//XMFLOAT4X4 translation;
		//XMFLOAT3 position;
		//XMFLOAT3 rotation;
	};

	// types for loading from obj file
	typedef struct
	{
		int vIndex1, vIndex2, vIndex3;
		int tIndex1, tIndex2, tIndex3;
		int nIndex1, nIndex2, nIndex3;
	} FaceType;

public:
	Mesh();
	~Mesh();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, bool, const char*);
	void Shutdown();

	bool UpdateTransform(ID3D11DeviceContext*, Transform*);
	void PrepareForRendering(ID3D11DeviceContext*);

	int GetVertexCount();
	int GetInstanceCount();

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

	XMFLOAT3 GetInstanceTransform(int);
	void SetInstanceTransform(int, XMFLOAT3);


	XMMATRIX m_translation;
	XMMATRIX m_rotation;
	XMMATRIX m_scale;

	bool Static;

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, const char*, const char*, const char*);
	void ReleaseTextures();

	bool LoadModel(const char*);
	bool LoadData(const char*, int&, int&, int&, int&);
	void ReleaseModel();

	//func for tangent and binormal vectors
	void CalculateModelVectors();
	void CalculateTangentBinormal(TempVertexType, TempVertexType, TempVertexType, VectorType&, VectorType&);

	// load the model data from file
	friend ifstream& operator>> (ifstream fin, Mesh* m)
	{
		//to do
	}

public:
	int m_OriginalVertexCount;
	int m_UVCount;
	int m_NormalCount;
	int m_FaceCount;

private:

	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer, *m_instanceBuffer;

	int m_instanceCount;
	//vector<XMFLOAT3> m_instancesPositions;

	int m_vertexCount;
	int m_indexCount;

	TextureClass* m_Texture;

	ModelType* m_model;
};

#endif