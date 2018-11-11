#ifndef __ModuleTimer_h__
#define __ModuleTimer_h__

#include "SDL.h"

class Timer {
public:
	Timer()
	{
	}

	~Timer()
	{
	}

	void Start()
	{
		timeStart = SDL_GetTicks();
	}

	Uint32 Stop()
	{
		return SDL_GetTicks() - timeStart;
	}

	void StartPerformance()
	{
		performancetimeStart = SDL_GetPerformanceCounter();
	}

	Uint64 StopPerformance()
	{
		return SDL_GetPerformanceCounter() - performancetimeStart;
	}

public:
	Uint32 timeStart;
	Uint64 performancetimeStart;
};

#endif // __ModuleTimer_h__