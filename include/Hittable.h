#pragma once

#include "Ray.h"
#include <glm/glm.hpp>

struct HitRecord {
	glm::vec3 point;
	glm::vec3 normal;
	float t;
};


// An interface that represents anything "hittable" by a ray, could be a singular object or some
// data structure of objects
class Hittable {
public:
	virtual ~Hittable() = default;
	virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;

};