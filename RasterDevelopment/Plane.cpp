#include "Plane.h"

/**
* Constructor for the Plane.
*/
Plane::Plane(const glm::vec3 & point, const glm::vec3 & normal, Material material)
	: Surface(material), a(point), n(glm::normalize(normal))
{
}

Plane::Plane(std::vector<glm::vec3> vertices, Material material)
	: Surface(material)
{
	a = vertices[0];

	n = glm::normalize(glm::cross(vertices[2] - vertices[1], vertices[0] - vertices[1]));
}


Plane::~Plane(void)
{
}

/*
* Checks a ray for intersection with the surface. Finds the closest point of intersection
* if one exits. Returns a HitRecord with the t parmeter set to FLT_MAX if there is no
* intersection.
*/
HitRecord Plane::findClosestIntersection(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection)
{
	HitRecord hitRecord;
	


	
	if (dot(n, rayDirection) > 0) {
		n = -n; // Reverse the normal
	}

	// Set parameter, t, in the hit record to indicate "no intersection."
	hitRecord.t = FLT_MAX;
	float tt;
	if (glm::dot(rayDirection, n) < 0) {
		tt = (glm::dot((a - rayOrigin), n) / glm::dot(rayDirection, n));
	}
	else {
		tt = FLT_MAX;
	}

	

	hitRecord.t = tt;
	hitRecord.material = this->material;
	hitRecord.interceptPoint = rayOrigin + tt * rayDirection;
	hitRecord.surfaceNormal = this->n;

	return hitRecord;

} // end checkIntercept

