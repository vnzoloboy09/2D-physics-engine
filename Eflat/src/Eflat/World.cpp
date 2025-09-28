#include "efpch.h"
#include "World.h"

#include "Eflat/Physics/Collision.h"

namespace Eflat {

	World::World()
	{

	}

	World::~World()
	{

	}

	void World::Step(float dt)
	{
		for (size_t it = 0; it < 20; it++)
		{
			m_ContactPair.clear();

			for (auto& entity : m_Entities)
			{
				entity.SetOutlineColor(BLACK);
				entity.ApplyForce(m_Gravity * entity.GetBody().GetData().mass);
				entity.Update(dt / 20);
			}

			if (GetNumEntities() > 1)
			{
				BroadPhase();
				NarrowPhase();
			}
		}
	}

	void World::BroadPhase()
	{
		for (size_t i = 0; i < m_Entities.size() - 1; i++)
		{
			RigidBody& bodyA = m_Entities[i].GetBody();

			for (size_t j = i + 1; j < m_Entities.size(); j++)
			{
				RigidBody& bodyB = m_Entities[j].GetBody();

				if (bodyA.GetData().isStatic && bodyB.GetData().isStatic)
					continue;

				if (!Collision::IntersectAABB(bodyA.GetAABB(), bodyB.GetAABB()))
					continue;

				m_ContactPair.emplace_back(i, j);
			}
		}
	}

	void World::NarrowPhase()
	{
		for (auto& pair : m_ContactPair)
		{
			Vector2D normal = { 0.0f, 0.0f };
			float depth = 0.0f;
			RigidBody& bodyA = m_Entities[pair.first].GetBody();
			RigidBody& bodyB = m_Entities[pair.second].GetBody();

			if (Collision::Collided(m_Entities[pair.first], m_Entities[pair.second], normal, depth))
			{
				Collision::SeparateBodies(bodyA, bodyB, normal * depth);

				Vector2D contact1, contact2;
				size_t contactCount;

				Collision::FindContactPoint(bodyA, bodyB, contact1, contact2, contactCount);
				Manifold contact(bodyA, bodyB, normal, depth, contact1, contact2, contactCount);
				Collision::ResolveCollision(contact);
			}
		}
	}

	void World::AddEntity(const RigidBody& body, const Color& color)
	{
		m_Entities.emplace_back(body, color);
	}

	void World::AddEntity(const RigidBody& body)
	{
		m_Entities.emplace_back(body);
	}

	void World::RemoveEntity(const Entity& entity)
	{
		m_Entities.erase(
			std::remove_if(m_Entities.begin(), m_Entities.end(),
				[&](const Entity& e) { return e == entity; }),
			m_Entities.end()
		);
	}

	bool World::AddCircle(Vector2D position, float radius, float density, bool IsStatic, float restitution)
	{
		float area = radius * radius * PI;

		float mass = 0.0f;
		float inertia = 0.0f;

		if (area < MIN_BODY_SIZE || area > MAX_BODY_SIZE ||
			density < MIN_DENSITY || density > MAX_DENSITY)
			return false;

		if (!IsStatic)
		{
			mass = area * density;
			inertia = (1.0f / 2.0f) * mass * radius * radius;
		}

		AddEntity(RigidBody(
			RigidBodyData(
				Circle, mass, density, restitution, area, 
				radius, 0.0f, 0.0f, IsStatic, inertia
			), 
		position), GetRandomColor() 
		);

		return true;
	}

	bool World::AddBox(Vector2D position, float width, float height, float density, bool IsStatic, float restitution)
	{
		float area = width * height;

		float mass = 0.0f;
		float inertia = 0.0f;

		if (area < MIN_BODY_SIZE || area > MAX_BODY_SIZE ||
			density < MIN_DENSITY || density > MAX_DENSITY)
			return false;

		if (!IsStatic) {
			mass = area * density;
			inertia = (1.0f / 12.0f) * mass * (width * width + height * height);
		}

		AddEntity(RigidBody(
			RigidBodyData(
				Box, mass, density, restitution, area,
				0.0f, width, height, IsStatic, inertia
			),
			position), GetRandomColor()
		);

		return true;
	}


	Color World::GetRandomColor()
	{
		return {
		(unsigned char)GetRandomValue(0, 255),  // Red
			(unsigned char)GetRandomValue(0, 255),  // Green
			(unsigned char)GetRandomValue(0, 255),  // Blue
			255                                     // Alpha (fully opaque)
		};
	}
}

