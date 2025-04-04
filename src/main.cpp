#include <iostream>
#include "tga_loader.h"
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "graphics.h"

SDL_Window *window = nullptr;
SDL_Surface *surface = nullptr;
ubyte *data;

//prepare the window and initialize SDL
bool InitSDL()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Simple renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);
    return window && surface;
}

//draw image on screen
void LoadData(ubyte *myData)
{

    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            unsigned char *color = new unsigned char[4];
            color[0] = *myData;
            myData++;
            color[1] = *myData;
            myData++;
            color[2] = *myData;
            myData++;
            color[3] = 0;

            unsigned int *iColor = (unsigned int *)color;
            drawPixel(surface, j, i, *iColor);
            //delete[] iColor;
            delete[] color;
        }
    }
}

//visual test by drawin the whole screen in blue.
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
            delete[] color;
        }
    }
}

//bool to manage the programs execution, events and image rendering
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
        SDL_Delay(16 - (start - end));
    }

    SDL_Quit();
    return true;
}

//general program flow
int main()
{
    unsigned int dataLength;
    
    std::cout << "Execution started." << std::endl;
    LoadTga("img/female.tga", data, dataLength);
    //FlipHorizontally(data, width, height, bpp);
    // BGRtoRGB(data, dataLength);
    if (!InitSDL())
    {
        std::cerr << "Error while initializing SDL" << std::endl;
    }
    // BufferTest();
    Render();
    free(data);
    std::cout << "Execution ended." << std::endl;
    return 0;
}