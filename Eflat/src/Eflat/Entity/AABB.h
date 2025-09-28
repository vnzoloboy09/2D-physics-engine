#pragma once

#include "Eflat/Math/Vector2D.h"

namespace Eflat {

	class AABB
	{
	public:
		AABB();
		AABB(const Vector2D& min, const Vector2D& max);
		AABB(float minX, float minY, float maxX, float maxY);

		~AABB();

	public:
		Vector2D min;
		Vector2D max;
	};

}



