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
	static float pastMouseY = guiInputHandler->MousePos.y;

	static float r = sqrt(
		pow(transform->translation.x, 2) +
		pow(transform->translation.y, 2) +
		pow(transform->translation.z, 2)
	);

	static float phi = atan2(transform->translation.z / transform->translation.x, transform->translation.x);
	static float theta = acos(transform->translation.y / r);

	if (guiInputHandler->MouseWheel != 0)
	{
		r -= guiInputHandler->MouseWheel;

		transform->translation.x = r * cos(theta) * cos(phi);
		transform->translation.y = r * sin(theta);
		transform->translation.z = r * cos(theta) * sin(phi);
	}

	if (guiInputHandler->MouseDown[MOUSE_SCROLL_CLICK]) {
		if (guiInputHandler->MousePos.x != pastMouseX || guiInputHandler->MousePos.y != pastMouseY)
		{
			float Yangle = (guiInputHandler->MousePos.x - pastMouseX) * 0.5f;
			transform->rotation.y += Yangle;

			float Xangle = (guiInputHandler->MousePos.y - pastMouseY) * 0.5f;
			transform->rotation.x += Xangle;

			theta += Xangle * XM_PI / 180;
			phi -= Yangle * XM_PI / 180;

			transform->translation.x = r * cos(theta) * cos(phi);
			transform->translation.y = r * sin(theta);
			transform->translation.z = r * cos(theta) * sin(phi);
		}
	}

	pastMouseX = guiInputHandler->MousePos.x;
	pastMouseY = guiInputHandler->MousePos.y;
}

#endif 