#pragma once

namespace Eflat {

	enum ShapeType {
		None = 0,
		Circle,
		Box
	};

	struct RigidBodyData {
		ShapeType shapeType;
		float mass;
		float invMass;
		float density;
		float restitution;
		float area;
		float radius;
		float width;
		float height;
		bool isStatic;
		float inertia;
		float invInertia;
		float staticFriction;
		float dynamicFriction;

		RigidBodyData(
			ShapeType shapeType   = Circle,
			float mass            = 10.0f,
			float density         = 1.0f,
			float restitution     = 0.5f,
			float area            = 50.0f,
			float radius          = 20.0f,
			float width           = 0.0f,
			float height          = 0.0f,
			bool b_IsStatic       = false,
			float inertia         = 1.0f,
			float staticFriction  = 0.5f,
			float dynamicFriction = 0.3f

		)
			: shapeType(shapeType),
			mass(mass),
			invMass(mass == 0.0f ? 0.0f : 1.0f / mass),
			density(density),
			restitution(restitution),
			area(area),
			radius(radius),
			width(width),
			height(height),
			isStatic(b_IsStatic),
			inertia(inertia),
			invInertia(inertia == 0.0f ? 0.0f : 1.0f / inertia),
			staticFriction(staticFriction),
			dynamicFriction(dynamicFriction) {
		}
	};
}