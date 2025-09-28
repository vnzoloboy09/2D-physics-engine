#include "efpch.h"
#include "Manifold.h"

namespace Eflat {


	Manifold::Manifold(RigidBody& bdA, RigidBody& bdB, Vector2D nor, float dep, 
		const Vector2D& ct1, const Vector2D& ct2, size_t ctCount)
		: bodyA(bdA), bodyB(bdB), normal(nor), depth(dep),
		contact1(ct1), contact2(ct2), contactCount(ctCount)
	{

	}

	Manifold::~Manifold()
	{

	}

}
