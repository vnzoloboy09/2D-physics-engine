#include "efpch.h"
#include "AABB.h"

namespace Eflat {


	AABB::AABB()
		: min({ 0.0f, 0.0f }), max({ 0.0f, 0.0f })
	{

	}

	AABB::AABB(const Vector2D& _min, const Vector2D& _max)
		: min(_min), max(_max)
	{

	}

	AABB::AABB(float minX, float minY, float maxX, float maxY)
		: min({ minX, minY }), max({ maxX, maxY })
	{

	}

	AABB::~AABB()
	{

	}

}