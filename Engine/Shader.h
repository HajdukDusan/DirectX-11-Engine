#ifndef _SHADER_H_
#define _SHADER_H_

#pragma once
#include <directxmath.h>
using namespace DirectX;

class CameraClass;
class ModelClass;
class Material;
class LightClass;

class Shader
{
public:
	virtual bool Render(
		ID3D11DeviceContext* deviceContext,
		XMMATRIX worldMatrix,
		XMMATRIX viewMatrix,
		XMMATRIX projectionMatrix,
		CameraClass* camera,
		ModelClass* model,
		Material* material,
		LightClass* light)
	{
		return false;
	}

	virtual ~Shader() {};
};

#endif

