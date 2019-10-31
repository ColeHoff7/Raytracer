#pragma once
#include "BasicIncludesAndDefines.h"
/**
* Simple stuct to hold the material properties of a surface
*/
struct Material {
	
	Material(color ambDifColor = color(1.0f, 1.0f, 1.0f, 1.0f),
		color specColor = color(1.0f, 1.0f, 1.0f, 1.0f))
		: ambientColor(ambDifColor), diffuseColor(ambDifColor),
		specularColor(specColor), emissiveColor(0.0f, 0.0f, 0.0f, 1.0f)
	{}
	// Ambient color of the surface
	color ambientColor;
	// Diffuse color of the surface
	color diffuseColor;
	// Specular color of the surface
	color specularColor;
	// Emissive color of the surface
	color emissiveColor;
};