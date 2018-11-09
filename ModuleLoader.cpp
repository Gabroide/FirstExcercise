#include "ModuleLoader.h"

#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleEditor.h"

#include <GL/glew.h>

#include <MathGeoLib.h>

#include <SDL.h>

#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

ModuleLoader::ModuleLoader()
{

}

// Destructor
ModuleLoader::~ModuleLoader()
{

}

bool ModuleLoader::Init()
{
	ModelToRender(1);

	return true;
}

void ModuleLoader::ModelToRender(int num)
{
	if (num == modelRendered) 
	{ 
		return; 
	}

	//char* path = ""; COMMENT
	switch (num)
	{
	case 1:
		path = "BakerHouse.fbx";
		break;
	case 2:
//		path = "Trex.fbx"; // COMMENT
		break;
	case 3:
	//	path = "Radioactive_barrel.fbx"; COMMENT
		break;
	default:
		modelRendered = -1;
		return;
	}

	modelRendered = num;

	ImportModel(path);
}

void ModuleLoader::ImportModel(const char* path)
{
	const aiScene* scene = aiImportFile(path, aiProcess_Triangulate);

	if (scene == NULL) {
		const char* a = aiGetErrorString();
		//App->editor->AddLog("Importing error: "); COMMENT
		//App->editor->AddLog(a);
		//App->editor->AddLog("\n");
		return;
	}
	else
	{
		//App->editor->AddLog("Fbx imported: "); COMMENT
		//App->editor->AddLog(path);
		//App->editor->AddLog("\n");
	}

	//App->editor->AddLog("Start GenerateMeshData\n"); COMMENT
	for (unsigned i = 0; i < scene->mNumMeshes; ++i)
	{
		//GenerateMesh(scene->mMeshes[i]); COMMENT
	}

	//App->editor->AddLog("Start GenerateMaterialData\n");
	for (unsigned i = 0; i < scene->mNumMaterials; ++i)
	{
		GenerateMaterial(scene->mMaterials[i]);
	}
}

// Generating Meshes
void ModuleLoader::GenerateMesh(const aiMesh* aiMesh)
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

void ModuleLoader::GenerateMaterial(const aiMaterial* aiMaterial)
{
	Material material;

	aiString file;
	aiTextureMapping mapping;
	unsigned uvindex = 0;

	if (aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file, &mapping, &uvindex) == AI_SUCCESS)
	{
		// COMMENT
		//App->editor->AddLog("Loading texture: ");
		//App->editor->AddLog(file.data);
		//App->editor->AddLog("\n");
		//material.texture0 = App->textures->Load(file.data);
		//material.width = App->textures->lastImageInfo.Width;
		//material.height = App->textures->lastImageInfo.Height;
	}

	materials.push_back(material);
}

// Cleaners
void ModuleLoader::CleanModel()
{
	//App->editor->AddLog("Cleaning meshes\n");
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

	//App->editor->AddLog("Cleaning materials\n");
	for (unsigned i = 0; i < materials.size(); ++i)
	{
		if (materials[i].texture0 != 0)
		{
			App->textures->Unload(materials[i].texture0);
		}
	}
	materials.clear();
}

bool ModuleLoader::CleanUp()
{
	CleanModel();

	return true;
}