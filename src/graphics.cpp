#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "graphics.h"


// Draws the first pixel and calculates the image orientation based on that offset
void drawPixel(SDL_Surface *surface, int x, int y, unsigned int color)
{
	unsigned int offset = SCREEN_WIDTH * y + x;
	if (offset > TOTAL_PIXELS)
	{
		return;
	}

	unsigned int *pixels;
	pixels = (unsigned int *)surface->pixels;
	pixels[offset] = color;
}

// Clears the screen
void clearSreen(SDL_Surface *surface)
{
	unsigned int *pixels;
	pixels = (unsigned int *)surface->pixels;
	memset(pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
}
