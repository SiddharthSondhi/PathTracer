#pragma once

#include "Hittable.h"
#include "Ray.h"
#include <vector>
#include <memory>

// maybe redo design for this later, for now inherits from hittable and represent hittable list of other hittables
class HittableList : public Hittable {
public:
	HittableList();
	HittableList(const std::shared_ptr<Hittable>& object);

	void clear();
	void add(const std::shared_ptr<Hittable>& object);

	bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const override;

private:
	std::vector<std::shared_ptr<Hittable>> objects;
};