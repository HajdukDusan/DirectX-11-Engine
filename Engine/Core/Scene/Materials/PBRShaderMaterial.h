#ifndef _PBRSHADERMATERIAL_H_
#define _PBRSHADERMATERIAL_H_

#include "../../Renderer/Utils/texturearrayclass.h"
#include "Material.h"
#include "../../Renderer/Shaders/PBR/PBRshaderclass.h"

class Mesh;
class LightClass;

class PBRShaderMaterial : public Material
{
public:
	TextureArrayClass* m_textureArray;

	const char* color_map_path;
	const char* normal_map_path;
	const char* specular_map_path;

	float normalStrength = 0.15;
	float specularFocus = 10;
	float specularStrenght = 1;

	PBRShaderMaterial(PBRShaderClass* PBRShader, ID3D11Device* device, ID3D11DeviceContext* deviceContext, const char* _name, const char* colorTextureName, const char* normalTextureName, const char* specularTextureName)
	{
		// setup the PBR shader
		m_Shader = PBRShader;

		m_Name = _name;
		color_map_path = colorTextureName;
		normal_map_path = normalTextureName;
		specular_map_path = specularTextureName;
		m_textureArray = new TextureArrayClass;
		m_textureArray->Initialize(device, deviceContext, colorTextureName, normalTextureName, specularTextureName);
	}
	~PBRShaderMaterial() {
		if (m_textureArray)
		{
			m_textureArray->Shutdown();
			delete m_textureArray;
		}

		//delete[] color_map_path;
		//delete[] normal_map_path;
		//delete[] specular_map_path;
	}

	friend ifstream& operator>> (ifstream& fin, PBRShaderMaterial* m)
	{
		string tmp;

		// texture paths
		fin >> tmp; m->m_Name = tmp.c_str();
		fin >> tmp; m->color_map_path = tmp.c_str();
		fin >> tmp; m->normal_map_path = tmp.c_str();
		fin >> tmp; m->specular_map_path = tmp.c_str();

		// value fields
		fin >> m->normalStrength;
		fin >> m->specularFocus;
		fin >> m->specularStrenght;

		// connect the textures
		//m->m_textureArray = new TextureArrayClass;
		//m->m_textureArray->Initialize(m->m_device, m->m_deviceContext,
		//	m->color_map_path, m->normal_map_path, m->specular_map_path);

		return fin;
	}

	bool Render(
		ID3D11DeviceContext* deviceContext,
		XMMATRIX worldMatrix,
		XMMATRIX viewMatrix,
		XMMATRIX projectionMatrix,
		Transform* transform,
		Mesh* model,
		LightClass* light)
		override
	{
		return m_Shader->Render(deviceContext, worldMatrix, viewMatrix, projectionMatrix,
			transform, model, this, light);
	}
};

#endif // !_PBRSHADERCOMPONENT_H_
