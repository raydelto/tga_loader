#include <iostream>
#include "tga_loader.h"
#include <SDL2/SDL.h>
#include "graphics.h"

SDL_Window *window = nullptr;
SDL_Surface *surface = nullptr;

bool InitSDL()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Simple renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);
    return window && surface;
}

int main()
{
    ubyte *data;
    unsigned int dataLength;

    std::cout << "Execution started." << std::endl;
    LoadTga("img/female.tga", data, dataLength);
    BGRtoRGB(data, dataLength);
    free(data);
    std::cout << "Execution ended." << std::endl;
    return 0;
}