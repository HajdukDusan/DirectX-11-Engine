#include "FileLoader.h"

namespace FileLoader
{
	namespace {

		typedef struct
		{
			float x, y, z;
		}VertexType;

		typedef struct
		{
			int vIndex1, vIndex2, vIndex3;
			int tIndex1, tIndex2, tIndex3;
			int nIndex1, nIndex2, nIndex3;
		}FaceType;

		// helper functions
		bool ReadFileCounts(const char* filename, int& vertexCount, int& textureCount, int& normalCount, int& faceCount)
		{
			ifstream fin;
			char input;

			// Initialize the counts.
			vertexCount = 0;
			textureCount = 0;
			normalCount = 0;
			faceCount = 0;

			// Open the file.
			fin.open(filename);

			// Check if it was successful in opening the file.
			if (fin.fail() == true)
			{
				return false;
			}

			// Read from the file and continue to read until the end of the file is reached.
			fin.get(input);
			while (!fin.eof())
			{
				// If the line starts with 'v' then count either the vertex, the texture coordinates, or the normal vector.
				if (input == 'v')
				{
					fin.get(input);
					if (input == ' ') { vertexCount++; }
					if (input == 't') { textureCount++; }
					if (input == 'n') { normalCount++; }
				}

				// If the line starts with 'f' then increment the face count.
				if (input == 'f')
				{
					fin.get(input);
					if (input == ' ') { faceCount++; }
				}

				// Otherwise read in the remainder of the line.
				while (input != '\n')
				{
					fin.get(input);
				}

				// Start reading the beginning of the next line.
				fin.get(input);
			}

			// Close the file.
			fin.close();

			return true;
		}
	}

	Mesh::ModelType* LoadObjFile(const char* filename, int& newVertexCount, int& originalVertexCount, int& textureCount, int& normalCount, int& faceCount)
	{
		// Read in the number of vertices, tex coords, normals, and faces so that the data structures can be initialized with the exact sizes needed.
		if (!ReadFileCounts(filename, originalVertexCount, textureCount, normalCount, faceCount)) {
			return nullptr;
		}

		VertexType* vertices, * texcoords, * normals;
		FaceType* faces;
		ifstream fin;
		int vertexIndex, texcoordIndex, normalIndex, faceIndex, vIndex, tIndex, nIndex;
		char input, input2;


		// Initialize the four data structures.
		vertices = new VertexType[originalVertexCount];
		if (!vertices)
		{
			return nullptr;
		}

		texcoords = new VertexType[textureCount];
		if (!texcoords)
		{
			return nullptr;
		}

		normals = new VertexType[normalCount];
		if (!normals)
		{
			return nullptr;
		}

		faces = new FaceType[faceCount];
		if (!faces)
		{
			return nullptr;
		}

		// Initialize the indexes.
		vertexIndex = 0;
		texcoordIndex = 0;
		normalIndex = 0;
		faceIndex = 0;

		// Open the file.
		fin.open(filename);

		// Check if it was successful in opening the file.
		if (fin.fail() == true)
		{
			return nullptr;
		}

		// Read in the vertices, texture coordinates, and normals into the data structures.
		// Important: Also convert to left hand coordinate system since Maya uses right hand coordinate system.
		fin.get(input);
		while (!fin.eof())
		{
			if (input == 'v')
			{
				fin.get(input);

				// Read in the vertices.
				if (input == ' ')
				{
					fin >> vertices[vertexIndex].x >> vertices[vertexIndex].y >> vertices[vertexIndex].z;

					// Invert the Z vertex to change to left hand system.
					vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;
					vertexIndex++;
				}

				// Read in the texture uv coordinates.
				if (input == 't')
				{
					fin >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;

					// Invert the V texture coordinates to left hand system.
					texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;
					texcoordIndex++;
				}

				// Read in the normals.
				if (input == 'n')
				{
					fin >> normals[normalIndex].x >> normals[normalIndex].y >> normals[normalIndex].z;

					// Invert the Z normal to change to left hand system.
					normals[normalIndex].z = normals[normalIndex].z * -1.0f;
					normalIndex++;
				}
			}

			// Read in the faces.
			if (input == 'f')
			{
				fin.get(input);
				if (input == ' ')
				{
					// Read the face data in backwards to convert it to a left hand system from right hand system.
					fin >> faces[faceIndex].vIndex3 >> input2 >> faces[faceIndex].tIndex3 >> input2 >> faces[faceIndex].nIndex3
						>> faces[faceIndex].vIndex2 >> input2 >> faces[faceIndex].tIndex2 >> input2 >> faces[faceIndex].nIndex2
						>> faces[faceIndex].vIndex1 >> input2 >> faces[faceIndex].tIndex1 >> input2 >> faces[faceIndex].nIndex1;
					faceIndex++;
				}
			}

			// Read in the remainder of the line.
			while (input != '\n')
			{
				fin.get(input);
			}

			// Start reading the beginning of the next line.
			fin.get(input);
		}

		// Close the file.
		fin.close();




		newVertexCount = faceCount * 3;
		Mesh::ModelType* model = new Mesh::ModelType[newVertexCount];


		// Now loop through all the faces and output the three vertices for each face.
		for (int i = 0; i < faceIndex; i++)
		{
			vIndex = faces[i].vIndex1 - 1;
			tIndex = faces[i].tIndex1 - 1;
			nIndex = faces[i].nIndex1 - 1;

			model[i * 3].x = vertices[vIndex].x;
			model[i * 3].y = vertices[vIndex].y;
			model[i * 3].z = vertices[vIndex].z;
			model[i * 3].tu = texcoords[tIndex].x;
			model[i * 3].tv = texcoords[tIndex].y;
			model[i * 3].nx = normals[nIndex].x;
			model[i * 3].ny = normals[nIndex].y;
			model[i * 3].nz = normals[nIndex].z;

			vIndex = faces[i].vIndex2 - 1;
			tIndex = faces[i].tIndex2 - 1;
			nIndex = faces[i].nIndex2 - 1;

			model[i * 3 + 1].x = vertices[vIndex].x;
			model[i * 3 + 1].y = vertices[vIndex].y;
			model[i * 3 + 1].z = vertices[vIndex].z;
			model[i * 3 + 1].tu = texcoords[tIndex].x;
			model[i * 3 + 1].tv = texcoords[tIndex].y;
			model[i * 3 + 1].nx = normals[nIndex].x;
			model[i * 3 + 1].ny = normals[nIndex].y;
			model[i * 3 + 1].nz = normals[nIndex].z;

			vIndex = faces[i].vIndex3 - 1;
			tIndex = faces[i].tIndex3 - 1;
			nIndex = faces[i].nIndex3 - 1;

			model[i * 3 + 2].x = vertices[vIndex].x;
			model[i * 3 + 2].y = vertices[vIndex].y;
			model[i * 3 + 2].z = vertices[vIndex].z;
			model[i * 3 + 2].tu = texcoords[tIndex].x;
			model[i * 3 + 2].tv = texcoords[tIndex].y;
			model[i * 3 + 2].nx = normals[nIndex].x;
			model[i * 3 + 2].ny = normals[nIndex].y;
			model[i * 3 + 2].nz = normals[nIndex].z;
		}

		// Release the four data structures.
		if (vertices) { delete[] vertices; };
		if (texcoords) { delete[] texcoords; };
		if (normals) { delete[] normals; };
		if (faces) { delete[] faces; };

		return model;
	}
}