#ifndef _MODULE_EDITOR_H
#define _MODULE_EDITOR_H

#include "Module.h"

class ModuleEditor : public Module
{
	bool Init();
	update_status PostUpdate();
	bool CleanUp();
};


#endif // !_MODULE_EDITOR_H

