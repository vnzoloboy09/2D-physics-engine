#pragma once

#include "Entity/Entity.h"

namespace Eflat {

	class World
	{
	public:
		World();
		~World();

		void Step(float dt);

		void BroadPhase();
		void NarrowPhase();

		void AddEntity(const RigidBody& body, const Color& color);
		void AddEntity(const RigidBody& body);

		void RemoveEntity(const Entity& entity);

		bool AddCircle(Vector2D position, float radius, float density, bool IsStatic, float restitution);
		bool AddBox(Vector2D position, float width, float height, float density, bool IsStatic, float restitution);

		inline std::vector<Entity>& GetEntityList() { return m_Entities; }
		inline size_t GetNumEntities() const { return m_Entities.size(); }

		Color GetRandomColor();

	private:
		std::vector<Entity> m_Entities;

		std::vector<std::pair<int, int>> m_ContactPair;

		Vector2D m_Gravity = { 0.0f, 9.81f };

		const float MIN_BODY_SIZE = 0.01f * 0.01f;
		const float MAX_BODY_SIZE = 64.0f * 64.0f;

		const float MIN_DENSITY = 0.5f;
		const float MAX_DENSITY = 21.4f;

		const int MIN_ITERATIONS = 1;
		const int MAX_ITERATIONS = 128;
	};

}

