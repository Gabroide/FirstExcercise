#ifndef _MODULE_EDITOR_H
#define _MODULE_EDITOR_H

#include "Module.h"
#include "Globals.h"

#include <imgui.h>

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init();

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

	bool CleanUp();

	struct AppLog
	{
		ImGuiTextBuffer imBuf;
		bool ScrollToBottom;

		void Clear() 
		{ 
			imBuf.clear(); 
		}

		void AddLog(const char* fmt, ...) //IM_PRINTFARGS(2) COMMENT
		{
			va_list args;
			va_start(args, fmt);
			imBuf.appendf(fmt, args);
			va_end(args);
			ScrollToBottom = true;
		}

		void Draw(const char* title, bool* p_opened = NULL)
		{
			ImGui::Begin(title, p_opened);
			ImGui::TextUnformatted(imBuf.begin());

			if (ScrollToBottom)
			{
				ImGui::SetScrollHere(1.0f); // CHANGE
			}

			ScrollToBottom = false;
			ImGui::End();
		}
	};

	// Vars
	int frames;
	float lastFrame;
	float lastTime;
	int logMSIterator;
	int logFPSIterator;
	float* fps_log;
	float* ms_log;
	AppLog console;

private:
	void updateFramerates();
};

#endif // !_MODULE_EDITOR_H