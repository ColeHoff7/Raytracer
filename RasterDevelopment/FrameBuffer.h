#pragma once

#include "BasicIncludesAndDefines.h"
extern color currentMaterial;

extern glm::vec4 eyePositionInWorldCoords;

extern color currentMaterial;

#define BYTES_PER_PIXEL 4

/**
* Structure to hold the width and height of the rendering window
*/
struct Window {
	int width;
	int height;
};

/**
* Class which controls memory that stores a color value for every pixel
* in a rendering window with a specified width and height. setBufferSize
* is used to match the size of the memory to the size of the window. 
* clearColorBuffer to the color that is specifed using setClearColor. 
* showColorBuffer copies the memory into the color buffer for display 
* by the graphics card.
*/
class FrameBuffer
{
public:

	/**
	* Constructor. Allocates memory for storing pixel values.
	*
	* @param width of the rendering window in pixels
	* @param height of the rendering window in pixels
	*/
	FrameBuffer(const int width, const int height);
	
	/**
	* Deallocates dynamically memory associated with the class.
	*/
	~FrameBuffer(void);

	/**
	* Sizes the color buffer to match the window size. Deallocates any 
	* memory that was previsouly allocated. 
	*
	* @param width of the rendering window in pixels
	* @param height of the rendering window in pixels
	*/
	void setFrameBufferSize(const int width, const int height);

	/**
	* Sets the color to which the window will be cleared. Does NOT
	* actually clear the window
	*/
	void setClearColor( const color & clearColor );

	/**
	* Clears the window to the clear color.
	*/
	void clearColorAndDepthBuffers( );

	/**
	* Copies memory into frame buffer and updates the window
	* using an old OpenGL command.
	*/ 
	void showColorBuffer();

	/**
	* Returns the width of the rendering window in pixels
	* @ return width of the rendering window
	*/
	int getWindowWidth(){ return window.width;}

	/**
	* Returns the height of the rendering window in pixels
	* @ return height of the rendering window
	*/
	int getWindowHeight(){ return window.height;}

	/**
	* Sets an individual pixel value in the color buffer. Origin (0,0)
	* is the lower left hand corner of the window.
	*
	* @param x coordinate of the pixel.
	* @param y coordinate of the pixel.
	* @param color to which the pixel is to be set.
	*/
	void setPixel(const int x, const int y, const color & rgba);

	/**
	* Sets an individual pixel value in the color buffer. Origin (0,0)
	* is the lower left hand corner of the window.
	*
	* @param x coordinate of the pixel.
	* @param y coordinate of the pixel.
	* @param color to which the pixel is to be set.
	*/
	void processFragment(const float x, const float y, const color & rgba);

	/**
	* Sets an individual pixel value in the color buffer. Origin (0,0)
	* is the lower left hand corner of the window.
	*
	* @param x coordinate of the pixel.
	* @param y coordinate of the pixel.
	* @param color to which the pixel is to be set.
	*/
	void processFragment(const float x, const float y, const GLubyte rgba[]);

protected:

	/**
	* Set the depth value for a specified pixel.
	* @param x coordinate of the pixel.
	* @param y coordinate of the pixel.
	* @param depth to which the pixel is to be set.
	*/
	void setDepth(const float x, const float y, const float depth);

	/**
	* Set the depth value for a specified pixel.
	* @param x coordinate of the pixel.
	* @param y coordinate of the pixel.
	* @param depth to which the pixel is to be set.
	*/
	void setDepth(const int x, const int y, const float depth);

	/**
	* Returns the depth value for a specified pixel position.
	* @param x coordinate of the pixel.
	* @param y coordinate of the pixel.
	* @ return depth that is stored for the pixel position
	*/
	float getDepth(const int x, const int y);

	/**
	* Returns the depth value for a specified pixel position.
	* @param x coordinate of the pixel.
	* @param y coordinate of the pixel.
	* @ return depth that is stored for the pixel position
	*/
	float getDepth(const float x, const float y);

	/**
	* Struct that maintains the width and height of the rendering window
	*/
	Window window;

	/**
	* Color to which memory is cleared when clearColorBuffer is called.
	*/
	GLubyte clearColor[BYTES_PER_PIXEL];

	/**
	* Storage for red, green, blue, alpha color values 
	*/
	GLubyte* colorBuffer;

	/*
	* Storage for fragment depth values
	*/
	float* depthBuffer;
	
}; // end FrameBuffer class

