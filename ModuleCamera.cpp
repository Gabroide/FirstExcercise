#include "ModuleCamera.h"

#include "Application.h"
#include "ModuleInput.h"
#include "Object.h"

#include "SDL.h"
#include "MathGeoLib.h"

bool  ModuleCamera::Init() 
{ 
	//cameraChanged = false;
	//speed1 = 0.1;
	//speed2 = speed1 * 3.5;
	//movementSpeed = speed1;
	//rotationSpeed = 0.0015;

	//camPos = math::float3(0, 1, 1); // COMMENT
	//distCamVrp = 1.0f; // COMMENT

	// Desplacement Vetors
	//forward = math::float3(0, 0, -1); // COMMENT
	//up = math::float3(0, 1, 0);

	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = newPos;
	frustum.front = forward.Normalized();
	frustum.up = up.Normalized();
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = math::pi / 4.0f;
	aspect = SCREEN_WIDTH / SCREEN_HEIGHT;
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov * 0.5f) *aspect);

	side = (frustum.WorldRight()).Normalized();

	//axiX = math::float3(1, 0, 0);
	//axiY = math::float3(0, 1, 0);
	//axiZ = math::float3(0, 0, 1);

	view = frustum.ViewMatrix();
	projection = frustum.ProjectionMatrix();

	//pressingRightMouse = false;
	lastPos = App->input->mouse_position;

	return true;
}

update_status ModuleCamera::Update()
{
	LOG("EDITOR CAMERA MOVE UPDATE");
	
		/* COMMENT
	if (App->input->GetKey(SDL_SCANCODE_UP) == KeyState::KEY_REPEAT) 
	{
		object->position.y += 0.1f; // Moving UP
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KeyState::KEY_REPEAT)
	{
		object->position.y -= 0.1f; // Moving DOWN
	}

	if (App->input->GetKey(SDL_SCANCODE_Z) == KeyState::KEY_REPEAT)
	{ // Zoom IN
		math::float4x4 model = object->RotationMatrix();
		object->position -= 0.1f*(model * math::float4(0.0f,0.0f,1.0f,1.0f)).Float3Part();
	}

	if (App->input->GetKey(SDL_SCANCODE_C) == KeyState::KEY_REPEAT)
	{ // Zoom OUT
		math::float4x4 model = object->RotationMatrix();
		object->position += 0.1f*(model * math::float4(0.0f, 0.0f, 1.0f, 1.0f)).Float3Part();
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KeyState::KEY_REPEAT)
	{ // Move RIGHT
		math::float4x4 model = object->RotationMatrix();
		object->position -= 0.1f*(model * math::float4(1.0f, 0.0f, 0.0f, 1.0f)).Float3Part();
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::KEY_REPEAT)
	{ // Move LEFT
		math::float4x4 model = object->RotationMatrix();
		object->position += 0.1f*(model * math::float4(1.0f, 0.0f, 0.0f, 1.0f)).Float3Part();
	}


	// Rotation
	if (App->input->GetKey(SDL_SCANCODE_Q) == KeyState::KEY_REPEAT)
	{ // y-axis
		math::float4x4 model = object->RotationMatrix().Inverted();
		object->rotation.y += 0.5f;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_REPEAT)
	{ // y-axis
		math::float4x4 model = object->RotationMatrix().Inverted();
		object->rotation.y -= 0.5f;
	}

	if (App->input->GetKey(SDL_SCANCODE_E) == KeyState::KEY_REPEAT)
	{ // x-axis
		object->rotation.x += 0.5f;
	}
	if()

	if (App->input->GetKey(SDL_SCANCODE_R) == KeyState::KEY_REPEAT)
	{ // x-axis
		object->rotation.x -= 0.5f;
	}*/

	// Mouse control
	if (App->input->mouse_buttons[SDL_BUTTON_RIGHT - 1] == KEY_DOWN)
	{
		if (App->input->keyboard[SDL_SCANCODE_E])
		{
			newPos += axiY * movSpeed;
			cameraChanged = true;
		}
		if (App->input->keyboard[SDL_SCANCODE_Q])
		{
			newPos -= axiY * movSpeed;
			cameraChanged = true;
		}
		if (App->input->keyboard[SDL_SCANCODE_W])
		{
			newPos += forward * movSpeed;
			cameraChanged = true;
		}
		if (App->input->keyboard[SDL_SCANCODE_S]) {
			newPos -= forward * movSpeed;
			cameraChanged = true;
		}
		if (App->input->keyboard[SDL_SCANCODE_A])
		{
			newPos -= side * movSpeed;
			cameraChanged = true;
		}
		if (App->input->keyboard[SDL_SCANCODE_D]) {
			newPos += side * movSpeed;
			cameraChanged = true;
		}

	if (App->input->keyboard[SDL_SCANCODE_LSHIFT]) 
	{
		movSpeed = speedMov * 2;
	}
	else
	{
		movSpeed = speedMov;
	}

	// Focus on Model
	if (App->input->keyboard[SDL_SCANCODE_F])
	{
		FocusModel();
	}

	//mouse rotation
	if (!rightButton) 
	{
		lastPos = App->input->mouse_position;
		rightButton = true;
	}
	else 
	{
		actualPos = App->input->mouse_position;
		calcNewPos = { actualPos.x - lastPos.x, actualPos.y - lastPos.y };

		Quat rot;

		if (calcNewPos.x != 0)
		{
			rot = Quat::RotateAxisAngle(axiY, -calcNewPos.x * rotSpeed);
			forward = (rot * forward).Normalized();
			side = (rot * side).Normalized();
			up = (rot * up).Normalized();
		}
		if (calcNewPos.y != 0)
		{
			rot = Quat::RotateAxisAngle(side, -calcNewPos.y * rotSpeed);
			forward = (rot * forward).Normalized();
			up = (side.Cross(forward)).Normalized();
		}

		lastPos = actualPos;
		cameraChanged = true;
	}
	}
	else 
	{
		rightButton = false;
	}

	if (cameraChanged) {
		UpdateFrustum();
		cameraChanged = false;
	}

	return UPDATE_CONTINUE;
}

void ModuleCamera::FocusModel() {
	newPos = 
	{
		App->modelLoader->boundingBox->CenterPoint().x,
		App->modelLoader->boundingBox->CenterPoint().y,
		App->modelLoader->boundingBox->CenterPoint().z + App->modelLoader->boundingBox->Diagonal().Length()
	};

	LookAt(App->modelLoader->boundingBox->CenterPoint());
	UpdateFrustum();
}

void ModuleCamera::LookAt(math::float3& target) {

	dir = (target - newPos).Normalized();
	rot = float3x3::LookAt(forward, dir, up, axiY);
	up = rot * up;
	forward = rot * forward;
	side = rot * side;
}

void ModuleCamera::UpdateFrustum() {
	frustum.pos = newPos;
	frustum.front = forward.Normalized();
	frustum.up = up.Normalized();

	view = frustum.ViewMatrix();
	projection = frustum.ProjectionMatrix();
 }

bool ModuleCamera::CleanUp()
{
	return true;
}

