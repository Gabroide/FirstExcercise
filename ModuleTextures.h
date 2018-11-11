#ifndef __ModuleTextures_h__
#define __ModuleTextures_h__

#include<list>

#include "Module.h"
#include "Globals.h"

#include "GL/glew.h"

#include "DevIL/include/IL/il.h"
#include "DevIL/include/IL/ilu.h" COMMENT
#include "DevIL/include/IL/ilut.h" COMMENT

struct SDL_Texture;

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool Init() override;
	bool CleanUp() override;

	GLuint Load(const char* path);
	void Unload(unsigned id);

public:
	ILinfo lastImageInfo;
};

#endif