#pragma once

#include "HitRecord.h"
#include "Material.h"

/** 
* Super class for all implicitly described surfaces in a scene. Support intersection testing
* with rays.
*/
class Surface
{
public:

	/**
	* Constructor for the surface.
	* @param - material: color of the plane.
	*/
	Surface(Material mat);

	~Surface(void);

	/**
	* Checks a ray for intersection with the surface. Finds the closest point of intersection
	* if one exits. Returns a HitRecord with the t parmeter set to FLT_MAX if there is no
	* intersection.
	* @param rayOrigin - Origin of the ray being check for intersetion
	* @param rayDirection - Unit vector represention the direction of the ray.
	* returns HitRecord containing intormation about the point of intersection.
	*/
	virtual HitRecord findClosestIntersection(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection);

	/**
	* Color of the surface
	*/
	Material material;

};

