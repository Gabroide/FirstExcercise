#ifndef __Globals_h__
#define __Globals_h__

#include <stdio.h>

#include <windows.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 640
#define SCREEN_SIZE 1
#define FULLSCREEN false
#define RESIZABLE true
#define VSYNC true
#define TITLE "My first Engine"
#define FRAME_VALUES 10

#endif // __Globals_h__