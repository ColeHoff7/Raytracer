#include "RaytraceX.h"


// Globals for raytracing

vec3 u;
vec3 v; // perpendicular up vector
vec3 w; // camera looks in the negative w direction

float fieldOfViewDegrees = 45.0;

// Measured relative to u

float rightLimit;
float leftLimit;

// Measured reltive to v (up)
float topLimit = 5;
float bottomLimit;

float nx;
float ny;

float distToPlane; // Distance to the view plane

vec3 eye(0.0, 0.0, 0.0);
vec3 rayDirection;
vec3 rayOrigin;

void setOrthoOriginAndDirection( int x, int y);
void setPerspectiveOriginAndDirection( int x, int y);
vec2 getViewPlaneCoordinate( int x, int y);
bool checkSphereCollision( vec3 & collisionPoint, vec3 & surfaceNormal );

void setCameraFrame(vec3 viewPosition, vec3 viewingDirection, vec3 up)
{
	eye = viewPosition;

	w = normalize( -viewingDirection );

	u = normalize( cross(up, w) );

	v = normalize( cross( w, u ) );

} // end setCameraFrame

void calculatePerspectiveViewingParameters()
{
	float fovRad = radians( fieldOfViewDegrees );

	distToPlane = 1.0f/tan(fovRad/2.0f); // distance from the view plane based on fov

	topLimit = 1.0f;

	rightLimit = topLimit * ((float)window.width/window.height); // Set r based on aspect ratio and height of plane

	// Make view plane symetrical about the viewing direction
	leftLimit = -rightLimit; 
	bottomLimit = -topLimit;

	// Calculate the distance between pixels in the horizontal and vertical directions
	nx = (float)window.width;
	ny = (float)window.height;
	
} // end calculatePerspectiveViewingParameters


void calculateOrthographicViewingParameters()
{
	rightLimit = topLimit * ((float)window.width/window.height); // Set r based on aspect ratio and height of plane

	// Make view plane symetrical about the viewing direction
	leftLimit = -rightLimit; 
	bottomLimit = -topLimit;

	// Calculate the distance between pixels in the horizontal and vertical directions
	nx = (float)window.width;
	ny = (float)window.height;

	distToPlane = 0.0; // Rays start on the view plane
	
} // end calculateOrthographicViewingParameters


vec3 lightPos(-5, 5, 0);
color white(1, 1, 1, 1);


void raytrace()
{
	color red(1.0, 0.0, 0.0, 1.0);


	for(int y = 0; y < window.height ; ++y) {
		for(int x = 0; x < window.width; ++x) {

			//setOrthoOriginAndDirection( x, y);

			setPerspectiveOriginAndDirection( x, y);

			vec3 interceptPoint;
			vec3 surfaceNormal;

			if(checkSphereCollision(interceptPoint, surfaceNormal)) {

				vec3 totalLight = clamp(white.rgb * red.rgb * glm::max(dot(surfaceNormal, normalize( lightPos - interceptPoint )), 0.0f) + 0.15f * red.xyz, 0.0f, 1.0f);

				setPixel(x, y, color(totalLight, 1.0f));
			}
			
		}
	}

}

void setOrthoOriginAndDirection( int x, int y)
{
	vec2 uv = getViewPlaneCoordinate( x, y );

	// Page 75
	rayDirection = normalize(-w);
	rayOrigin = eye + uv.x * u + uv.y * v;

}

void setPerspectiveOriginAndDirection( int x, int y)
{
	vec2 uv = getViewPlaneCoordinate( x, y );
	rayDirection = normalize((float)(-distToPlane) * w + uv.x * u + uv.y * v); // Page 76
	rayOrigin = eye;

}




vec2 getViewPlaneCoordinate( int x, int y)
{
	// Page 75
	vec2 s;
	s.x = leftLimit+(rightLimit-leftLimit)*(x+0.5f)/nx;
	s.y = bottomLimit+(topLimit-bottomLimit)*(y+0.5f)/ny;
	return s;
}


float radius = 1;
vec3 center(1.0, 0.0, -5.0);


bool checkSphereCollision( vec3 & collisionPoint, vec3 & surfaceNormal )
{
	// Page 77
	float discriminant = pow(dot( rayDirection, rayOrigin-center),2) - dot( rayDirection, rayDirection )*(dot( rayOrigin - center, rayOrigin - center ) -radius * radius);

	if(discriminant >= 0) {

		if(discriminant>0) {

			float t1 = ( dot( -rayDirection, rayOrigin - center ) - discriminant )/dot( rayDirection, rayDirection);
			float t2 = ( dot( -rayDirection, rayOrigin - center ) + discriminant )/dot( rayDirection, rayDirection);

			if (t1 < t2 ) {

				collisionPoint = rayOrigin + t1 * rayDirection;
			}
			else {

				collisionPoint = rayOrigin + t2 * rayDirection;
			}

		}
		else {
			// One Intercept. Find and return the t for the single point of intersection.
			float t3 = dot(-rayDirection, rayOrigin-center)/dot( rayDirection, rayDirection);

			collisionPoint = rayOrigin + t3 * rayDirection;
		}

		surfaceNormal = normalize(collisionPoint - center);

		return true;

	}
	else {

		return false;
	}



} // end checkSphereCollision
