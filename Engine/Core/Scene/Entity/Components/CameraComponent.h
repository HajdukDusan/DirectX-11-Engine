#ifndef _CAMERACOMPONENT_H_
#define _CAMERACOMPONENT_H_

#pragma once
#include <directxmath.h>

#include "../Component.h"
#include "../Transform.h"

using namespace DirectX;

class CameraComponent : public Component
{
public:
	CameraComponent();
	virtual ~CameraComponent();

	void RotateY(float);

	void Render(Transform*);
	void RenderBaseViewMatrix(Transform*);

	void GetViewMatrix(XMMATRIX&);
	void GetBaseViewMatrix(XMMATRIX&);

private:
	XMMATRIX m_viewMatrix, m_baseViewMatrix;
};

#endif