#include "ModuleRender.h"

#include "Application.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include"ModuleCamera.h"

#include <SDL.h>
#include <GL/glew.h>

//#include "MathGeoLib.h"
//#include "ModueModelLoader" COMMENT
//#include "ModuleProgram" COMMENT

ModuleRender::ModuleRender()
{
}

// Destructor
ModuleRender::~ModuleRender()
{
}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	context = SDL_GL_CreateContext(App->window->window);

	glewInit();

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_TEXTURE_2D);

	glClearDepth(1.0f);
	glClearColor(0.3f, 0.3f, 0.3f, 1.f);

    int width, height;
    SDL_GetWindowSize(App->window->window, &width, &height);
    glViewport(0, 0, width, height);

	//model = math::float4x4::identity; COMMENT
	
	return true;
}

update_status ModuleRender::PreUpdate()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	//glUseProgram(App->shader->program); COMMENT

	//glUniformMatrix4fv(glGetUniformLocation(App->shader->program,
	//	"model"), 1, GL_TRUE, &model[0][0]); COMMENT
	//glUniformMatrix4fv(glGetUniformLocation(App->shader->program,
	//	"view"), 1, GL_TRUE, &App->camera->view[0][0]); COMMENT
	//glUniformMatrix4fv(glGetUniformLocation(App->shader->program,
	//	"proj"), 1, GL_TRUE, &App->camera->projection[0][0]); COMMENT
	/* COMMENT
	for (int i = 0; i < App->modelLoader->scene->mNumMeshes; ++i) {
	*/

		/*unsigned vboActual = App->modelLoader->vbos[i];
		unsigned numVerticesActual = App->modelLoader->numVerticesMesh[i];
		unsigned numIndexesActual = App->modelLoader->numIndexesMesh[i];
*/
		/* COMMENT
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, App->modelLoader->vbos[i]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * App->modelLoader->numVerticesMesh[i]));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, App->modelLoader->ibos[i]);
		glDrawElements(GL_TRIANGLES, App->modelLoader->numIndexesMesh[i], GL_UNSIGNED_INT, nullptr);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

	}
	*/
	// glUseProgram(0); COMMENT

	/*
	glLineWidth(1.0f);

	glBegin(GL_LINES);
	float d = 200.f;

	for (float i = -d; i <= d; i += 1.0f) {
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}
	glEnd();*/

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window

	return true;
}

void ModuleRender::WindowResized(unsigned width, unsigned height)
{
    glViewport(0, 0, width, height); 
}