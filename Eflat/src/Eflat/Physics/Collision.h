#pragma once

#include "Eflat/Math/Vector2D.h"

#include "Eflat/Entity/Entity.h"
#include "Manifold.h"

namespace Eflat {

	class Collision
	{
	public:
		static bool IntersectCircles( const Vector2D& centerA, float radiusA, 
			const Vector2D& centerB, float radiusB, Vector2D& normal, float& depth);

		static bool IntersectPolygons(const Vector2D& centerA, const std::vector<Vector2D>& verticesA,
			const Vector2D& centerB, const std::vector<Vector2D>& verticesB, Vector2D& normal, float& depth);

		static bool IntersectCirclePolygon(const Vector2D& circleCenter, float radius, const Vector2D& pylygonCenter,
			const std::vector<Vector2D>& vertices, Vector2D& normal, float& depth);

		static bool Collided(Entity& entityA, Entity& entityB, Vector2D& normal, float& depth);

		static void FindContactPoint(RigidBody& bodyA, RigidBody& bodyB, Vector2D& contact1, Vector2D& contact2, size_t& contactCount);

		static bool IntersectAABB(const AABB& a, const AABB& b);

		static void ResolveCollision(Manifold& contact);

		static void SeparateBodies(RigidBody& bodyA, RigidBody& bodyB, const Vector2D& mtv);

	private:
		static void ProjectVertices(const std::vector<Vector2D>& vertices, const Vector2D& axis, float& _min, float& _max);

		static void ProjectCircle(const Vector2D& position, float radius, const Vector2D& axis, float& _min, float& _max);

		static int FindClosePointOnPolygon(const Vector2D& circleCenter, const std::vector<Vector2D>& vertices);

		static void FindCirclesContactPonint(const Vector2D& centerA, float radiusA, 
			const Vector2D& centerB, float radiusB, Vector2D& contact);

		static void FindPolygonsContactPonint(const std::vector<Vector2D>& verticesA, const std::vector<Vector2D>& verticesB,
			Vector2D& contact1, Vector2D& contact2, size_t& contactCount);

		static void FindCirclePolygonContactPoint(const Vector2D& centerA, const float& radiusA,
			const Vector2D& centerB, const std::vector<Vector2D>& polygonVertices, Vector2D& contact);

		static void PointSegmentDistance(const Vector2D& p, const Vector2D& a, const Vector2D& b,
			float& distanceSquared, Vector2D& contactPoint);
	};

}

