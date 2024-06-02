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

bool Render()
{
    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_q:
                    quit = true;
                    break;
                default:
                    break;
                }
            }
        }
        clearSreen(surface);

        auto start = SDL_GetTicks();

        // Do update

        auto end = SDL_GetTicks();
        SDL_UpdateWindowSurface(window);
        SDL_Delay(16 - (start - end));
    }

    SDL_Quit();
    return true;
}

int main()
{
    ubyte *data;
    unsigned int dataLength;

    std::cout << "Execution started." << std::endl;
    LoadTga("img/female.tga", data, dataLength);
    BGRtoRGB(data, dataLength);
    if (!InitSDL())
    {
        std::cerr << "Error while initializing SDL" << std::endl;
    }
    Render();
    free(data);
    std::cout << "Execution ended." << std::endl;
    return 0;
}