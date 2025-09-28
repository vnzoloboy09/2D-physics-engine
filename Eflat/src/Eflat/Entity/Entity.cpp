#include "efpch.h"
#include "Entity.h"

namespace Eflat {

	uint32_t Entity::s_NextID = 1;

	Entity::Entity(const RigidBody& body)
		: m_Body(body), m_Color( {0, 0, 0 ,255} ), m_ID(s_NextID++)
	{}

	Entity::Entity(const RigidBody& body, const Color& color)
		: m_Body(body), m_Color(color), m_ID(s_NextID++)
	{}

	Entity::~Entity()
	{ }

	void Entity::Update(float dt)
	{
		m_Body.Integrate(dt);
	}

	void Entity::SetPosition(const Vector2D& pos)
	{
		m_Body.MoveTo(pos);
	}

	void Entity::ApplyForce(const Vector2D& force)
	{
		m_Body.AddForce(force);
	}

	void Entity::ApplyTorque(const float& torque)
	{
		m_Body.AddTorque(torque);
	}

	bool Entity::operator==(const Entity& other) const
	{
		return m_ID == other.GetID();
	}

}
