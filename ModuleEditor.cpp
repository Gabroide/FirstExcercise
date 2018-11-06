#include "ModuleEditor.h"

#include <stdio.h>

#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"

#include <SDL.h>
#include <GL/glew.h>

#include <imgui.h>
#include "examples/imgui_impl_sdl.h"
#include "examples/imgui_impl_opengl3.h"

//#include "imgui.h" COMMENT TO BE ERASED

#define GLSL_VERSION "#version 130"
//#define GRID_LENGTH 100 COMMENT
//#define GIZMO_LENGTH 0.5F COMMENT

/* CHAMGE COLORS */
#define DISABLEDTEXT_COLOR ImVec4(0.7F, 0.7F, 0.7F, 1.0F)
#define DISABLED_COLOR ImVec4(0.5F, 0.5F, 0.5F, 1.0F)
#define DISABLED_HIGHLIGHT_COLOR ImVec4(0.6F, 0.6F, 0.6F, 1.0F)
#define NONE_COLOR ImVec4(0.0F, 1.0F, 0.0F, 1.0F)
#define DEBUG_COLOR ImVec4(0.0F, 1.0F, 1.0F, 1.0F)
#define INFO_COLOR ImVec4(1.0F, 1.0F, 1.0F, 1.0F)
#define WARNING_COLOR ImVec4(1.0F, 1.0F, 0.0F, 1.0F)
#define ERROR_COLOR ImVec4(1.0F, 0.0F, 0.0F, 1.0F)

ModuleEditor::ModuleEditor()
{
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init() 
{
	IMGUI_CHECKVERSION();

	// Window setup
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);

	// Setting vars
	logMSIterator = 0;
	logFPSIterator = 0;
	fps_log = new float[50];
	ms_log = new float[50];
	lastFrame = SDL_GetTicks();
	lastTime = SDL_GetTicks();
	console.AddLog("Model geometry:\n");

	/* COMENT TO BE ERASED
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	const char* glsl_version = "#version 130";
	SDL_GLContext gl_context = SDL_GL_CreateContext(App->window->window);
	
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, gl_context);
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImGui::StyleColorsDark();
	*/
	return true;
}

void ModuleEditor::updateFramerates() {
	
	float timeElapsed = SDL_GetTicks() - lastTime;
	
	// Calculating FPS
	lastTime = SDL_GetTicks(); // COMMENT?
	fps_log[logFPSIterator] = 1000 / timeElapsed;
	
	++logFPSIterator;
	
	if (logFPSIterator > 49) logFPSIterator = 0;
	
	//ms calculation
	ms_log[logMSIterator] = timeElapsed;
	lastFrame = SDL_GetTicks(); // COMMENT?
	
	//iterator increase
	++logMSIterator;
	
	if (logMSIterator > 49)
	{
		logMSIterator = 0;
	}
}

update_status ModuleEditor::PreUpdate() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();
	return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update() {
	bool show_demo_window = false;
	if (show_demo_window)ImGui::ShowDemoWindow(&show_demo_window);

	else {
		// Menu
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				ImGui::Text("Menu");
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Help"))
			{
				if (ImGui::Button("Documentation")) {
					ShellExecute(NULL, "open", "https://github.com/RogerNogue/MVJ_Engine_base/wiki", NULL, NULL, SW_SHOWNORMAL);
				}
				if (ImGui::Button("Download latest")) {
					ShellExecute(NULL, "open", "https://github.com/RogerNogue/MVJ_Engine_base/releases", NULL, NULL, SW_SHOWNORMAL);
				}
				if (ImGui::Button("Report a bug")) {
					ShellExecute(NULL, "open", "https://github.com/RogerNogue/MVJ_Engine_base/issues", NULL, NULL, SW_SHOWNORMAL);
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Exit")) {
				return UPDATE_STOP;
			}
			ImGui::EndMainMenuBar();
		}

		ImGui::Spacing();
		if (ImGui::CollapsingHeader("Configuration"))
		{
			ImGui::Text("Application Time = %d", SDL_GetTicks() / 1000);
			char* title = new char[50];
			updateFramerates();
			sprintf_s(title, 50, "Framerate %.1f", fps_log[logFPSIterator]);
			ImGui::PlotHistogram("", fps_log, 50, 0, title, 0.0f, 100.0f, ImVec2(350, 100));
			sprintf_s(title, 50, "Milliseconds %.1f", ms_log[logMSIterator]);
			ImGui::PlotHistogram("", ms_log, 50, 0, title, 0.0f, 100.0f, ImVec2(350, 100));
		}

		/*
		ImGui::Spacing();
		if (ImGui::CollapsingHeader("About"))
		{
			ImGui::BulletText("Engine name: DESPACITO 2");
			ImGui::Text("Description");
			ImGui::BulletText("DESPACITO 2 allows you to create AAA-quality games with little to none effort.");
			ImGui::Text("Authors");
			ImGui::BulletText("Roger Nogue Ballbe.");
			ImGui::Text("Libraries");
			ImGui::BulletText("SDL.");
			ImGui::BulletText("IMGUI.");
			ImGui::BulletText("GLEW.");
			ImGui::Text("Licenses");
			if (ImGui::Button("SDL")) {
				ShellExecute(NULL, "open", "https://www.libsdl.org/license.php", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::Button("IMGUI")) {
				ShellExecute(NULL, "open", "https://github.com/ocornut/imgui/blob/master/LICENSE.txt", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::Button("GLEW")) {
				ShellExecute(NULL, "open", "https://www.opengl.org/about/#11", NULL, NULL, SW_SHOWNORMAL);
			}
			ImGui::Separator();
		}

		//going over all the menus
		//App info
		if (ImGui::CollapsingHeader("Configuration"))
		{
			ImGui::Text("Application Time = %d", SDL_GetTicks()/1000);
			char* title = new char[50];
			updateFramerates();
			sprintf_s(title, 50, "Framerate %.1f", fps_log[logFPSIterator]);
			ImGui::PlotHistogram("", fps_log, 50, 0, title, 0.0f, 100.0f, ImVec2(350, 100));
			sprintf_s(title, 50, "Milliseconds %.1f", ms_log[logMSIterator]);
			ImGui::PlotHistogram("", ms_log, 50, 0, title, 0.0f, 100.0f, ImVec2(350, 100));
		}
		//global variables
		if (ImGui::CollapsingHeader("Globals"))
		{
			ImGui::Text("Screen Width = %d", SCREEN_WIDTH);
			ImGui::Text("Screen Height = %d", SCREEN_HEIGHT);
			ImGui::Text("Fullscreen = %d", FULLSCREEN);
			ImGui::Text("VSYNC = %d", VSYNC);
			ImGui::Text("GLSL version = %s", GLSL_VERSION);
		}
		//module window
		if (ImGui::CollapsingHeader("Window"))
		{
			ImGui::Text("Not much to be shown about this module yet.");
		}
		//module menu
		if (ImGui::CollapsingHeader("Menu"))
		{
			ImGui::Text("Not much to be shown about this module yet.");
		}
		//module render
		if (ImGui::CollapsingHeader("Render"))
		{
			ImGui::Text("Not much to be shown about this module yet.");
		}
		//module textures
		if (ImGui::CollapsingHeader("Textures"))
		{
			ImGui::Text("Not much to be shown about this module yet.");
		}
		//module input
		if (ImGui::CollapsingHeader("Input"))
		{
			ImGui::Text("Not much to be shown about this module yet.");
		}
		//module render exercise
		if (ImGui::CollapsingHeader("Camera"))
		{
			ImGui::Text("Cam declarations:");
			ImGui::BulletText("Camera position = ( %f, %f, %f )", App->camera->cam.x, App->camera->cam.y, App->camera->cam.z);
			ImGui::BulletText("VRP position = ( %f, %f, %f )", App->camera->vrp.x, App->camera->vrp.y, App->camera->vrp.z);
			ImGui::BulletText("Up directions = ( %f, %f, %f )", App->camera->up.x, App->camera->up.y, App->camera->up.z);
			ImGui::BulletText("Forward directions= ( %f, %f, %f )", App->camera->fwd.x, App->camera->fwd.y, App->camera->fwd.z);
			ImGui::BulletText("Side directions = ( %f, %f, %f )", App->camera->side.x, App->camera->side.y, App->camera->side.z);
			ImGui::BulletText("Distance between camera and VRP = %f", App->camera->distCamVrp);
		}
		//module program
		if (ImGui::CollapsingHeader("Program"))
		{
			ImGui::Text("Not much to be shown about this module yet.");
		}
		*/
	}
	console.Draw("Console");

	//ImGui::End();
	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	delete fps_log;
	delete ms_log;

	return true;
}
