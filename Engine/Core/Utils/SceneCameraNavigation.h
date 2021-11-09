#pragma once
#ifndef _SCENECAMERANAVIGATION_H
#define _SCENECAMERA_H

#include "../Scene/Entity/Transform.h"
#include "../../GUI/ImGui/imgui.h"
// mouse inputs
#define MOUSE_LEFT_CLICK    0
#define MOUSE_RIGHT_CLICK   1
#define MOUSE_SCROLL_CLICK  2
#define MOUSE_POS_X         3
#define MOUSE_POS_Y         4


void MoveCamera(Transform* transform, ImGuiIO* guiInputHandler)
{
	static float pastMouseX = guiInputHandler->MousePos.x;

	//Horizontal Camera Rotation Around World Origin
	if (guiInputHandler->MouseDown[MOUSE_SCROLL_CLICK]) {
		if (guiInputHandler->MousePos.x != pastMouseX)
		{
			float angle = -(guiInputHandler->MousePos.x - pastMouseX) * 0.01f;
			float x = transform->translation.x;
			float z = transform->translation.z;

			//move cam
			transform->translation.x = x * cos(angle) - z * sin(angle);
			transform->translation.z = z * cos(angle) + x * sin(angle);

			//rotate cam
			transform->rotation.y -= angle * 180 / XM_PI;
		}
	}

	pastMouseX = guiInputHandler->MousePos.x;
}

#endif 