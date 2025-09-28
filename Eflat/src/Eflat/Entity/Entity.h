#pragma once

#include "RigidBody.h"
#include "raylib.h"

namespace Eflat {

	class Entity
	{
	public:
		Entity(const RigidBody& body);
		Entity(const RigidBody& body, const Color& color);
		~Entity();

		void Update(float dt);
		void Render();

		inline RigidBody& GetBody() { return m_Body; }
		inline Color GetColor() const { return m_Color; }
		inline Color GetOutlineColor() const { return m_OulineColor; }
		inline void SetColor(const Color& color) { m_Color = color; }
		inline void SetOutlineColor(const Color& color) { m_OulineColor = color; }
		inline uint32_t GetID() const { return m_ID; }

		void SetPosition(const Vector2D& pos);
		void ApplyForce(const Vector2D& force);
		void ApplyTorque(const float& torque);

		bool operator==(const Entity& other) const;
		Entity(const Entity&) = default;
		Entity& operator=(const Entity&) = default;

	private:
		RigidBody m_Body;
		Color m_Color;
		Color m_OulineColor = BLACK;
		uint32_t m_ID;

		static uint32_t s_NextID;
	};

}


