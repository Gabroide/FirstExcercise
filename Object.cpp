#include "Object.h"

#include "MathGeoLib.h"
//#include "Behaviour.h"

#define DEG2RAD 0.0174532925f

Object::Object()
{
}


Object::~Object()
{
	for (std::list<Behaviour*>::iterator it = behaviours.begin(); it != behaviours.end(); ++it)
		delete(*it);
	behaviours.clear();
}

void Object::Start()
{
	/*for (std::list<Behaviour*>::iterator it = behaviours.begin(); it != behaviours.end(); ++it)
		(*it)->Start();*/
}

void Object::Update()
{
	/*for (std::list<Behaviour*>::iterator it = behaviours.begin(); it != behaviours.end(); ++it)
		(*it)->Update();
		*/
}

void Object::CleanUp()
{
	/*for (std::list<Behaviour*>::iterator it = behaviours.begin(); it != behaviours.end(); ++it)
		(*it)->CleanUp();*/
}

void Object::AddVertex(float x, float y, float z, float uv0, float uv1)
{
	std::vector<float> v = { x, y, z, uv0, uv1 };
	vertices.push_back(v);
}

std::vector<float>* Object::GetVertices()
{
	std::vector<float>* output = new std::vector<float>;

	for (std::list<std::vector<float>>::iterator it = vertices.begin(); it != vertices.end(); ++it)
	{
		output->insert(output->end(), it->begin(), it->end());
	}

	return output;
}

math::float4x4 Object::RotationMatrix()
{

	math::float4x4 rot = math::float4x4::identity; // RotX * RotY * RotZ

	float CX = cos(DEG2RAD * rotation.x); float SX = sin(DEG2RAD * rotation.x);
	float CY = cos(DEG2RAD * rotation.y); float SY = sin(DEG2RAD * rotation.y);
	float CZ = cos(DEG2RAD * rotation.z); float SZ = sin(DEG2RAD * rotation.z);

	rot[0][0] = CY * CZ;				rot[0][1] = -CY * SZ;				rot[0][2] = SY;
	rot[1][0] = CX * SZ + SX * SY*CZ;	rot[1][1] = CX * CZ - SX * SY*SZ;	rot[1][2] = -SX * CY;
	rot[2][0] = SX * SZ - CX * SY*CZ;	rot[2][1] = -CX * SY*SZ + SX * CZ;	rot[2][2] = CX * CY;

	return rot;
}

math::float4x4 Object::ModelMatrix()
{
	math::float4x4 rot = RotationMatrix();
	math::float4x4 scaleM = math::float4x4::identity;
	math::float4x4 translate = math::float4x4::identity;

	scaleM[0][0] = scale.x;				scaleM[1][1] = scale.y;				scaleM[2][2] = scale.z;
	translate[0][3] = position.x;		translate[1][3] = position.y;		translate[2][3] = position.z;

	return  translate * scaleM * rot;
}
