#pragma once
#ifndef _CAMERASCENENAVIGATION_H
#define _CAMERASCENENAVIGATION_H

#include "Transform.h"
#include "GUI/ImGui/imgui.h"
// mouse inputs
#define MOUSE_LEFT_CLICK    0
#define MOUSE_RIGHT_CLICK   1
#define MOUSE_SCROLL_CLICK  2
#define MOUSE_POS_X         3
#define MOUSE_POS_Y         4

void MoveCamera(Transform* transform, ImGuiIO* guiInputHandler);

#endif 