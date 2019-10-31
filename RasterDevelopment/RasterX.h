#pragma once

#include "BasicIncludesAndDefines.h"

#define BYTES_PER_PIXEL 4

// Structure to hold the width and height of the rendering window
struct Window {
	int width;
	int height;
};


void setPixel(int x, int y, const color & rgba);

void setPixel(float x, float y, const color & rgba);

// Set an individual pixel to a specified color
void setPixel(int x, int y, const GLubyte rgba[]);

// Set an individual pixel to a specified color
void setPixel(float x, float y, const GLubyte rgba[]);

// Size the color buffer to match the window size.
void setColorBufferSize(int width, int height);

// Sets the color to which the window will be cleared
void setClearColor( const color & clearColor );

// Clears the window to a specified color
void clearColorBuffer( );

// Copies memory into frame buffer and updates the window
void showColorBuffer();

extern Window window;



