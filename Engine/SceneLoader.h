#ifndef _SCENELOADER_H_
#define _SCENELOADER_H_

#include <fstream>
#include <vector>

#include "modelclass.h"
#include "PBRShaderMaterial.h"
#include "ColorShaderMaterial.h"

using namespace std;

class SceneLoader
{
public:
	SceneLoader(D3DClass* Direct3D,
				const char* scenePath, vector<ModelClass*>& models,
				vector<PBRShaderMaterial*>& pbr_materials,
				vector<ColorShaderMaterial*>& color_materials) {

		ifstream fin;
		char input;
		int array_size;

		fin.open(scenePath);

		fin.get(input);
		while (input != ':')
		{
			fin.get(input);
		}


		// Load pbr materials
		fin >> array_size;
		for (int i = 0; i < array_size; i++)
		{
			PBRShaderMaterial* tmp = new PBRShaderMaterial(Direct3D->GetDevice(), Direct3D->GetDeviceContext());
			// overriding the operator
			fin >> tmp;
			pbr_materials.push_back(tmp);
		}

		// Load color materials
		fin >> array_size;
		for (int i = 0; i < array_size; i++)
		{
			//ColorShaderMaterial* tmp = new ColorShaderMaterial();
			//fin >> tmp;
			//color_materials.push_back(tmp);
		}


		// Load models
		fin >> array_size;
		for (int i = 0; i < array_size; i++)
		{
			ModelClass* m = new ModelClass();
			//fin >> m;
			//models.push_back();
		}

		//// Create the model using the vertex count that was read in.
		//m_model = new ModelType[m_vertexCount];
		//if (!m_model)
		//{
		//	return false;
		//}

		//// Read up to the beginning of the data.
		//fin.get(input);
		//while (input != ':')
		//{
		//	fin.get(input);
		//}
		//fin.get(input);
		//fin.get(input);

		//// Read in the vertex data.
		//for (i = 0; i < m_vertexCount; i++)
		//{
		//	fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		//	fin >> m_model[i].tu >> m_model[i].tv;
		//	fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
		//}

		//// Close the model file.
		fin.close();
	}
	~SceneLoader();
};

#endif // !_SCENELOADER_H_
