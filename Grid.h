#ifndef __Grid_h__
#define __Grid_h__

#include "Module.h"
#include "Math/float4x4.h"

class Object;

class Grid : public Module
{
public:
	Grid();
	~Grid();

	bool            Init();
	update_status   Update();
	bool            CleanUp();

	static math::float4x4 LookAt(const Object &target, const Object &eye);

private:
	void LoadShaderProgram();
	char* LoadShaderData(const char* filename);
	math::float4x4 ProjectionMatrix();
	void DrawPlane();

	unsigned vbo = 0;
	unsigned program = 0;
	unsigned vao = 0;
	unsigned ibo = 0;
	unsigned int textureID = 0;

	Object* triangle;
	Object* camera;
};

#endif /* __Grid_h__ */
