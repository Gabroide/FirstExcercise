#ifndef _CAMERA_MOVE_H
#define _CAMERA_MOVE_H

#include "Behaviour.h"

class CameraMove : public Behaviour
{
public:
	CameraMove(Object* object) : Behaviour(object) {}
	
	void Update();

	int cameraSpeed;
};

#endif // !_CAMERA_MOVE_H

