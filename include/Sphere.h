#pragma once

#include "Hittable.h"


class Sphere : public Hittable {
public:
	Sphere(const glm::vec3 center, float radius);
	bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const override;

private:
	glm::vec3 center;
	float radius;
};