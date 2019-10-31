#include "RayTracer.h"


RayTracer::RayTracer(FrameBuffer & cBuffer, color defaultColor )
:colorBuffer(cBuffer), defaultColor(defaultColor)
{
	
}


RayTracer::~RayTracer(void)
{
}

void RayTracer::setOrtho(bool b) {
	ortho = b;
}

bool RayTracer::getOrtho() {
	return ortho;
}

void RayTracer::setCameraFrame(const glm::vec3 & viewPosition, const glm::vec3 & viewingDirection, glm::vec3 up)
{
	eye = viewPosition;
	w = glm::normalize(-viewingDirection);
	u = glm::normalize(glm::cross(up, w));
	v = glm::normalize(glm::cross(w, u));

} // end setCameraFrame


void RayTracer::calculatePerspectiveViewingParameters(const float verticalFieldOfViewDegrees)
{
	nx = (float)colorBuffer.getWindowWidth();
	ny = (float)colorBuffer.getWindowHeight();
	distToPlane = 1 / glm::tan(verticalFieldOfViewDegrees / 2);
	topLimit = 1;
	bottomLimit = -topLimit;

	rightLimit = topLimit * (nx/ny);
	leftLimit = -rightLimit;

} // end calculatePerspectiveViewingParameters


void RayTracer::calculateOrthographicViewingParameters(const float viewPlaneHeight)
{
	topLimit = fabs(viewPlaneHeight) / 2.0f;

	rightLimit = topLimit * ((float)colorBuffer.getWindowWidth()/colorBuffer.getWindowHeight()); // Set r based on aspect ratio and height of plane

	// Make view plane symetrical about the viewing direction
	leftLimit = -rightLimit; 
	bottomLimit = -topLimit;

	// Calculate the distance between pixels in the horizontal and vertical directions
	nx = (float)colorBuffer.getWindowWidth();
	ny = (float)colorBuffer.getWindowHeight();

	distToPlane = 0.0; // Rays start on the view plane
	
} // end calculateOrthographicViewingParameters


void RayTracer::raytraceScene(const std::vector<std::shared_ptr<Surface>> & surfaces, const std::vector<std::shared_ptr<LightSource>> & lights)
{
	this->surfacesInScene = surfaces;
	this->lightsInScene = lights;

	for (int x = 0; x < colorBuffer.getWindowWidth(); x++) {
		for (int y = 0; y < colorBuffer.getWindowHeight(); y++) {
			if (ortho) {
				setOrthoRayOriginAndDirection(x, y);
			}
			else {
				setPerspectiveRayOriginAndDirection(x, y);
			}
			color pixel = traceIndividualRay(rayOrigin, rayDirection, recursionDepth);
			colorBuffer.setPixel(x, y, pixel);
		}
	}
	
} // end raytraceScene



color RayTracer::traceIndividualRay(const glm::vec3 &e, const glm::vec3 &d, int recursionLevel)
{

	HitRecord closestHit = findIntersection(e, d, surfacesInScene);
	closestHit.interceptPoint = closestHit.interceptPoint + 1.0E-4f * glm::normalize(closestHit.surfaceNormal);

	color totalLight;

	for (int i = 0; i < (int)lightsInScene.size(); i++) {
		totalLight += lightsInScene[i]->illuminate(-d, closestHit, surfacesInScene);
	}

	if (recursionLevel > 0)
	{
		if (closestHit.t > 0) {
			glm::vec3 norm = closestHit.surfaceNormal;
			glm::vec3 newD = reflect(d, norm);//normalize(d - (2.0f * dot(d, norm) * norm));
			totalLight += .2f*traceIndividualRay(closestHit.interceptPoint, newD, recursionLevel - 1);
		}
		else {
			//reflecting the sky
			totalLight += .3f*defaultColor;
		}
	}

	if (recursionLevel < recursionDepth) {
		//distance attenuation
		return (float)(1 / (.005 + .07*closestHit.t + .01*pow(closestHit.t, 2))) * totalLight;
	}
	return totalLight;


} // end traceRay

void RayTracer::setOrthoRayOriginAndDirection( const int x, const int y)
{
	glm::vec2 uv = getProjectionPlaneCoordinates(x, y);
	rayDirection = glm::normalize(-w);
	rayOrigin = eye + uv.x * u + uv.y * v;

} // end setOrthoOriginAndDirection


void RayTracer::setPerspectiveRayOriginAndDirection(const int x, const int y)
{
	glm::vec2 uv = getProjectionPlaneCoordinates(x, y);
	// TODO
	rayOrigin = eye;
	rayDirection = glm::normalize((-distToPlane * w) + ((float)uv.x * u) + ((float)uv.y * v));

} // end setPerspectiveOriginAndDirection


glm::vec2 RayTracer::getProjectionPlaneCoordinates(const int x, const int y)
{
	glm::vec2 s;
	
	double u = (x + .05) * ((rightLimit - leftLimit) / colorBuffer.getWindowWidth()) + leftLimit;
	double v = (y + .05) * ((topLimit - bottomLimit) / colorBuffer.getWindowHeight()) + bottomLimit;
	s = glm::vec2(u,v);
	

	return s;
}



