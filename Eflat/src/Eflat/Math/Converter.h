#pragma once

#include "raylib.h"
#include "Vector2D.h"

namespace Eflat {

	class Converter
	{
	public:
		static Vector2 ToVector2(const Vector2D& vec);
		static Vector2D ToVector2D(const Vector2& vec);
		static std::vector<Vector2> ToVector2List(const std::vector<Vector2D>& flatVertices);
	};

}

