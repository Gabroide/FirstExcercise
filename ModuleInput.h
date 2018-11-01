#pragma once
#include "Module.h"
#include "Globals.h"

enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();
	KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

private:
	KeyState * keyboard;
	//const Uint8* keyboard = NULL;
};