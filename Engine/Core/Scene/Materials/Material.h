#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#pragma once
#include <d3d11.h>
#include <directxmath.h>

#include "../../Renderer/Shaders/Shader.h"



using namespace DirectX;

class Transform;
class Mesh;
class LightClass;

class Material
{
public:
	const char* m_Name;
	Shader*		m_Shader;

	Material() {};

	Material(const char* name, Shader* shader)
	{
		m_Shader = shader;
		m_Name = name;
	}

	virtual bool Render(
		ID3D11DeviceContext* deviceContext,
		XMMATRIX worldMatrix,
		XMMATRIX viewMatrix,
		XMMATRIX projectionMatrix,
		Transform* cameraTransform,
		Mesh* model,
		LightClass* light)
	{
		return m_Shader->Render(
			deviceContext,
			worldMatrix,
			viewMatrix,
			projectionMatrix,
			cameraTransform,
			model,
			this,
			light);
	}

	virtual ~Material()
	{
		//delete[] m_Name;
	};
};
#endif