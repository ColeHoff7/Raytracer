#pragma once
#include "BasicIncludesAndDefines.h"
#include "Surface.h"
#include "QuadricSurface.h"

class Ellipsoid : public QuadricSurface
{
public:
	Ellipsoid(const glm::vec3 & position, Material mat, double height, double width, double depth);
	virtual HitRecord findClosestIntersection(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection);
private:
	double h;
	double w;
	double d;
};