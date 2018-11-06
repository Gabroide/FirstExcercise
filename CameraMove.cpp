#include "CameraMove.h"

#include "Application.h"
#include "ModuleInput.h"
#include "Object.h"

#include "SDL.h"
#include "MathGeoLib.h"

void CameraMove::Update()
{
	//LOG("EDITOR CAMERA MOVE UPDATE")
	if (App->input->GetKey(SDL_SCANCODE_UP) == KeyState::KEY_REPEAT) 
	{
		object->position.y += 0.1f*cameraSpeed; // Moving UP
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KeyState::KEY_REPEAT)
	{
		object->position.y -= 0.1f*cameraSpeed; // Moving DOWN
	}


	if (App->input->GetKey(SDL_SCANCODE_Z) == KeyState::KEY_REPEAT)
	{ // Zoom IN
		math::float4x4 model = object->RotationMatrix();
		object->position -= 0.1f*cameraSpeed*(model * math::float4(0.0f,0.0f,1.0f,1.0f)).Float3Part();
	}

	if (App->input->GetKey(SDL_SCANCODE_C) == KeyState::KEY_REPEAT)
	{ // Zoom OUT
		math::float4x4 model = object->RotationMatrix();
		object->position += 0.1f*cameraSpeed*(model * math::float4(0.0f, 0.0f, 1.0f, 1.0f)).Float3Part();
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KeyState::KEY_REPEAT)
	{ // Move RIGHT
		math::float4x4 model = object->RotationMatrix();
		object->position -= 0.1f*cameraSpeed*(model * math::float4(1.0f, 0.0f, 0.0f, 1.0f)).Float3Part();
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::KEY_REPEAT)
	{ // Move LEFT
		math::float4x4 model = object->RotationMatrix();
		object->position += 0.1f*cameraSpeed*(model * math::float4(1.0f, 0.0f, 0.0f, 1.0f)).Float3Part();
	}
	
	// Rotation
	if (App->input->GetKey(SDL_SCANCODE_Q) == KeyState::KEY_REPEAT)
	{ // y-axis
		math::float4x4 model = object->RotationMatrix().Inverted();
		object->rotation.y += 0.5f*cameraSpeed;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_REPEAT)
	{ // y-axis
		math::float4x4 model = object->RotationMatrix().Inverted();
		object->rotation.y -= 0.5f*cameraSpeed;
	}

	if (App->input->GetKey(SDL_SCANCODE_E) == KeyState::KEY_REPEAT)
	{ // x-axis
		object->rotation.x += 0.5f*cameraSpeed;
	}

	if (App->input->GetKey(SDL_SCANCODE_R) == KeyState::KEY_REPEAT)
	{ // x-axis
		object->rotation.x -= 0.5f*cameraSpeed;
	}

	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KeyState::KEY_REPEAT)
	{
		cameraSpeed = cameraSpeed * 2;
	}
	else
	{
		cameraSpeed = 2;
	}
}