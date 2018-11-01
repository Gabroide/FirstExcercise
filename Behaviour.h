#ifndef _BEHAVIOUR_H
#define _BEHAVIOUR_H

#include "Globals.h"

class Object;

class Behaviour
{
public:
	Behaviour(Object* object) : object(object) {}
	virtual ~Behaviour() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void CleanUp() {}

	Object* object;
};

#endif
