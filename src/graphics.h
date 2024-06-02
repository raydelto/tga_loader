#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;
constexpr int TOTAL_PIXELS = SCREEN_WIDTH * SCREEN_HEIGHT;
constexpr int BOX_X_SIZE = 32;
constexpr int BOX_Y_SIZE = 32;

void drawPixel(SDL_Surface *surface, int x, int y, int color);
void clearSreen(SDL_Surface *surface);
