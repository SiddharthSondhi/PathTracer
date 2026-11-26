#include "HittableList.h"

HittableList::HittableList() {}

HittableList::HittableList(const std::shared_ptr<Hittable>& object) {
	add(object);
}

void HittableList::add(const std::shared_ptr<Hittable>& object) {
	objects.push_back(object);
}

void HittableList::clear() {
	objects.clear();
}

bool HittableList::hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const {
	HitRecord tempRec;
	float closestSoFar{ tMax };
	bool hitAnything{ false };

	// traverse through all objects, checking for intersections
	for (const auto& object : objects) {
		// since closestSoFar is used as tMax, any new intersecions will be closer, therefore, set any new intersection as 
		// closest so far and update hitRecord.
		if (object->hit(r, tMin, closestSoFar, tempRec)) {
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}

	return hitAnything;
}
