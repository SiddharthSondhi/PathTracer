#include "Ray.h"

Ray::Ray() :
	origin{ 0.0f, 0.0f, 0.0f },
	direction{ 0.0f, 0.0f, -1.0f }
{}

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction) :
	origin{ origin },
	direction{ glm::normalize(direction) }
{}


const glm::vec3& Ray::getOrigin() const {
	return origin;
}


const glm::vec3& Ray::getDirection() const {
	return direction;
}

glm::vec3 Ray::at(float t) const {
	return origin + direction * t;
}
