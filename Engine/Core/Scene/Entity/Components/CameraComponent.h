#ifndef _CAMERACOMPONENT_H_
#define _CAMERACOMPONENT_H_

#pragma once

#include "../Component.h"
#include "../../../Renderer/Utils/Camera.h"

using namespace DirectX;

class CameraComponent : public Component
{
public:

	Camera* m_Camera;

	CameraComponent(Transform* transform)
	{
		m_Camera = new Camera(transform);
	}
	~CameraComponent()
	{
		delete m_Camera;
	}
};

#endif