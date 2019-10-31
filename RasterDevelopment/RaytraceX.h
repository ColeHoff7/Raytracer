#pragma once

#include "BasicIncludesAndDefines.h"

void raytrace();

void setCameraFrame(vec3 viewPosition, vec3 viewingDirection, vec3 up);

void calculateOrthographicViewingParameters();

void calculatePerspectiveViewingParameters();



