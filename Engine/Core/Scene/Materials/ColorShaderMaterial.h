#ifndef _COLORSHADERMATERIAL_H_
#define _COLORSHADERMATERIAL_H_

#include <directxmath.h>

using namespace DirectX;


class ColorShaderMaterial
{
public:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;

	ColorShaderMaterial(ID3D11Device* device, ID3D11DeviceContext* deviceContext) {
		m_device = device;
		m_deviceContext = deviceContext;
	};
	ColorShaderMaterial(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const char* _name, XMFLOAT4 _color) {
		m_device = device;
		m_deviceContext = deviceContext;
		name = _name;
		color = _color;
	}
	~ColorShaderMaterial() {

		delete name;
	}

	friend ifstream& operator>> (ifstream& fin, ColorShaderMaterial* m)
	{
		//string tmp;

		//// texture paths
		//fin >> tmp; m->name = tmp.c_str();
		//fin >> tmp; m->color_map_path = tmp.c_str();
		//fin >> tmp; m->normal_map_path = tmp.c_str();
		//fin >> tmp; m->specular_map_path = tmp.c_str();

		//// value fields
		//fin >> m->normalStrength;
		//fin >> m->specularFocus;
		//fin >> m->specularStrenght;

		//// connect the textures
		//m->m_textureArray = new TextureArrayClass;
		//m->m_textureArray->Initialize(m->m_device, m->m_deviceContext,
		//	m->color_map_path, m->normal_map_path, m->specular_map_path);

		return fin;
	}

	const char* name;

	XMFLOAT4 color = XMFLOAT4(1, 1, 1, 1);
};


#endif