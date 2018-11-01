#pragma once
#include "Module.h"
#include "Globals.h"

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
	update_status Update();
	bool CleanUp();

	KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

private:
	KeyState* keyboard = nullptr;
	//const Uint8 *keyboard = NULL;
};