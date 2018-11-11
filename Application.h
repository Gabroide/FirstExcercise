#pragma once

#include<list>

#include "Globals.h"
#include "Module.h"
#include "SDL.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleGrid;
class ModuleEditor;
class ModuleCamera;
class ModuleProgram;
class ModuleModelLoader;
class ModuleTimer;

class Application
{
public:
	Application();
	~Application();

	bool Init();
	bool CleanUp();

	update_status Update();
	
public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleInput* input = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleProgram* shaderProgram = nullptr;
	ModuleModelLoader* modelLoader = nullptr;
	ModuleGrid* grid = nullptr;
	ModuleTimer* timer = nullptr;
	
public:
	float fps;

private:
	void FPSInit();
	void FPSCalculation();

private:
	std::list<Module*> modules;

	Uint32 frametimes[FRAME_VALUES];
	Uint32 frametimelast;
	Uint32 framecount;
};

extern Application* App;