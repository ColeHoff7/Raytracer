#include "FrameBuffer.h"

/**
* Constructor. Allocates memory for storing pixel values.
*/
FrameBuffer::FrameBuffer( const int width, const int height)
{
	setFrameBufferSize(width, height);

} // end FrameBuffer constructor


/**
* Deallocates dynamically memory associated with the class.
*/
FrameBuffer::~FrameBuffer(void)
{
	// Free the memory associated with the color buffer
	delete [] colorBuffer;
	delete[] depthBuffer;

} // end FrameBuffer destructor


/**
* Sizes the color buffer to match the window size. Deallocates any
* memory that was previsouly allocated.
*/
void FrameBuffer::setFrameBufferSize( const int width, const int height) {

	// Save the dimensions of the window
	window.width = width;
    window.height = height;

	// Set pixel storage modes. 
	// (https://www.opengl.org/archives/resources/features/KilgardTechniques/oglpitfall/)
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);

	// Free the memory previously associated with the color buffer
	delete [] colorBuffer;
	delete[] depthBuffer;

	// Allocate the color buffer to match the size of the window
	colorBuffer = new GLubyte[width*BYTES_PER_PIXEL*height];
	depthBuffer = new float[width*height];

} // end setFrameBufferSize


/**
* Sets the color to which the window will be cleared. Does NOT
* actually clear the window
*/
void FrameBuffer::setClearColor( const color & clear ) {
	
	color clampedColor = glm::clamp(clear, 0.0f, 1.0f);

	clearColor[0] = (GLubyte)(clampedColor.r * 255.0f);
	clearColor[1] =	(GLubyte)(clampedColor.g * 255.0f);
	clearColor[2] =	(GLubyte)(clampedColor.b * 255.0f);
	clearColor[3] =	(GLubyte)(clampedColor.a * 255.0f);

} // end setClearColor


/**
* Clears the window to the clear color.
*/
void FrameBuffer::clearColorAndDepthBuffers() {

	for(int y = 0; y < window.height ; ++y) {
		for(int x = 0; x < window.width; ++x) {

			std::memcpy( colorBuffer + BYTES_PER_PIXEL * (x + y * window.width ), 
						 clearColor,  BYTES_PER_PIXEL );
			depthBuffer[y * window.width + x] = 1.0f;
		
		}
	}

} // end clearFrameBuffer


/**
* Copies memory into frame buffer and updates the window
* using an OpenGL command.
*/
void FrameBuffer::showColorBuffer()
{
	// Insure raster position is lower left hand corner of the window. (OpenGL command)
	glRasterPos2d(-1, -1);

	// Copy color buffer to raster (OpenGL command)
	glDrawPixels( window.width, window.height, GL_RGBA, GL_UNSIGNED_BYTE, colorBuffer );
	
	// Flush all drawing commands and swapbuffers (Glut command)
	glutSwapBuffers();

} // end showFrameBuffer


/**
* Sets an individual pixel value in the color buffer. Origin (0,0)
* is the lower left hand corner of the window.
*/
void FrameBuffer::setPixel(const int x, const int y, const color & rgba) {

	if (x >= 0 && x < window.width && y >= 0 && y < window.height) {

		// Clamp the color components to the range [0 1]
		color clampedColor = glm::clamp(rgba, 0.0f, 1.0f);

		// Convert floating point color components to integer (byte) values
		GLubyte c[] = { (GLubyte)(clampedColor.r * 255),
						(GLubyte)(clampedColor.g * 255),
						(GLubyte)(clampedColor.b * 255),
						(GLubyte)(clampedColor.a * 255) };

		// Set the color of the pixel by copying the color components into the color buffer
		std::memcpy(colorBuffer + BYTES_PER_PIXEL * (x + y * window.width), c, BYTES_PER_PIXEL);
	}

} // end setPixel




/**
* Set the depth value for a specified pixel.
*/
void FrameBuffer::setDepth(const float x, const float y, const float depth) {
	
	setDepth((int)(x + 0.5f), (int)(y + 0.5f), depth);

} // end setDepth

/**
* Set the depth value for a specified pixel.
*/
void FrameBuffer::setDepth(const int x, const int y, const float depth) {
	
	depthBuffer[y * window.width + x] = depth;

} // end setDepth

/**
* Returns the depth value for a specified pixel position.
*/
float FrameBuffer::getDepth(const int x, const int y) {

	return depthBuffer[y * window.width + x];

} // end getDepth

/**
* Returns the depth value for a specified pixel position.
*/
float FrameBuffer::getDepth(const float x, const float y) {

	return getDepth((int)(x + 0.5f), (int)(y + 0.5f));

} // end getDepth
