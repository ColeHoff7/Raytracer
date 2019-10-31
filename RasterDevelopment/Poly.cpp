#include "Poly.h"



Poly::Poly(std::vector<glm::vec3> points, Material material)
	: Plane(points, material), vertices(points)
{
}


Poly::~Poly()
{
}

HitRecord Poly::findClosestIntersection(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection)
{
	HitRecord hr = Plane::findClosestIntersection(rayOrigin, rayDirection);
	
	if (hr.t < FLT_MAX) {
		//std::cout << "true";
		bool b = true;
		for (int i = 0; i < vertices.size(); i++) {
			if (i == vertices.size() - 1) {
				int c = glm::dot(glm::cross((vertices[0] - vertices[i]), (hr.interceptPoint - vertices[i])), n);
				if (c <= 0) {
					b = false;
				}
			}
			else {
				int c = glm::dot(glm::cross((vertices[i + 1] - vertices[i]), (hr.interceptPoint - vertices[i])), n);
				if (c <= 0) {
					b = false;
				}
			}
		}


		//if it is left of all sides, return the hr, else it didn't hit
		if (b) {
			return hr;
		}
		else {
			hr.t = FLT_MAX;
			return hr;
		}
	}
	else {
		return hr;
	}
}
