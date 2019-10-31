#include "Ellipsoid.h"

Ellipsoid::Ellipsoid(const glm::vec3 & position, Material mat, double height, double width, double depth)
	: QuadricSurface(position, mat), h(height), w(width), d(depth)
{
	A = (1 / pow(w, 2));
	B = (1 / pow(h, 2));
	C = (1 / pow(d, 2));
	D = 0;
	E = 0;
	F = 0;
	G = 0;
	H = 0;
	I = 0;
	J = -1;
}

HitRecord Ellipsoid::findClosestIntersection(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection)
{
	HitRecord hr = QuadricSurface::findClosestIntersection(rayOrigin, rayDirection);
	glm::vec3 v = hr.interceptPoint;
	return hr;

}