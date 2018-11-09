#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleWindow.h"

#include "imgui.h"
#include "examples/imgui_impl_sdl.h"

//#define MAX_KEYS 256

ModuleInput::ModuleInput()
{
	//keyboard = new KeyState[MAX_KEYS]; COMMENT
	//memset(keyboard, KEY_IDLE, sizeof(KeyState) * MAX_KEYS);
}

// Destructor
ModuleInput::~ModuleInput()
{
	delete[] keyboard;
	delete[] mouse_buttons;
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);
	//SDL_Init; // COMMENT (SDL_INIT_GAMECONTROLLER);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	
	mouse_buttons = new Uint8[10]; // COMMENT

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();
	//Uint8 pad_buttons[MAX_BUTTONS]; COMMENT
	keyboard = SDL_GetKeyboardState(NULL);
	Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
	
	bool done = false;
	
	static SDL_Event event;

	// Keyboard
	keyboard = SDL_GetKeyboardState(NULL);

	if (keyboard[SDL_SCANCODE_ESCAPE]) {
		return UPDATE_STOP;
	}

	/*for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}*/

	// Mouse
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			mouse_buttons[event.button.button - 1] = KEY_DOWN;
			break;

		case SDL_MOUSEBUTTONUP:
			mouse_buttons[event.button.button - 1] = KEY_UP;
			break;

		case SDL_MOUSEWHEEL:
			mouseWheel = event.wheel.y;
			break;

		case SDL_MOUSEMOTION:
			mouse.x = event.motion.xrel;
			mouse.y = event.motion.yrel;

			mouse_position.x = event.motion.x;
			mouse_position.y = event.motion.y;
			break;

		case (SDL_DROPFILE):      // In case if dropped file
			dropped_filedir = event.drop.file;
			SDL_free(dropped_filedir);    // Free dropped_filedir memory
			//App->modelLoader->LoadNewModel(dropped_filedir);

			break;

		case SDL_QUIT:
			done = true;
			break;

		case SDL_WINDOWEVENT:
		{
			if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				//App->renderer->WindowResized(event.window.data1, event.window.data2);
				done = false; // COMMENT TO BE ERASED
			else if (event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(App->window->window))
				done = true;

			break;
		}
		}
	}

	// COMMENT TRY TO MODIFIE
	/*if (done || keyboard[SDL_SCANCODE_ESCAPE] == KEY_UP)
	{
		return UPDATE_STOP;
	}*/

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
