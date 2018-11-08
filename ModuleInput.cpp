#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleWindow.h"

#include "imgui.h"
#include "examples/imgui_impl_sdl.h"

#define MAX_KEYS 256

ModuleInput::ModuleInput()
{
	keyboard = new KeyState[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KeyState) * MAX_KEYS);
}

// Destructor
ModuleInput::~ModuleInput()
{
	delete[](keyboard);
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	//SDL_Init(0); COMMENT
	SDL_Init(SDL_INIT_GAMECONTROLLER);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	
	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();
	Uint8 pad_buttons[MAX_BUTTONS];
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
	bool done = false;
	SDL_Event event;

	
	// Keyboard
	for (int i = 0; i < MAX_KEYS; ++i)
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
	}

	
	while (SDL_PollEvent(&event))
	{
		// App->gui->handleInput(&event); COMMENT
		switch (event.type)
		{
		case SDL_CONTROLLERBUTTONDOWN:
			move_up = true;
			break;

		case SDL_MOUSEWHEEL:
			//if (!App->gui->isMouseOnGUI())
				//mouse_z = event.wheel.y;
			break;

		case SDL_MOUSEMOTION:
			mouse_x = event.motion.x / SCREEN_SIZE;
			mouse_y = event.motion.y / SCREEN_SIZE;

			mouse_x_motion = event.motion.xrel / SCREEN_SIZE;
			mouse_y_motion = event.motion.yrel / SCREEN_SIZE;
			break;

		case SDL_QUIT:
			done = true;
			//return UpdateState::Update_End;
			break;

		case SDL_WINDOWEVENT:
		{
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				//App->window->OnResize(event.window.data1, event.window.data2);
				//App->renderer3D->OnResize(event.window.data1, event.window.data2);
			}

			else if (event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(App->window->window))
				done = true;
			break;
		}

		case (SDL_DROPFILE):
			//App->fileSystem->manageDroppedFiles(event.drop.file);
			break;
		}
	}

	if (done || keyboard[SDL_SCANCODE_ESCAPE] == KEY_UP)
	{
		return UPDATE_STOP;
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
