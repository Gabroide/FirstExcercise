#ifndef _MODULE_CAMERA_H
#define _MODULE_CAMERA_H

#include "Module.h"
#include "ModuleInput.h"

#include "Math/float3.h"
#include "Math/float3x3.h"
#include "Math/float4x4.h"
#include "Geometry/Frustum.h"

//#include "Behaviour.h"

class ModuleCamera : 
	public Module //Behaviour
{
public:
	ModuleCamera();
	~ModuleCamera();

	//ModuleCamera(Object* object) : Behaviour(object) {}
	//void Update();

	bool Init() override;
	bool CleanUp() override;

	update_status Update() override;

	void UpdateFrustum();

	void LookAt(math::float3& target);
	void FocusModel();

public:
	
	float distCamVrp = 1.0f; // COMMENT
	float movSpeed = 0.0f; // COMMENT
	float speedMov = 1.0f; // COMMENT
	//float speed2 = 0.0f; // COMMENT
	float rotSpeed = 0.00015f; // COMMENT


	bool rightButton = false;

	Punt lastPos; //lastMouse; // COMMENT
	Punt actualPos; //actualMouse; // COMMENT
	Punt calcNewPos;

	// Movement Vectors
	math::float3 newPos = math::float3(0, 1, 1); ;
	math::float3 up = math::float3(0, 1, 0);
	math::float3 forward = math::float3(0, 0, -1);
	math::float3 side;

	// Axis Vectors
	math::float3 axiX = math::float3(1, 0, 0);;
	math::float3 axiY = math::float3(0, 1, 0);;
	math::float3 axiZ = math::float3(0, 0, 1);;

	// Matrix
	Frustum frustum;
	math::float4x4 view;
	math::float4x4 projection;

private:

	float aspect = 0.0f;

	bool cameraChanged = false;


	float3 dir; // = (0.0f, 0.0f, 0.0f); COMMENT

	float3x3 rot;
};

#endif // !_CAMERA_MOVE_H

