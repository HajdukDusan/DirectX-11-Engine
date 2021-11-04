#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_

#pragma once
#include <directxmath.h>
#include "Transform.h"
using namespace DirectX;

class CameraClass : public Transform
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void RotateY(float);

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Render();
	void GetViewMatrix(XMMATRIX&);

	void RenderBaseViewMatrix();
	void GetBaseViewMatrix(XMMATRIX&);

public:
	//float m_positionX, m_positionY, m_positionZ;
	//float m_rotationX, m_rotationY, m_rotationZ;
private:
	
	
	XMMATRIX m_viewMatrix, m_baseViewMatrix;
};

#endif