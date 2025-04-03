#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "graphics.h"


//Dibuja el primer pixel y calcula la orientación de la imagen a partir de ese offset
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

//Limpia la pantalla
void clearSreen(SDL_Surface *surface)
{
	unsigned int *pixels;
	pixels = (unsigned int *)surface->pixels;
	memset(pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
}
