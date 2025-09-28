#include "efpch.h"
#include "Renderer.h"

#include "Math/Converter.h"
#include "Math/Transform.h"

namespace Eflat {

	void Renderer::DrawBoxFill(const Vector2D& position, const float& width, const float& height, const float& angle, const Color& fillColor) {
		Rectangle rect = { position.x, position.y, width, height };
		DrawRectanglePro(rect, { width / 2.0f, height / 2.0f }, angle * 180.0f / PI, fillColor);
	}

	void Renderer::DrawPolygonOutline(const std::vector<Vector2>& vertices, const Color color) {
		for (size_t i = 0; i < vertices.size(); ++i) {
			Vector2 v1 = vertices[i];
			Vector2 v2 = vertices[(i + 1) % vertices.size()];
			DrawLineV(v1, v2, color);
		}
	}

	void Renderer::DrawBoxOutline(const Vector2D& position, const float& width, const float& height, const Color& outlineColor) {
		DrawRectangleLinesEx({ position.x - width / 2.0f, position.y - height / 2.0f, width, height }, 0.1f, outlineColor);
	}

	void Renderer::DrawBoxFull(const Vector2D& position, const float& width, const float& height,
		const float& angle, const Color& fillColor, const Color& outlineColor) {
		DrawBoxFill(position, width, height, angle, fillColor);
		DrawBoxOutline(position, width, height, outlineColor);
	}

	void Renderer::DrawCircleFill(const Vector2D position, const float radius, const Color color) {
		DrawCircleV(Converter::ToVector2(position), radius, color);
	}

	void Renderer::DrawCircleOutline(const Vector2D position, const float radius, const Color color) {
		DrawCircleLinesV(Converter::ToVector2(position), radius, color);
	}

	void Renderer::DrawCircleFull(const Vector2D position, const float radius, const Color fillColor, const Color outlineColor) {
		DrawCircleFill(position, radius, fillColor);
		DrawCircleOutline(position, radius, outlineColor);
	}

	void Renderer::Render(Entity& entity)
	{
		const RigidBody& body = entity.GetBody();
		const RigidBodyData& bodyData = body.GetData();

		if (bodyData.shapeType == Circle)
		{
			Vector2D va = { 0.0f, 0.0f };
			Vector2D vb = { body.GetData().radius, 0.0f};
			Transform transform(body.GetPosition(), body.GetAngle());
			va = Vector2D::Vector2DTransform(va, transform);
			vb = Vector2D::Vector2DTransform(vb, transform);

			Renderer::DrawCircleFull(body.GetPosition(), bodyData.radius,
				entity.GetColor(), entity.GetOutlineColor());
			DrawLineEx(Converter::ToVector2(va), Converter::ToVector2(vb), 0.1f, RED);

		}
		else if (bodyData.shapeType == Box)
		{
			Renderer::DrawBoxFill(body.GetPosition(), bodyData.width, bodyData.height,
				body.GetAngle(), entity.GetColor());
			Renderer::DrawPolygonOutline(Converter::ToVector2List(entity.GetBody().GetTransformVertices()), entity.GetOutlineColor());
		}
		else {
			TraceLog(LOG_ERROR, "Type not found!");
		}
		//Render(entity.GetBody().GetAABB());
	}

	void Renderer::Render(const AABB& aabb)
	{
		Rectangle rec = { aabb.min.x, aabb.min.y, aabb.max.x - aabb.min.x, aabb.max.y - aabb.min.y };
		DrawRectangleLinesEx(rec, 0.1f, BLUE);
	}
}

