#include "Main.h"

//******** Global Variables ***********

// Frame buffer for holding pixel color and depth values
FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

// Ray tracer that generates the rendered image
RayTracer rayTrace(frameBuffer);

// Surfaces or object in the scene to be rendered
std::vector<std::shared_ptr<Surface>> surfaces;

// Light sources in the scene
std::vector<std::shared_ptr<LightSource>> lights;

//***********************************

/**
* Acts as the display function for the window. 
*/
static void RenderSceneCB()
{

	// Ray trace the scene to determine the color of all the pixels in the scene
	rayTrace.raytraceScene( surfaces, lights);

	// Display the color buffer
	frameBuffer.showColorBuffer();

} // end RenderSceneCB


// Reset viewport limits for full window rendering each time the window is resized.
// This function is called when the program starts up and each time the window is 
// resized.
static void ResizeCB(int width, int height)
{
	// Size the color buffer to match the window size.
	frameBuffer.setFrameBufferSize( width, height );

	rayTrace.setCameraFrame(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0) );

	if (rayTrace.getOrtho()) {
		rayTrace.calculatePerspectiveViewingParameters();
	}
	else {
		rayTrace.calculatePerspectiveViewingParameters(45.0f);
	}
	// Signal the operating system to re-render the window
	glutPostRedisplay();

} // end ResizeCB


// Responds to 'f' and escape keys. 'f' key allows 
// toggling full screen viewing. Escape key ends the
// program. Allows lights to be individually turned on and off.
static void KeyboardCB(unsigned char key, int x, int y)
{
	std::shared_ptr<LightSource> ambientLightNight = std::make_shared<LightSource>(color(0.15, 0.15, 0.15, 1.0));
	//std::shared_ptr<PositionalLight> lightPosNight = std::make_shared<PositionalLight>(glm::vec3(5, 3, -9), glm::vec4(1, 1, 1, 1));
	std::shared_ptr<DirectionalLight>  dirLightNight = std::make_shared<DirectionalLight>(glm::vec3(0, 1, 0), glm::vec4(.3, .3, .3, 1));

	std::shared_ptr<LightSource> ambientLightDay = std::make_shared<LightSource>(color(0.15, 0.15, 0.15, 1.0));
	std::shared_ptr<PositionalLight> lightPosDay = std::make_shared<PositionalLight>(glm::vec3(5, 3, -9), glm::vec4(1, 1, 1, 1));
	std::shared_ptr<DirectionalLight>  dirLightDay = std::make_shared<DirectionalLight>(glm::vec3(0, 1, 0), glm::vec4(.6, .6, .6, 1));
	std::cout << key << " key pressed." << std::endl;
	switch(key) {
		
	case('F') : // 'f' key to toggle full screen
		glutFullScreenToggle();
		break;
	case('0'):
		rayTrace.setRecursionDepth(0);
		break;
	case('1'):
		rayTrace.setRecursionDepth(1);
		break;
	case('2'):
		rayTrace.setRecursionDepth(2);
		break;
	case('3'):
		rayTrace.setRecursionDepth(3);
		break;
	case('d'):
		
		lights.clear();
		lights.push_back(ambientLightDay);
		lights.push_back(lightPosDay);
		lights.push_back(dirLightDay);
		break;
	case('n'):
		
		lights.clear();
		lights.push_back(ambientLightNight);
		//lights.push_back(lightPosNight);
		lights.push_back(dirLightNight);
		break;
	case('f'):
		rayTrace.setCameraFrame(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
		break;
	case('b'):
		rayTrace.setCameraFrame(glm::vec3(0, 0, -45), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
		break;
	case('p'):
		
		if (rayTrace.getOrtho()) {
			rayTrace.setOrtho(false);
		}
		else {
			rayTrace.setOrtho(true);
		}
		break;
	case(27): // Escape key
		glutLeaveMainLoop();
		break;
	default:
		std::cout << key << " key pressed." << std::endl;
	}

	glutPostRedisplay();

} // end KeyboardCB


// Responds to presses of the arrow keys
static void SpecialKeysCB(int key, int x, int y)
{
	switch(key) {
	
	case(GLUT_KEY_RIGHT):
		
		break;
	case(GLUT_KEY_LEFT):
		
		break;
	default:
		std::cout << key << " key pressed." << std::endl;
	}

	glutPostRedisplay();

} // end SpecialKeysCB

void buildScene()
{
	// Initialize random seed - used to create random colors
	srand((unsigned int)time(NULL));

	// Create objects in the scene
	std::shared_ptr<Sphere> redBall = std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -10.0f), 1.5f, Material(color(0.8f, 0.3f, 0.3f, 1.0f), color(1.0f, 1.0f, 1.0f, 1.0f)));
	std::shared_ptr<Sphere> greenBall = std::make_shared<Sphere>(glm::vec3(3.0f, 0.0f, -15.0f), 2.0f, Material(color(.2f, 0.8f, 0.2f, 1.0f), color(1.0f, 1.0f, 1.0f, 1.0f)));
	std::shared_ptr<Sphere> blueBall = std::make_shared<Sphere>(glm::vec3(-4.0f, 2.0f, -20.0f), 4.0f, Material(color(.4f, .4f, .9f, 1.0f), color(1.0f, 1.0f, 1.0f, 1.0f)));
	std::shared_ptr<Ellipsoid>el = std::make_shared<Ellipsoid>(glm::vec3(-7.0f, 2.0f, -15.0f), Material(color(.4f, .2f, .7f, 1.0f), color(1.0f, 1.0f, 1.0f, 1.0f)), 1.5, 1.0, 2.0);

	std::shared_ptr<Plane> plane = std::make_shared<Plane>(glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), Material(color(.6f, .6f, 1.0f, 1.0f), color(1.0f, 1.0f, 1.0f, 1.0f)));
	std::vector<glm::vec3> polyPoints;
	polyPoints.push_back(glm::vec3(5.0f, 0.0f, -10.0f));
	polyPoints.push_back(glm::vec3(8.0f, 3.0f, -10.0f));
	polyPoints.push_back(glm::vec3(5.0f, 5.0f, -11.0f));
	std::shared_ptr<Poly> poly = std::make_shared<Poly>(polyPoints, Material(color(.4f, .4f, .9f, 1.0f), color(1.0f, 1.0f, 1.0f, 1.0f)));

	//rayTrace.setRecursionDepth(1);

	// Add objects to vector of objects in the scene
	surfaces.push_back(redBall);
	surfaces.push_back(greenBall);
	surfaces.push_back(blueBall);
	surfaces.push_back(plane);
	surfaces.push_back(poly);
	surfaces.push_back(el);

	// Create light sources
	std::shared_ptr<LightSource> ambientLight = std::make_shared<LightSource>(color(0.15, 0.15, 0.15, 1.0));
	std::shared_ptr<PositionalLight> lightPos = std::make_shared<PositionalLight>(glm::vec3(5, 3, -9), glm::vec4(1, 1, 1, 1));
	std::shared_ptr<DirectionalLight>  dirLight = std::make_shared<DirectionalLight>(glm::vec3(-1, 0, 0), glm::vec4(.6, .6, .6, 1));

	// Add light sources to vector of light sources
	lights.push_back(lightPos);
	lights.push_back(ambientLight);
	lights.push_back(dirLight);
}


// Register as the "idle" function to have the screen continously
// repainted. Due to software rendering, the frame rate will not
// be fast enough to support motion simulation
static void animate()  
{
	glutPostRedisplay();

} // end animate


int main(int argc, char** argv)
{
	// freeGlut and Window initialization ***********************

    // Pass any applicable command line arguments to GLUT. These arguments
	// are platform dependent.
    glutInit(&argc, argv);

	// Set the initial display mode.
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	// Set the initial window size
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Create a window using a string and make it the current window.
	GLuint world_Window = glutCreateWindow("Ray Trace");

	// Indicate to GLUT that the flow of control should return to the program after
	// the window is closed and the GLUTmain loop is exited.
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// Request that the window be made full screen
	//glutFullScreenToggle();

	// Set red, green, blue, and alpha to which the color buffer is cleared.
	frameBuffer.setClearColor(color(0.784, 0.784, 1.0, 1.0));

	// Setting up the Raytracer
	rayTrace.setDefaultColor(color(0, 0, 0, 1.0));

	// Callback for window redisplay
	glutDisplayFunc(RenderSceneCB);		
	glutReshapeFunc(ResizeCB);
	glutKeyboardFunc(KeyboardCB);
	glutSpecialFunc(SpecialKeysCB);

	buildScene();

	// Enter the GLUT main loop. Control will not return until the window is closed.
	glutMainLoop();

	// To keep the console open on shutdown, start the project with Ctrl+F5 instead of just F5.

	return 0;

} // end main