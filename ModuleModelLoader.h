#ifndef __ModuleModelLoader_h__
#define __ModuleModelLoader_h__

#include <vector>

#include "Module.h"
#include "Globals.h"

#include <assimp/mesh.h>
#include <assimp/material.h>

#include "GL/glew.h"

class ModuleModelLoader : public Module
{
public:
	ModuleModelLoader();
	~ModuleModelLoader();

	bool Init();
	bool CleanUp();

	void ChooseModel(int num);
	void ImportModel(const char* path);
	void CleanModel();

	void GenerateMesh(const aiMesh* aiMesh);
	void GenerateMaterial(const aiMaterial* aiMaterial);

public:
	struct Mesh
	{
		unsigned vbo = 0;
		unsigned ibo = 0;
		unsigned material = 0;
		unsigned numVertices = 0;
		unsigned numIndices = 0;
	};

	struct Material
	{
		unsigned texture0 = 0;
		unsigned width = 0;
		unsigned height = 0;
	};

public:
	std::vector<Mesh> meshes;
	std::vector<Material> materials;

	int modelRendered = 1;
};

#endif