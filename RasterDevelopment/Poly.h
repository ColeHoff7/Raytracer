#pragma once
#include "Plane.h"
#include <vector>
class Poly : public Plane
{
public:
	Poly(std::vector<glm::vec3> points, Material material);
	~Poly();
	virtual HitRecord findClosestIntersection(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection);
	std::vector<glm::vec3> vertices;
};

