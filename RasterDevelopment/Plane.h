#pragma once
#include "surface.h"

/**
* Sub-class of Surface that represents implicit description of a plane.
*/
class Plane : public Surface
{
public:

	/**
	* Constructor for the plane. 
	* @param - point: specifies an xyz position that is on the plane
	* @param - normal: unit Vector that is perpendicular to the front face of the plane
	* @param - material: color of the plane.
	*/
	Plane(const glm::vec3 & point, const glm::vec3 & normal, Material material);

	Plane(std::vector<glm::vec3> vertices, Material material);

	~Plane(void);

	/**
	* Checks a ray for intersection with the surface. Finds the closest point of intersection
	* if one exits.
	*/
	virtual HitRecord findClosestIntersection(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection);

	/** Point on the plane */
	glm::vec3 a;

	/** Unit Vector that is perpendicular to the front face of the plane 
	* (surface normal */
	glm::vec3 n;

};

