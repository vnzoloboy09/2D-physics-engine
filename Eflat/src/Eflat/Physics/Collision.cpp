#include "efpch.h"
#include "Collision.h"

#include "Eflat/Math/Math.h"

namespace Eflat {

	void Collision::ProjectVertices(const std::vector<Vector2D>& vertices, const Vector2D& axis, float& _min, float& _max) {
		_min = FLT_MAX;
		_max = -FLT_MAX;

		for (auto& v : vertices) {
			float projection = Math::Dot(v, axis);

			if (projection < _min) { _min = projection; }
			if (projection > _max) { _max = projection; }
		}
	}

	void Collision::ProjectCircle(const Vector2D& center, float radius, const Vector2D& axis, float& min, float& max)
	{
		Vector2D direction = Math::Normalize(axis);
		
		Vector2D point1 = center + (direction * radius);
		Vector2D point2	= center - (direction * radius);

		min = Math::Dot(point1, axis);
		max = Math::Dot(point2, axis);
	
		if (min > max)
		{
			std::swap(min, max);
		}
	}
	
	int Collision::FindClosePointOnPolygon(const Vector2D& circleCenter, const std::vector<Vector2D>& vertices) {
		int result = -1;
		float minDistance = FLT_MAX;

		for (size_t i = 0; i < vertices.size(); i++) {
			float distance = Math::Distance(vertices[i], circleCenter);
			if (minDistance > distance) {
				minDistance = distance;
				result = i;
			}
		}
		return result;
	}

	void Collision::FindCirclesContactPonint(const Vector2D& centerA, float radiusA, 
		const Vector2D& centerB, float radiusB, Vector2D& contact)
	{
		Vector2D ab = centerB - centerA;
		Vector2D direction = Math::Normalize(ab);
		contact = centerA + (direction * radiusA);
	}

	void Collision::FindPolygonsContactPonint(const std::vector<Vector2D>& verticesA, const std::vector<Vector2D>& verticesB, 
		Vector2D& contact1, Vector2D& contact2, size_t& contactCount)
	{
		float distanceSquared;
		Vector2D contactPoint;
		float minDisSq = FLT_MAX;

		for (auto& point : verticesA)
		{
			for(size_t i = 0; i < verticesB.size(); i++)
			{
				const Vector2D& va = verticesB[i];
				const Vector2D& vb = verticesB[(i + 1) % verticesB.size()];

				PointSegmentDistance(point, va, vb, distanceSquared, contactPoint);

				if (Math::NearlyEqual(distanceSquared, minDisSq)) {
					if (!Math::NearlyEqual(contactPoint, contact1)) {
						contact2 = contactPoint;
						contactCount = 2;
					}
				}
				else if (distanceSquared < minDisSq) {
					minDisSq = distanceSquared;
					contact1 = contactPoint;
					contactCount = 1;
				}
			}
		}

		for (auto& p : verticesB) {
			for (int i = 0; i < verticesA.size(); i++) {
				const Vector2D& va = verticesA[i];
				const Vector2D& vb = verticesA[(i + 1) % verticesA.size()];

				PointSegmentDistance(p, va, vb, distanceSquared, contactPoint);

				if (Math::NearlyEqual(distanceSquared, minDisSq)) {
					if (!Math::NearlyEqual(contactPoint, contact1)) {
						contact2 = contactPoint;
						contactCount = 2;
					}
				}
				else if (distanceSquared < minDisSq) {
					minDisSq = distanceSquared;
					contact1 = contactPoint;
					contactCount = 1;
				}
			}
		}
	}

	void Collision::FindCirclePolygonContactPoint(const Vector2D& centerA, const float& radiusA, 
		const Vector2D& centerB, const std::vector<Vector2D>& polygonVertices, Vector2D& outContact)
	{
		float distanceSquared;
		float minDistanceSquared = FLT_MAX;
		Vector2D contact;

		for (size_t i = 0; i < polygonVertices.size(); i++) {
			const Vector2D& va = polygonVertices[i];
			const Vector2D& vb = polygonVertices[(i + 1) % polygonVertices.size()];

			PointSegmentDistance(centerA, va, vb, distanceSquared, contact);

			if (distanceSquared < minDistanceSquared) {
				minDistanceSquared = distanceSquared;
				outContact = contact;
			}
		}
	}

	void Collision::PointSegmentDistance(const Vector2D& p, const Vector2D& a, const Vector2D& b, 
		float& distanceSquared, Vector2D& contactPoint)
	{
		Vector2D ab = b - a;
		Vector2D ap = p - a;

		float proj = Math::Dot(ap, ab);
		float abLenSq = Math::LengthSquared(ab);
		float dis = proj / abLenSq;

		if (dis < 0.0f) {
			contactPoint = a;
		}
		else if (dis > 1.0f) {
			contactPoint = b;
		}
		else {
			contactPoint = a + ab * dis;
		}

		distanceSquared = Math::DistanceSquared(p, contactPoint);
	}

	bool Collision::IntersectCircles(
		const Vector2D& centerA, float radiusA, 
		const Vector2D& centerB, float radiusB, 
		Vector2D& normal, float& depth)
	{
		float distance = Math::Distance(centerA, centerB);
		float radii = radiusA + radiusB;

		if (distance >= radii)
			return false;

		normal = Math::Normalize(centerB - centerA);
		depth = radii - distance;

		return true;
	}

	bool Collision::IntersectPolygons(
		const Vector2D& centerA, const std::vector<Vector2D>& verticesA, 
		const Vector2D& centerB, const std::vector<Vector2D>& verticesB, 
		Vector2D& normal, float& depth)
	{
		depth = FLT_MAX;

		for (size_t i = 0; i < verticesA.size(); i++) {
			const Vector2D& va = verticesA[i];
			const Vector2D& vb = verticesA[(i + 1) % verticesA.size()];

			Vector2D edge = vb - va;
			Vector2D axis = Vector2D(-edge.y, edge.x);
			axis = Math::Normalize(axis);

			float minA, maxA, minB, maxB;

			ProjectVertices(verticesA, axis, minA, maxA);
			ProjectVertices(verticesB, axis, minB, maxB);

			if (minA >= maxB || minB >= maxA) {
				return false;
			}
			float axisDepth = std::min(maxB - minA, maxA - minB);
			if (axisDepth < depth) {
				depth = axisDepth;
				normal = axis;
			}
		}

		for (size_t i = 0; i < verticesB.size(); i++) {
			const Vector2D& va = verticesB[i];
			const Vector2D& vb = verticesB[(i + 1) % verticesB.size()];

			Vector2D edge = vb - va;
			Vector2D axis = Vector2D(-edge.y, edge.x);
			axis = Math::Normalize(axis);

			float minA, maxA, minB, maxB;

			ProjectVertices(verticesA, axis, minA, maxA);
			ProjectVertices(verticesB, axis, minB, maxB);

			if (minA >= maxB || minB >= maxA) {
				return false;
			}

			float axisDepth = std::min(maxB - minA, maxA - minB);
			if (axisDepth < depth) {
				depth = axisDepth;
				normal = axis;
			}
		}

		Vector2D direction = centerB - centerA;

		if (Math::Dot(direction, normal) < 0.0f) {
			normal = -normal;
		}

		return true;
	}

	bool Collision::IntersectCirclePolygon(const Vector2D& circleCenter, float circleRadius, 
		const Vector2D& polygonCenter, const std::vector<Vector2D>& vertices, Vector2D& normal, float& depth)
	{
		normal = { 0.0f, 0.0f };
		depth = FLT_MAX;
		Vector2D axis; 
		float axisDepth = 0.0f;
		float minA, maxA, minB, maxB;

		for (size_t i = 0; i < vertices.size(); i++) {
			const Vector2D& va = vertices[i];
			const Vector2D& vb = vertices[(i + 1) % vertices.size()];

			Vector2D edge = vb - va;
			axis = Vector2D(-edge.y, edge.x);
			axis = Math::Normalize(axis);

			ProjectVertices(vertices, axis, minA, maxA);
			ProjectCircle(circleCenter, circleRadius, axis, minB, maxB);

			if (minA >= maxB || minB >= maxA) {
				return false;
			}

			axisDepth = std::min(maxB - minA, maxA - minB);

			if (axisDepth < depth) {
				depth = axisDepth;
				normal = axis;
			}
		}

		const Vector2D& closestPoint = vertices[FindClosePointOnPolygon(circleCenter, vertices)];
		axis = Math::Normalize(closestPoint - circleCenter);

		ProjectVertices(vertices, axis, minA, maxA);
		ProjectCircle(circleCenter, circleRadius, axis, minB, maxB);

		if (minA >= maxB || minB >= maxA) {
			return false;
		}

		axisDepth = std::min(maxB - minA, maxA - minB);

		if (axisDepth < depth) {
			depth = axisDepth;
			normal = axis;
		}

		Vector2D direction = closestPoint - circleCenter;

		if (Math::Dot(direction, normal) < 0.0f) {
			normal = -normal;
		}

		std::cerr << normal.x << ' ' << normal.y << " " << depth << '\n';

		return true;
	}

	bool Collision::Collided(Entity& entityA, Entity& entityB, Vector2D& normal, float& depth)
	{
		RigidBody& bodyA = entityA.GetBody();
		RigidBody& bodyB = entityB.GetBody();

		const RigidBodyData& dataA = bodyA.GetData();
		const RigidBodyData& dataB = bodyB.GetData();

		if (dataA.shapeType == Circle && dataB.shapeType == Circle)
		{
			return IntersectCircles(bodyA.GetPosition(), dataA.radius, bodyB.GetPosition(), dataB.radius, normal, depth);
		}
		if (dataA.shapeType == Box && dataB.shapeType == Circle)
		{
			return IntersectCirclePolygon(bodyB.GetPosition(), dataB.radius,
				bodyA.GetPosition(), bodyA.GetTransformVertices(), normal, depth);
		}
		if (dataA.shapeType == Circle && dataB.shapeType == Box)
		{
			return IntersectCirclePolygon(bodyA.GetPosition(), dataA.radius,
				bodyB.GetPosition(), bodyB.GetTransformVertices(), normal, depth);
		}
		if (dataA.shapeType == Box && dataB.shapeType == Box)
		{
			return IntersectPolygons(bodyA.GetPosition(), bodyA.GetTransformVertices(),
				bodyB.GetPosition(), bodyB.GetTransformVertices(), normal, depth);
		}

		return false;
	}

	void Collision::FindContactPoint(RigidBody& bodyA, RigidBody& bodyB, Vector2D& contact1, Vector2D& contact2, size_t& contactCount)
	{
		ShapeType shapeA = bodyA.GetData().shapeType;
		ShapeType shapeB = bodyB.GetData().shapeType;

		if (shapeA == Box)
		{
			if (shapeB == Box)
			{
				FindPolygonsContactPonint(bodyA.GetTransformVertices(), bodyB.GetTransformVertices(), 
					contact1, contact2, contactCount);
			}
			else if (shapeB == Circle)
			{
				FindCirclePolygonContactPoint(bodyB.GetPosition(), bodyB.GetData().radius,
					bodyA.GetPosition(), bodyA.GetTransformVertices(), contact1);
				contactCount = 1;
			}
		}
		else if (shapeA == Circle)
		{
			if (shapeB == Box)
			{
				FindCirclePolygonContactPoint(bodyA.GetPosition(), bodyA.GetData().radius,
					bodyB.GetPosition(), bodyB.GetTransformVertices(), contact1);
				contactCount = 1;
			}
			else if (shapeB == Circle)
			{
				FindCirclesContactPonint(bodyA.GetPosition(), bodyA.GetData().radius,
					bodyB.GetPosition(), bodyB.GetData().radius, contact1);
				contactCount = 1;
			}
		}
	}

	bool Collision::IntersectAABB(const AABB& a, const AABB& b)
	{
		if (a.max.x <= b.min.x || b.max.x < a.min.x ||
			a.max.y <= b.min.y || b.max.y < a.min.y) {
			return false;
		}

		return true;
	}

	void Collision::ResolveCollision(Manifold& contact)
	{
		float restitution = std::min(contact.bodyA.GetData().restitution, contact.bodyB.GetData().restitution);

		float staticFriction = (contact.bodyA.GetData().staticFriction + contact.bodyA.GetData().staticFriction) / 2.0f;
		float dynamicFriction = (contact.bodyA.GetData().dynamicFriction + contact.bodyA.GetData().dynamicFriction) / 2.0f;

		Vector2D rbList[2]              = { { 0.0f, 0.0f }, { 0.0f, 0.0f } };
		Vector2D raList[2]              = { { 0.0f, 0.0f }, { 0.0f, 0.0f } };
		Vector2D impulseList[2]         = { { 0.0f, 0.0f }, { 0.0f, 0.0f } };
		Vector2D frictionImpulseList[2] = { { 0.0f, 0.0f }, { 0.0f, 0.0f } };
		Vector2D contactList[2]         = { contact.contact1, contact.contact2 };
		float magnitudeList[2]		    = { 0.0f, 0.0f };

		for (size_t i = 0; i < contact.contactCount; i++) {
			Vector2D ra = contactList[i] - contact.bodyA.GetPosition();
			Vector2D rb = contactList[i] - contact.bodyB.GetPosition();

			raList[i] = ra;
			rbList[i] = rb;

			Vector2D raPerp(-ra.y, ra.x);
			Vector2D rbPerp(-rb.y, rb.x);

			Vector2D angularLinearVelocityA = raPerp * contact.bodyA.GetAngularVelocity();
			Vector2D angularLinearVelocityB = rbPerp * contact.bodyB.GetAngularVelocity();

			Vector2D relativeVelocity =
				(contact.bodyB.GetVelocity() + angularLinearVelocityB) -
				(contact.bodyA.GetVelocity() + angularLinearVelocityA);

			float contactVelocityMagnitue = Math::Dot(relativeVelocity, contact.normal);

			if (contactVelocityMagnitue > 0.0f) {
				continue;
			}

			float raPerpDotNormal = Math::Dot(raPerp, contact.normal);
			float rbPerpDotNormal = Math::Dot(rbPerp, contact.normal);

			float denominator = contact.bodyA.GetData().invMass + contact.bodyB.GetData().invMass +
				(raPerpDotNormal * raPerpDotNormal) * contact.bodyA.GetData().invInertia +
				(rbPerpDotNormal * rbPerpDotNormal) * contact.bodyB.GetData().invInertia;

			float magnitude = -(1.0f + restitution) * contactVelocityMagnitue;
			magnitude /= denominator * (float)contact.contactCount;

			magnitudeList[i] = magnitude;

			Vector2D impulse = magnitude * contact.normal;
			impulseList[i] = impulse;
		}

		for (size_t i = 0; i < contact.contactCount; i++) {
			Vector2D impulse = impulseList[i];

			contact.bodyA.AdjustVelocity(-impulse * contact.bodyA.GetData().invMass);
			contact.bodyA.AdjustAngularVelocity(-Math::Cross(raList[i], impulse) * contact.bodyA.GetData().invInertia);

			contact.bodyB.AdjustVelocity(impulse * contact.bodyB.GetData().invMass);
			contact.bodyB.AdjustAngularVelocity(Math::Cross(rbList[i], impulse) * contact.bodyB.GetData().invInertia);
		}

		// Friction
		for (size_t i = 0; i < contact.contactCount; i++) {
			Vector2D ra = contactList[i] - contact.bodyA.GetPosition();
			Vector2D rb = contactList[i] - contact.bodyB.GetPosition();

			raList[i] = ra;
			rbList[i] = rb;

			Vector2D raPerp(-ra.y, ra.x);
			Vector2D rbPerp(-rb.y, rb.x);

			Vector2D angularLinearVelocityA = raPerp * contact.bodyA.GetAngularVelocity();
			Vector2D angularLinearVelocityB = rbPerp * contact.bodyB.GetAngularVelocity();

			Vector2D relativeVelocity =
				(contact.bodyB.GetVelocity() + angularLinearVelocityB) -
				(contact.bodyA.GetVelocity() + angularLinearVelocityA);

			Vector2D tangent = relativeVelocity - Math::Dot(relativeVelocity, contact.normal) * contact.normal;

			if (Math::NearlyEqual(tangent, { 0.0f, 0.0f })) 
				continue;
			tangent = Math::Normalize(tangent);

			float raPerpDotTangent = Math::Dot(raPerp, tangent);
			float rbPerpDotTangent = Math::Dot(rbPerp, tangent);

			float denominator = contact.bodyA.GetData().invMass + contact.bodyB.GetData().invMass +
				(raPerpDotTangent * raPerpDotTangent) * contact.bodyA.GetData().invInertia +
				(rbPerpDotTangent * rbPerpDotTangent) * contact.bodyB.GetData().invInertia;

			float tangentMagnitude = -Math::Dot(relativeVelocity, tangent);
			tangentMagnitude /= denominator * (float)contact.contactCount;

			Vector2D frictionImpulse;
			float magnitude = magnitudeList[i];

			if (abs(tangentMagnitude) <= magnitude * staticFriction) {
				frictionImpulse = tangentMagnitude * tangent;
			}
			else {
				frictionImpulse = -magnitude * tangent * dynamicFriction;
			}

			frictionImpulseList[i] = frictionImpulse;
		}

		for (int i = 0; i < contact.contactCount; i++) {
			Vector2D frictionImpulse = frictionImpulseList[i];

			contact.bodyA.AdjustVelocity(-frictionImpulse * contact.bodyA.GetData().invMass);
			contact.bodyA.AdjustAngularVelocity(-Math::Cross(raList[i], frictionImpulse) * contact.bodyA.GetData().invInertia);

			contact.bodyB.AdjustVelocity(frictionImpulse * contact.bodyB.GetData().invMass);
			contact.bodyB.AdjustAngularVelocity(Math::Cross(rbList[i], frictionImpulse) * contact.bodyB.GetData().invInertia);
		}
	}

	void Collision::SeparateBodies(RigidBody& bodyA, RigidBody& bodyB, const Vector2D& mtv) {
		if (bodyA.GetData().isStatic) {
			bodyB.Move(mtv);
		}
		else if (bodyB.GetData().isStatic) {
			bodyA.Move(-mtv);
		}
		else {
			bodyA.Move(-mtv * 0.5f);
			bodyB.Move(mtv * 0.5f);
		}
	}
}