#include "GameObject.h"

GameObject::GameObject(ModelClass* model, Material* material)
{
	m_Name = "GameObject";
	m_Model = model;
	m_Material = material;
}
GameObject::GameObject(const char* name, ModelClass* model, Material* material)
{
	m_Name = name;
	m_Model = model;
	m_Material = material;
}



bool GameObject::Render(ID3D11DeviceContext* deviceContext, 
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	CameraClass* camera, LightClass* light)
{
	// update the objects position, rotation and scale
	if(!m_Model->UpdateTransform(deviceContext, (Transform*) this)) return false;
	// prepare the model for rendering
	m_Model->PrepareForRendering(deviceContext);

	// render the model with the material shader
	return m_Material->Render(deviceContext, worldMatrix, viewMatrix, projectionMatrix, camera, m_Model, light);
}

GameObject::~GameObject()
{
	//delete[] m_Name;
}