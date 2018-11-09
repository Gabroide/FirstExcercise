#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleGrid;
class ModuleEditor;
class ModuleCamera;
class ModuleLoader;	
//class ModuleProgram; COMMENT

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleInput* input = nullptr;
    ModuleGrid* grid = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleEditor* editor = nullptr;
	//ModuleProgram* program = nullptr; COMMENT
	ModuleLoader* modelLoader = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;
