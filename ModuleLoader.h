#ifndef __MODULE_LOADER_h__
#define __MODULE_LOADER_h__

#include <vector>

#include "Module.h"
#include "Globals.h"

#include <GL/glew.h>

#include <assimp/mesh.h>
#include <assimp/material.h>



class ModuleLoader : 
	public Module
{
public:
	ModuleLoader();
	~ModuleLoader();

	bool Init();
	bool CleanUp();

	void ModelToRender(int num);
	void ImportModel(const char* path);
	void CleanModel();

	void GenerateMesh(const aiMesh* aiMesh);
	void GenerateMaterial(const aiMaterial* aiMaterial);

	int modelRendered = -1;

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

	std::vector<Mesh> meshes;
	std::vector<Material> materials;

private:
	char* path = "";
};

#endif // |_MODULE_LOADER_H