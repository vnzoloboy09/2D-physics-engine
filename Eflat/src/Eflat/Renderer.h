#pragma once

#include "raylib.h"
#include "Math/Vector2D.h"
#include "Entity/Entity.h"

namespace Eflat {

	class Renderer
	{
	public:
		static void DrawCircleFill(const Vector2D position, const float radius, const Color color);
		static void DrawPolygonOutline(const std::vector<Vector2>& vertices, const Color color);
		static void DrawCircleOutline(const Vector2D position, const float radius, const Color color);
		static void DrawCircleFull(const Vector2D position, const float radius, const Color fillColor, const Color outlineColor);
		static void DrawBoxFill(const Vector2D& position, const float& width, const float& height, const float& angle, const Color& fillColor);
		static void DrawBoxOutline(const Vector2D& position, const float& width, const float& height, const Color& outlineColor);
		static void DrawBoxFull(const Vector2D& position, const float& width, const float& height,
			const float& angle, const Color& fillColor, const Color& outlineColor);

		static void Render(const AABB& aabb);

		static void Render(Entity& entity);
	};


}


