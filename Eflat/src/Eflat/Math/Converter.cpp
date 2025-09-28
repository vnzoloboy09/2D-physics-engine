#include "efpch.h"
#include "Converter.h"

namespace Eflat {

	Vector2 Converter::ToVector2(const Vector2D& vec)
	{
		return { vec.x, vec.y };
	}

	Vector2D Converter::ToVector2D(const Vector2& vec)
	{
		return { vec.x, vec.y };
	}

	std::vector<Vector2> Converter::ToVector2List(const std::vector<Vector2D>& flatVertices)
	{
		std::vector<Vector2> result(flatVertices.size());
		for (int i = 0; i < flatVertices.size(); i++) {
			result[i] = { flatVertices[i].x, flatVertices[i].y };
		}
		return result;
	}
}