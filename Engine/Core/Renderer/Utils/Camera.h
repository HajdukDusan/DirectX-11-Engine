#ifndef _CAMERA_H
#define _CAMERA_H

#pragma once
#include <directxmath.h>
#include "../../Scene/Entity/Transform.h"

class Camera
{
public:
	Transform* m_Transform;

	Camera(Transform*);
	~Camera();

	void RotateY(float);

	void Render();
	void RenderBaseViewMatrix();

	void GetViewMatrix(XMMATRIX&);
	void GetBaseViewMatrix(XMMATRIX&);

private:
	XMMATRIX m_viewMatrix, m_baseViewMatrix;

};

#endif
