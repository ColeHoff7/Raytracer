#include "Raster.h"

Window window;

GLubyte clearColor[BYTES_PER_PIXEL];

//color clearColor;

// Storage for red, green, blue, alpha color values 
GLubyte* colorBuffer;

//color* colorBuffer;

void setPixel(float x, float y, const color & rgba) {

	GLubyte c[] = { (GLubyte)(rgba.r * 255.0f), 
					(GLubyte)(rgba.g * 255.0f), 
					(GLubyte)(rgba.b * 255.0f),
					(GLubyte)(rgba.a * 255.0f) };

	setPixel( x, y, c );

} // end

void setPixel(int x, int y, const GLubyte rgba[]) {

	if(x >= 0 && x < window.width && y >= 0 && y < window.height ) {

			std::memcpy( colorBuffer + BYTES_PER_PIXEL * (x + y * window.width ), rgba,  BYTES_PER_PIXEL );
	}

} // end

void setPixel(float x, float y, const GLubyte rgba[]) {

	setPixel((int)(x + 0.5f), (int)(y + 0.5f), rgba);

} // end

void setPixel(int x, int y, const color & rgba) {

	GLubyte c[] = { (GLubyte)(rgba.r * 255.0f), 
					(GLubyte)(rgba.g * 255.0f), 
					(GLubyte)(rgba.b * 255.0f),
					(GLubyte)(rgba.a * 255.0f) };

	setPixel(x, y, c);

} // end

void setColorBufferSize(int width, int height) {

	// Save the dimensions of the window
	window.width = width;
    window.height = height;

	// Set pixel storage modes. (https://www.opengl.org/archives/resources/features/KilgardTechniques/oglpitfall/)
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);

	// Free the memory previously associated with the color buffer
	delete [] colorBuffer;

	// Allocate the color buffer to match the size of the window
	colorBuffer = new GLubyte[width*BYTES_PER_PIXEL*height];

	//colorBuffer = new color[width*height];

} // end


// Sets the color to which the window will be cleared
void setClearColor( const color & clear ) {

	clearColor[0] = (GLubyte)(clear.r * 255);
	clearColor[1] =	(GLubyte)(clear.g * 255);
	clearColor[2] =	(GLubyte)(clear.b * 255);
	clearColor[3] =	(GLubyte)(clear.a * 255);

	//clearColor = clear;

} // end

void clearColorBuffer( ) {

	for(int y = 0; y < window.height ; ++y) {
		for(int x = 0; x < window.width; ++x) {

			std::memcpy( colorBuffer + BYTES_PER_PIXEL * (x + y * window.width ), clearColor,  BYTES_PER_PIXEL );

			//colorBuffer[x+y*window.width] = clearColor;
			
		}
	}

} // end 


void showColorBuffer()
{
	//glRasterPos2d(-1, -1);

	// Copy color buffer to raster 
	glDrawPixels( window.width, window.height, GL_RGBA, GL_UNSIGNED_BYTE, colorBuffer );

	//glDrawPixels( window.width, window.height, GL_RGBA, GL_FLOAT, colorBuffer );
	
	// Flush all drawing commands and swapbuffers
	glutSwapBuffers();

} // end 