#include "efpch.h"
#include "RigidBody.h"

#include "Eflat/Math/Transform.h"

namespace Eflat {

	RigidBody::RigidBody(RigidBodyData data, Vector2D position)
		: m_Data(data), m_Force({ 0.0f, 0.0f }), m_Torque(0.0f),
		m_Velocity({ 0.0f, 0.0f }), m_Angle(0.0f), m_AngularVelocity(0.0f),
		m_Position(position)
	{
		if (m_Data.shapeType == Box)
			m_Vertices = CreateBoxVertices(m_Data.width, m_Data.height);
		m_TransformVertices.resize(m_Vertices.size());
	}

	RigidBody::RigidBody()
		: m_Force({ 0.0f, 0.0f }), m_Torque(0.0f),
		m_Velocity({ 0.0f, 0.0f }), m_Angle(0.0f), m_AngularVelocity(0.0f),
		m_Position({ 0.0f, 0.0f })
	{}

	RigidBody::~RigidBody()
	{

	}

	void RigidBody::Integrate(float dt)
	{
		if (m_Data.isStatic) 
			return;

		m_Velocity += (m_Force * m_Data.invMass) * dt;
		m_Position += m_Velocity * dt;
		
		m_AngularVelocity += m_Torque * m_Data.invInertia * dt;
		m_Angle += m_AngularVelocity * dt;

		m_Force = { 0.0f, 0.0f };
		m_Torque = 0.0f;

		m_TransformUpdateRequired = true;
		m_AabbUpdateRequired = true;
	}

	void RigidBody::Move(const Vector2D& amout)
	{
		m_Position += amout;
		m_TransformUpdateRequired = true;
		m_AabbUpdateRequired = true;
	}

	void RigidBody::MoveTo(const Vector2D& position)
	{
		m_Position = position;
		m_TransformUpdateRequired = true;
		m_AabbUpdateRequired = true;
	}

	void RigidBody::SetVelocity(Vector2D velocity)
	{
		m_Velocity = velocity;
	}

	void RigidBody::AdjustVelocity(const Vector2D& amout)
	{
		m_Velocity += amout;
	}

	void RigidBody::SetAngularVelocity(float angVel)
	{
		m_AngularVelocity = angVel;
	}

	void RigidBody::AdjustAngularVelocity(float amout)
	{
		m_AngularVelocity += amout;
	}

	void RigidBody::Rotate(const float& amout)
	{
		m_Angle += amout;
		m_TransformUpdateRequired = true;
		m_AabbUpdateRequired = true;
	}

	void RigidBody::RotateTo(const float& angle)
	{
		m_Angle = angle;
		m_TransformUpdateRequired = true;
		m_AabbUpdateRequired = true;
	}

	void RigidBody::AddForce(const Vector2D& force)
	{
		m_Force += force;
	}

	void RigidBody::AddTorque(const float& torque)
	{
		m_Torque += torque;
	}

	std::vector<Vector2D>& RigidBody::GetTransformVertices()
	{
		if (m_TransformUpdateRequired)
		{
			Transform transform(m_Position, m_Angle);

			for (size_t i = 0; i < m_Vertices.size(); i++)
			{
				m_TransformVertices[i] = Vector2D::Vector2DTransform(m_Vertices[i], transform);
			}
		}
		m_TransformUpdateRequired = false;

		return m_TransformVertices;
	}

	std::vector<Vector2D> RigidBody::CreateBoxVertices(float width, float height) {
		float left = -width / 2.0f;
		float right = left + width;
		float bottom = height / 2.0f;
		float top = bottom - height;

		std::vector<Vector2D> vectices(4);
		vectices[0] = { left, top };
		vectices[1] = { right, top };
		vectices[2] = { right, bottom };
		vectices[3] = { left, bottom };

		return vectices;
	}

	AABB& RigidBody::GetAABB()
	{
		if (m_AabbUpdateRequired) {
			float minX = FLT_MAX;
			float minY = FLT_MAX;
			float maxX = -FLT_MAX;
			float maxY = -FLT_MAX;

			if (m_Data.shapeType == Box) {
				std::vector<Vector2D>& vertices = GetTransformVertices();
				for (auto& v : vertices) {
					if (v.x < minX) minX = v.x;
					if (v.x > maxX) maxX = v.x;
					if (v.y < minY) minY = v.y;
					if (v.y > maxY) maxY = v.y;
				}
			}
			else if (m_Data.shapeType == Circle) {
				minX = m_Position.x - m_Data.radius;
				minY = m_Position.y - m_Data.radius;
				maxX = m_Position.x + m_Data.radius;
				maxY = m_Position.y + m_Data.radius;
			}
			else {
				__debugbreak();
			}
			m_AABB = AABB(minX, minY, maxX, maxY);
		}

		m_AabbUpdateRequired = false;
		return m_AABB;
	}

}