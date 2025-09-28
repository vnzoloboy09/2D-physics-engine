#pragma once

#include "Vector2D.h"

namespace Eflat {

	class Transform {
	public:
		Transform(Vector2D position, float angle);
		Transform(float x, float y, float angle);
		Transform();
		~Transform();

	public:
		const float positionX;
		const float positionY;
		const float sin;
		const float cos;
	};

}

