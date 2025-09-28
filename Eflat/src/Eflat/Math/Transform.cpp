#include "efpch.h"
#include "Transform.h"

namespace Eflat {

	Transform::Transform(Vector2D position, float angle)
		: positionX(position.x),
		positionY(position.y),
		sin(std::sin(angle)),
		cos(std::cos(angle)) 
	{}

	Transform::Transform(float x, float y, float angle)
		: positionX(x),
		positionY(y),
		sin(std::sin(angle)),
		cos(std::cos(angle)) 
	{}

	Transform::Transform()
		: positionX(0.0f),
		positionY(0.0f),
		sin(std::sin(0.0f)),
		cos(std::cos(0.0f)) 
	{}

	Transform::~Transform()
	{

	}
}