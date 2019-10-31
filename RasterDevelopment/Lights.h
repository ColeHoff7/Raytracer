#pragma once

#include "BasicIncludesAndDefines.h"
#include "HitRecord.h"
#include <algorithm> 
#include "Surface.h"


HitRecord findIntersection(const glm::vec3 &e, const glm::vec3 &d, std::vector<std::shared_ptr<Surface>> & surfaces);
/**
* Base struct for all types of lights. 
*/
struct LightSource
{
	LightSource(const color & col)
	: lightColor(col)
	{}

	virtual color illuminate(const glm::vec3 & eyeVector, HitRecord & closestHit, std::vector<std::shared_ptr<Surface>> & surfaces)
	{
		return lightColor * closestHit.material.ambientColor;
	}

	/*
	* Color and intensity of the light.
	*/
	color lightColor;
};

/**
* Struct for simulating light sources that have an explicit position and
* shine equally in all directions.
*/
struct PositionalLight : public LightSource
{
	PositionalLight(glm::vec3 position, const color & col)
	: LightSource(col), position(position)
	{}

	virtual color illuminate(const glm::vec3 & eyeVector, HitRecord & closestHit, std::vector<std::shared_ptr<Surface>> & surfaces)
	{
		glm::vec3 n = glm::normalize(closestHit.surfaceNormal);
		glm::vec3 l = glm::normalize(position - closestHit.interceptPoint);
		glm::vec3 r = glm::reflect(-l, n);//glm::normalize(-l - (2 * glm::dot(l, n) * n));
		glm::vec3 v = glm::normalize(eyeVector);
		glm::vec3 h = glm::normalize(v + l);

		HitRecord hr = findIntersection(closestHit.interceptPoint, glm::normalize(position-closestHit.interceptPoint), surfaces);
		
		color diffuse = std::max(0.0f, glm::dot(n, l)) * closestHit.material.diffuseColor * lightColor;
		color specular = std::pow(std::max(0.0f, glm::dot(r,v)), 100) * closestHit.material.specularColor * color(1.0f, 1.0f, 1.0f, 1.0f);
		
		if (hr.t < FLT_MAX && hr.t > 0) {
			return color(0.0, 0.0, 0.0, 1.0);
		}
		//attenuation
		return (float)(1/(.05+ .07*closestHit.t+.01*pow(closestHit.t,2))) * diffuse+specular;
	}

	/**
	* x, y, z position of the light source.
	*/
	glm::vec3 position;
};

/**
* Struct for simulating light sources that do not have an explicit position.
*/
struct DirectionalLight : public LightSource
{
	DirectionalLight(glm::vec3 direction, const color & col)
	: LightSource(col), direction(glm::normalize(direction))
	{}

	virtual color illuminate(const glm::vec3 & eyeVector, HitRecord & closestHit, std::vector<std::shared_ptr<Surface>> & surfaces)
	{
		glm::vec3 n = glm::normalize(closestHit.surfaceNormal);
		glm::vec3 l = glm::normalize(direction);
		glm::vec3 r = glm::reflect(-l, n);//glm::normalize(-l - (2 * glm::dot(l, n) * n));
		glm::vec3 v = glm::normalize(eyeVector);
		glm::vec3 h = glm::normalize(v + l);

		HitRecord hr = findIntersection(closestHit.interceptPoint, glm::normalize(direction), surfaces);

		color diffuse = std::max(0.0f, glm::dot(n, l)) * closestHit.material.diffuseColor * lightColor;
		color specular = std::pow(std::max(0.0f, glm::dot(r, v)), 100) * closestHit.material.specularColor * color(1.0f, 1.0f, 1.0f, 1.0f);

		if (hr.t < FLT_MAX && hr.t > 0) {
			return color(0.0, 0.0, 0.0, 1.0);
		}
		return diffuse + specular;
	}

	/**
	* Unit vector that points in the direction that is opposite
	* the direction in which the light is shining.
	*/
	glm::vec3 direction;
};



