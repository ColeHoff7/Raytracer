#include "Lights.h"
#include "Surface.h"

HitRecord findIntersection(const glm::vec3 &e, const glm::vec3 &d, std::vector<std::shared_ptr<Surface>> & surfaces)
{
	double smallestT = FLT_MAX;
	int size = (int)surfaces.size();
	HitRecord closestHit;

	for (int i = 0; i < size; i++) {
		HitRecord hr = surfaces[i]->findClosestIntersection(e, d);
		if (hr.t < smallestT && hr.t > 0) {
			smallestT = hr.t;
			closestHit = hr;
		}
	}

	return closestHit;

}


