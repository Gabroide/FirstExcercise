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

struct Punt {
	int x, y;
};

//typedef unsigned __int8 Uint8; COMMENT

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();

	update_status PreUpdate() override;
	bool CleanUp() override;
	


	/*COMMENT TO ERASE?*/
	/*KeyState GetKey(int id) const
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
	*/
public:
	const Uint8* keyboard = NULL;
	Uint8* mouse_buttons = NULL;

	Punt mouse_position;
	Punt mouse;

	char* dropped_filedir;

	/* COMMENT TO ERASE??*/
	//KeyState* keyboard = nullptr;
	//KeyState mouse_buttons[MAX_MOUSE_BUTTONS];
	//KeyState player_controll[MAX_BUTTONS];

	//SDL_GameController *controller = nullptr;

	int mouseWheel = 0;
	int mouse_x = 0;
	int mouse_y = 0;
	int mouse_z = 0;

	int mouse_x_motion = 0;
	int mouse_y_motion = 0;

	bool move_up = false;
	bool move_left = false;
	bool move_right = false;
	bool stop = false;

private:
	//KeyState * keyboard;
	//const Uint8* keyboard = NULL;
};