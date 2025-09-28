#include "efpch.h"
#include "Math.h"

#include <cmath>

namespace Eflat {

	const float Math::SMALL_AMOUNT = 0.0005f; // 1/2 of a milimeter

	float Math::Clamp(float& value, const float& min, const float& max) {
		if (min == max) return min;
		if (min > value) return min;
		if (max < value) return max;
		return value;
	}

	int Math::Clamp(int& value, const int& min, const int& max) {
		if (min == max) return min;
		if (min > value) return min;
		if (max < value) return max;
		return value;
	}

	float Math::Length(const Vector2D& v) {
		return sqrt(v.x * v.x + v.y * v.y);
	}

	float Math::LengthSquared(const Vector2D& v) {
		return v.x * v.x + v.y * v.y;
	}

	float Math::Distance(const Vector2D& a, const Vector2D& b) {
		Vector2D d = a - b;
		return sqrt(d.x * d.x + d.y * d.y);
	}

	float Math::DistanceSquared(const Vector2D& a, const Vector2D& b) {
		Vector2D d = a - b;
		return d.x * d.x + d.y * d.y;
	}

	Vector2D Math::Normalize(const Vector2D& v) {
		float magnitude = Math::Length(v);
		if (magnitude < 1e-6f) return { 0.0f, 0.0f }; // Avoid division by near-zero
		return { v.x / magnitude, v.y / magnitude };
	}

	float Math::Dot(const Vector2D& a, const Vector2D& b) {
		return a.x * b.x + b.y * a.y;
	}

	float Math::Cross(const Vector2D& a, const Vector2D& b) {
		return a.x * b.y - a.y * b.x;
	}

	bool Math::NearlyEqual(const float& a, const float& b) {
		return std::abs(a - b) < SMALL_AMOUNT;
	}

	bool Math::NearlyEqual(const Vector2D& a, const Vector2D& b) {
		return Math::DistanceSquared(a, b) < SMALL_AMOUNT * SMALL_AMOUNT;

	}

}