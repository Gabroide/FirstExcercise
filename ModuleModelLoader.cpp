#include "Globals.h"
#include "Application.h"
#include "ModuleModelLoader.h"
#include "ModuleTextures.h"
#include "ModuleEditor.h"
#include "GL/glew.h"
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "MathGeoLib.h"
#include "SDL/include/SDL.h"


ModuleModelLoader::ModuleModelLoader()
{

}

// Destructor
ModuleModelLoader::~ModuleModelLoader()
{

}

bool ModuleModelLoader::Init()
{
	ChooseModel(1);

	return true;
}

void ModuleModelLoader::ChooseModel(int num)
{
	if (num == modelRendered) 
	{ 
		return; 
	}

	char* path = "";
	switch (num)
	{
	case 1:
		path = "BakerHouse.fbx";
		break;
	case 2:
		path = "";
		break;
	case 3:
		path = "";
		break;
	default:
		modelRendered = 1;
		return;
	}

	modelRendered = num;

	ImportModel(path);
}

void ModuleModelLoader::ImportModel(const char* path)
{
	const aiScene* scene = aiImportFile(path, aiProcess_Triangulate);

	if (scene == NULL) {
		const char* a = aiGetErrorString();
		
		LOG("Importing error");
		
		return;
	}
	else 
	{
		App->editor->AddLog("Model: ");
		App->editor->AddLog(path);
		App->editor->AddLog("\n");
	}

	for (unsigned i = 0; i < scene->mNumMeshes; ++i)
	{
		GenerateMesh(scene->mMeshes[i]);
	}

	for (unsigned i = 0; i < scene->mNumMaterials; ++i)
	{
		GenerateMaterial(scene->mMaterials[i]);
	}
}

bool ModuleModelLoader::CleanUp()
{
	CleanModel();

	return true;
}

void ModuleModelLoader::CleanModel()
{
	for (unsigned i = 0; i < meshes.size(); ++i)
	{
		if (meshes[i].vbo != 0)
		{
			glDeleteBuffers(1, &meshes[i].vbo);
		}

		if (meshes[i].ibo != 0)
		{
			glDeleteBuffers(1, &meshes[i].ibo);
		}
	}
	meshes.clear();

	for (unsigned i = 0; i < materials.size(); ++i)
	{
		if (materials[i].texture0 != 0)
		{
			App->textures->Unload(materials[i].texture0);
		}
	}
	materials.clear();
}

void ModuleModelLoader::GenerateMesh(const aiMesh* aiMesh)
{
	Mesh mesh;

	glGenBuffers(1, &mesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

	glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * 3 + sizeof(float) * 2)*aiMesh->mNumVertices, nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 3 * aiMesh->mNumVertices, aiMesh->mVertices);

	math::float2* texture_coords = (math::float2*)glMapBufferRange(GL_ARRAY_BUFFER, sizeof(float) * 3 * aiMesh->mNumVertices, sizeof(float) * 2 * aiMesh->mNumVertices, GL_MAP_WRITE_BIT);
	for (unsigned i = 0; i < aiMesh->mNumVertices; ++i)
	{
		texture_coords[i] = math::float2(aiMesh->mTextureCoords[0][i].x, aiMesh->mTextureCoords[0][i].y);
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &mesh.ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned)*aiMesh->mNumFaces * 3, nullptr, GL_STATIC_DRAW);

	unsigned* indices = (unsigned*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned)*aiMesh->mNumFaces * 3, GL_MAP_WRITE_BIT);

	for (unsigned i = 0; i < aiMesh->mNumFaces; ++i)
	{
		assert(aiMesh->mFaces[i].mNumIndices == 3);

		*(indices++) = aiMesh->mFaces[i].mIndices[0];
		*(indices++) = aiMesh->mFaces[i].mIndices[1];
		*(indices++) = aiMesh->mFaces[i].mIndices[2];
	}

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	mesh.material = aiMesh->mMaterialIndex;
	mesh.numVertices = aiMesh->mNumVertices;
	mesh.numIndices = aiMesh->mNumFaces * 3;

	meshes.push_back(mesh);
}

void ModuleModelLoader::GenerateMaterial(const aiMaterial* aiMaterial)
{
	Material material;

	aiString file;
	aiTextureMapping mapping;
	unsigned uvindex = 0;

	if (aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file, &mapping, &uvindex) == AI_SUCCESS)
	{
		App->editor->AddLog("Texture: ");
		App->editor->AddLog(file.data);
		App->editor->AddLog("\n");
		material.texture0 = App->textures->Load(file.data);
		material.width = App->textures->lastImageInfo.Width;
		material.height = App->textures->lastImageInfo.Height;
	}

	materials.push_back(material);
}
