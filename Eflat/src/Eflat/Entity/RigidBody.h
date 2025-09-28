#pragma once

#include "RigidBodyData.h"
#include "Eflat/Math/Vector2D.h"
#include "AABB.h"

namespace Eflat {

	class RigidBody
	{
	public:
		RigidBody(RigidBodyData data, Vector2D position);
		RigidBody();

		~RigidBody();

		void Integrate(float dt);

		void Move(const Vector2D& amout);
		void MoveTo(const Vector2D& position);
		void SetVelocity(Vector2D velocity);
		void AdjustVelocity(const Vector2D& amout);
		void SetAngularVelocity(float angularVelocity);
		void AdjustAngularVelocity(float amout);
		void Rotate(const float& amout);
		void RotateTo(const float& angle);

		void AddForce(const Vector2D& force);
		void AddTorque(const float& m_Torque);

		inline RigidBodyData GetData() const { return m_Data; }
		
		inline Vector2D GetPosition() const { return m_Position; }
		inline Vector2D GetVelocity() const { return m_Velocity; }
		inline float GetAngle() const { return m_Angle; }
		inline float GetAngularVelocity() const { return m_AngularVelocity; }

		std::vector<Vector2D>& GetTransformVertices();

		std::vector<Vector2D> CreateBoxVertices(float width, float height);

		AABB& GetAABB();

	private:
		RigidBodyData m_Data;
		
		AABB m_AABB;

		Vector2D m_Position;
		Vector2D m_Force;
		Vector2D m_Velocity;

		float m_Torque;
		float m_Angle;
		float m_AngularVelocity;

		std::vector<Vector2D> m_Vertices;
		std::vector<Vector2D> m_TransformVertices;
		
		bool m_TransformUpdateRequired = true;
		bool m_AabbUpdateRequired = true;
	};

}

