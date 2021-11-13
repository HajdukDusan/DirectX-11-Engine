#ifndef _MESHCOMPONENT_H_
#define _MESHCOMPONENT_H_

#pragma once
#include "../Component.h"
#include "../../../Renderer/Utils/Mesh.h"

class MeshComponent : public Component
{
public:
	Mesh* m_Mesh;
	Material* m_Material;

	MeshComponent(Mesh* model, Material* material)
	{
		m_Mesh = model;
		m_Material = material;
	}

	void SerializeObject()
	{

	}

	bool Render(
		ID3D11DeviceContext* deviceContext,
		XMMATRIX worldMatrix,
		XMMATRIX viewMatrix,
		XMMATRIX projectionMatrix,
		Transform* entityTransform,
		Transform* cameraTransform,
		LightClass* light)
	{
		// update the objects position, rotation and scale
		if (!m_Mesh->UpdateTransform(deviceContext, entityTransform)) return false;
		// prepare the model for rendering
		m_Mesh->PrepareForRendering(deviceContext);
		// render the model with the material shader
		return m_Material->Render(deviceContext, worldMatrix, viewMatrix, projectionMatrix, cameraTransform, m_Mesh, light);
	}
};

#endif