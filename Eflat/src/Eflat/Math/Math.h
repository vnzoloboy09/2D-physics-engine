#pragma once

#include "Vector2D.h"

namespace Eflat {

	class Math {
	public:
		static const float SMALL_AMOUNT; 

	public:
		static float Clamp(float& value, const float& min, const float& max);
		static int Clamp(int& value, const int& min, const int& max);

		static float Length(const Vector2D& v);
		static float LengthSquared(const Vector2D& v);
		static float Distance(const Vector2D& a, const Vector2D& b);
		static float DistanceSquared(const Vector2D& a, const Vector2D& b);
		static Vector2D Normalize(const Vector2D& v);
		static float Dot(const Vector2D& a, const Vector2D& b);
		static float Cross(const Vector2D& a, const Vector2D& b);
		static bool NearlyEqual(const float& a, const float& b);
		static bool NearlyEqual(const Vector2D& a, const Vector2D& b);
	};

}

