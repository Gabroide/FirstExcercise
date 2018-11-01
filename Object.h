#pragma once

#include <list>
#include <vector>

#include "Math/float3.h"
#include "Math/float4x4.h"

class Behaviour;

class Object
{
public:
	Object();
	virtual ~Object();

	virtual void Start();
	virtual void Update();
	virtual void CleanUp();

	virtual void AddVertex(float x, float y, float z, float uv0, float uv1);
	virtual std::vector<float>* GetVertices();
	virtual math::float4x4 RotationMatrix();
	virtual math::float4x4 ModelMatrix();

	std::list<std::vector<float>> vertices;
	math::float3 position = math::float3::zero;
	math::float3 rotation = math::float3::zero;
	math::float3 scale = math::float3::one;

	std::list<Behaviour*> behaviours;
};

