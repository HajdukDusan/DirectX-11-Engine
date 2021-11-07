#include "CameraSceneNavigation.h"

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