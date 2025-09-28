#pragma once

namespace Eflat {

	class Transform;

	class Vector2D
	{
	public:
		Vector2D(float x = 0.0f, float y = 0.0f);
		Vector2D(float value);
		~Vector2D();

		Vector2D& Add(const Vector2D& vec);
		Vector2D& Subtract(const Vector2D& vec);
		Vector2D& Multiply(const Vector2D& vec);
		Vector2D& Divide(const Vector2D& vec);

		friend Vector2D operator +(const Vector2D& v1, const Vector2D& v2);
		friend Vector2D operator -(const Vector2D& v1, const Vector2D& v2);
		friend Vector2D operator *(const Vector2D& v1, const Vector2D& v2);
		friend Vector2D operator /(const Vector2D& v1, const Vector2D& v2);

		Vector2D& operator +=(const Vector2D& vec);
		Vector2D& operator -=(const Vector2D& vec);
		Vector2D& operator *=(const Vector2D& vec);
		Vector2D& operator /=(const Vector2D& vec);

		friend Vector2D operator +(float scalar, const Vector2D& vec);
		friend Vector2D operator -(float scalar, const Vector2D& vec);
		friend Vector2D operator *(float scalar, const Vector2D& vec);
		friend Vector2D operator /(float scalar, const Vector2D& vec);

		Vector2D operator +(float scalar) const;
		Vector2D operator -(float scalar) const;
		Vector2D operator *(float scalar) const;
		Vector2D operator /(float scalar) const;

		bool Equals(const Vector2D& other) const;
		bool operator==(const Vector2D& other) const;

		Vector2D operator -() const;

		static Vector2D Vector2DTransform(Vector2D v, Transform transform);

	public:
		float x, y;
	};

}

