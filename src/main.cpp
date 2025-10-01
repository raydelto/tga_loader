#include <iostream>
#include "tga_loader.h"
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include "graphics.h"

SDL_Window *window = nullptr;
SDL_Surface *surface = nullptr;
ubyte *data;

bool InitSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }
    window = SDL_CreateWindow("Simple renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }
    surface = SDL_GetWindowSurface(window);
    if (!surface)
    {
        std::cerr << "SDL_GetWindowSurface Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void LoadData(ubyte *myData)
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            unsigned char color[4];
            color[0] = *myData++;
            color[1] = *myData++;
            color[2] = *myData++;
            color[3] = 0;

            unsigned int *iColor = (unsigned int *)color;
            drawPixel(surface, j, i, *iColor);
        }
    }
}
void BufferTest()
{
    unsigned char *color = new unsigned char[4];
    color[0] = 0;
    color[1] = 0;
    color[2] = 255;
    color[3] = 255;

    unsigned int *iColor = (unsigned int *)color;

    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            drawPixel(surface, j, i, *iColor);
            // delete color;
        }
    }
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

        LoadData(data);

        auto end = SDL_GetTicks();
        SDL_UpdateWindowSurface(window);
        auto elapsed = end - start;
        if (elapsed < 16)
        {
            SDL_Delay(16 - elapsed);
        }
    }

    SDL_Quit();
    return true;
}

int main()
{
    unsigned int dataLength;

    std::cout << "Execution started." << std::endl;
    if (!LoadTga("img/female.tga", data, dataLength))
    {
        std::cerr << "Error loading TGA file" << std::endl;
        return 1;
    }
    // BGRtoRGB(data, dataLength);
    if (!InitSDL())
    {
        std::cerr << "Error while initializing SDL" << std::endl;
        free(data);
        return 1;
    }
    // BufferTest();
    Render();
    free(data);
    std::cout << "Execution ended." << std::endl;
    return 0;
}
