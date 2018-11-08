#pragma once
#include "Module.h"
#include "Globals.h"

#include "SDL.h"
#include "SDL_scancode.h"
#include "SDL_gamecontroller.h"

#define MAX_MOUSE_BUTTONS 5
#define MAX_BUTTONS 20

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

	KeyState GetMouseButton(int id) const;

	KeyState GetController(int id) const
	{
		return player_controll[id];
	}

	int GetMouseX() const
	{
		return mouse_x;
	}

	int GetMouseY() const
	{
		return mouse_y;
	}

	int GetMouseZ() const
	{
		return mouse_z;
	}

	int GetMouseXMotion() const
	{
		return mouse_x_motion;
	}

	int GetMouseYMotion() const
	{
		return mouse_y_motion;
	}

public:
	KeyState* keyboard = nullptr;
	KeyState mouse_buttons[MAX_MOUSE_BUTTONS];
	KeyState player_controll[MAX_BUTTONS];

	SDL_GameController *controller = nullptr;

	int mouse_x;
	int mouse_y;
	int mouse_z;
	int mouse_x_motion;
	int mouse_y_motion;

	bool move_up = false;
	bool move_left = false;
	bool move_right = false;
	bool stop = false;

private:
	//KeyState * keyboard;
	//const Uint8* keyboard = NULL;
};