#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#pragma once
#include "../../Transform.h"
#include "modelclass.h"
#include "../../Core/Scene/Materials/Material.h"

class GameObject : public Transform
{
public:
	const char*		m_Name;
	ModelClass*		m_Model;
	Material*		m_Material;

	GameObject(ModelClass* model, Material* material);
	GameObject(const char* name, ModelClass* model, Material* material);

	bool Render(
		ID3D11DeviceContext* deviceContext,
		XMMATRIX worldMatrix,
		XMMATRIX viewMatrix,
		XMMATRIX projectionMatrix,
		CameraClass* camera,
		LightClass* light);

	virtual ~GameObject();
};

#endif
