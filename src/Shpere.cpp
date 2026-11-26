#include "Sphere.h"

Sphere::Sphere(const glm::vec3 center, float radius) : 
	center{ center },
	radius{ radius }
{}

// Finds if there is an intersection between a ray and the sphere. If there is one, finds the closes root (value of t)
// that is within the given (tMin, tMax) range. If found, calculates normal for sphere at that point.
bool Sphere::hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const {
	glm::vec3 d{ r.getDirection() };
	glm::vec3 Q{ r.getOrigin() };
	glm::vec3 CminusQ{ center - Q };

	float a{ glm::dot(d, d) };
	float h{ glm::dot(d, CminusQ) };
	float c{ glm::dot(CminusQ, CminusQ) - radius * radius };

	float discriminant{ h * h - a * c };

	// 0 solutions, if ray does not intersect
	if (discriminant < 0)
		return false;

	float discSqrt{ glm::sqrt(discriminant) };
	
	// first root, subtract discriminant, this will always be smaller than the second root
	float root{ (h - discSqrt) / a };

	// if the first root is greater than the maximum, the second root will always also be greater, so just return
	if (root >= tMax)
		return false;

	// then if the first root is less than tMin (case where it is inside the sphere or close to the surface)
	// check the second root
	if (root <= tMin) {
		root = (h + discSqrt) / a;

		// now check if this root is within the range
		if (root <= tMin || root >= tMax)
			return false;
	}

	// update hit record
	rec.t = root;
	rec.point = r.at(root);

	// Normal of sphere is vector form center to point on surface. Make unit vector by / by radius
	rec.normal = (rec.point - center) / radius;
	
	return true;
}

