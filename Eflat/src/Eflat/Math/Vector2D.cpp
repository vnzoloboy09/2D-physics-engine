#include "efpch.h"
#include "Vector2D.h"

#include "Transform.h"

namespace Eflat {

	Vector2D::Vector2D(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2D::Vector2D(float value)
	{
		this->x = value;
		this->y = value;
	}

	Vector2D::~Vector2D()
	{

	}

	Vector2D& Vector2D::Add(const Vector2D& vec)
	{
		this->x += vec.x;
		this->y += vec.y;

		return *this;
	}

	Vector2D& Vector2D::Subtract(const Vector2D& vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;
	
		return *this;
	}

	Vector2D& Vector2D::Multiply(const Vector2D& vec)
	{
		this->x *= vec.x;
		this->y *= vec.y;
	
		return *this;
	}

	Vector2D& Vector2D::Divide(const Vector2D& vec)
	{
		if (vec.x == 0 || vec.y == 0)
			__debugbreak();

		this->x /= vec.x;
		this->y /= vec.y;
	
		return *this;
	}

	bool Vector2D::Equals(const Vector2D& other) const
	{
		return (x == other.x && y == other.y);
	}

	Vector2D Vector2D::operator-() const
	{
		return { -this->x, -this->y };
	}

	bool Vector2D::operator==(const Vector2D& other) const
	{
		return Equals(other);
	}

	Vector2D& Vector2D::operator/=(const Vector2D& vec)
	{
		return this->Divide(vec);
	}

	Vector2D& Vector2D::operator*=(const Vector2D& vec)
	{
		return this->Multiply(vec);
	}

	Vector2D& Vector2D::operator-=(const Vector2D& vec)
	{
		return this->Subtract(vec);
	}

	Vector2D& Vector2D::operator+=(const Vector2D& vec)
	{
		return this->Add(vec);
	}

	Vector2D operator +(const Vector2D& v1, const Vector2D& v2)
	{
		return { v1.x + v2.x, v1.y + v2.y };
	}

	Vector2D operator -(const Vector2D& v1, const Vector2D& v2)
	{
		return { v1.x - v2.x, v1.y - v2.y };
	}

	Vector2D operator *(const Vector2D& v1, const Vector2D& v2)
	{
		return { v1.x * v2.x, v1.y * v2.y };
	}

	Vector2D operator /(const Vector2D& v1, const Vector2D& v2)
	{
		if (v2.x == 0 || v2.y == 0)
			__debugbreak();
		return { v1.x / v2.x, v1.y / v2.y };
	}

	Vector2D operator +(float scalar, const Vector2D& vec)
	{
		return { vec.x + scalar, vec.y + scalar };
	}

	Vector2D operator -(float scalar, const Vector2D& vec)
	{
		return { vec.x - scalar, vec.y - scalar };

	}
	
	Vector2D operator *(float scalar, const Vector2D& vec)
	{
		return { vec.x * scalar, vec.y * scalar };

	}
	
	Vector2D operator /(float scalar, const Vector2D& vec)
	{
		return { vec.x / scalar, vec.y / scalar };

	}

	Vector2D Vector2D::operator +(float scalar) const
	{
		return { x + scalar, y + scalar };
	}

	Vector2D Vector2D::operator -(float scalar) const
	{
		return { x - scalar, y - scalar };
	}

	Vector2D Vector2D::Vector2DTransform(Vector2D v, Transform transform)
	{
		return { transform.cos * v.x - transform.sin * v.y + transform.positionX,
		transform.sin * v.x + transform.cos * v.y + transform.positionY };
	}

	Vector2D Vector2D::operator *(float scalar) const
	{
		return { x * scalar, y * scalar };
	}

	Vector2D Vector2D::operator /(float scalar) const
	{
		if (scalar == 0)
			__debugbreak();
		return { x / scalar, y / scalar };
	}
}