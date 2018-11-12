#ifndef __ModuleEditor_h__
#define __ModuleEditor_h__

#include <vector>

#include "Module.h"
#include "Globals.h"

#include "imgui.h"
#include "examples/imgui_impl_sdl.h"

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init() override;
	bool CleanUp() override;

	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	
	void AddLog(const char* fmt, ...);
	void Clear();

public:
	const char* glsl_version = "#version 130";
	
	bool showConfiguration = false;
	bool showAbout = false;
	bool showHardware = false;
	bool showConsole = true;
	bool ScrollToBottom;

	int currentItemSelected = 1;

	std::vector<float> fps_log;
	
	ImGuiTextBuffer Buf;
	ImGuiIO io;
};

#endif // __ModuleEditor_h__