#ifndef _FILELOADER_H_
#define _FILELOADER_H_

#pragma once
#include <iostream>
#include <fstream>
#include "../Renderer/Utils/Mesh.h"

using namespace std;

namespace FileLoader
{
	// load the obj model, no index buffer
	Mesh::ModelType* LoadObjFile(
		const char* filename,
		int& newVertexCount,
		int& originalVertexCount,
		int& textureCount,
		int& normalCount,
		int& faceCount);
}
#endif
