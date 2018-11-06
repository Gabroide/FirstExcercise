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
//class ModuleCamera; COMMENT
//class ModuleModelLoader; COMMENT	
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
	//ModuleCamera* camera = nullptr; COMMENT
	ModuleEditor* editor = nullptr;
	//ModuleProgram* program = nullptr; COMMENT
	//ModuleModelLoader* modelLoader = nullptr; COMMENT

private:

	std::list<Module*> modules;

};

extern Application* App;
