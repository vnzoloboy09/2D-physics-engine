#pragma once

#include "Eflat/Entity/RigidBody.h"

namespace Eflat {

	class Manifold
	{
	public:
		Manifold(RigidBody& bodyA, RigidBody& bodyB, Vector2D nor, float dep,
			const Vector2D& ct1, const Vector2D& ct2, size_t ctCount);
		~Manifold();

	public:
		RigidBody& bodyA;
		RigidBody& bodyB;
		const Vector2D normal;
		const float depth;

		const Vector2D contact1;
		const Vector2D contact2;
		const size_t contactCount;

	private:
	};

}

