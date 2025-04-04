#include <iostream>
#include <cstdio>
#include <utility>
#include "tga_loader.h"
#include <cstring>

constexpr int SIGNATURE_SIZE = 12;
constexpr int BITS_PER_BYTE = 8;

bool BGRtoRGB(ubyte *&data, const unsigned int dataLength)
{
    constexpr int RGB_LENGTH = 3;
    for (unsigned int i = 0; i < dataLength; i += RGB_LENGTH)
    {
        std::swap(data[i], data[i + 2]);
    }
    return true;
}

bool BGRtoBGRA(ubyte *&data, const unsigned int dataLength)
{
    constexpr int RGB_LENGTH = 3;
    for (unsigned int i = 0; i < dataLength; i += RGB_LENGTH)
    {
        std::swap(data[i], data[i + 2]);
    }
    return true;
}

bool LoadTga(const char *filename, ubyte *&data, unsigned int &dataLength, unsigned int &width, unsigned int &height, unsigned int &bpp)
{
    FILE *file = fopen(filename, "rb");

    if (!file)
    {
        std::cerr << "Could not open file " << filename << "." << std::endl;
        return false;
    }

    constexpr ubyte CORRECT_SIGNATURE[] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ubyte signature[SIGNATURE_SIZE];

    fread(signature, 1, SIGNATURE_SIZE, file);

    if (memcmp(signature, CORRECT_SIGNATURE, SIGNATURE_SIZE) != 0)
    {
        std::cerr << filename << " is an invalid TGA file." << std::endl;
        fclose(file);
        return false;
    }

    fread(&width, 1, sizeof(short), file);
    fread(&height, 1, sizeof(short), file);

    ubyte bpp_byte;
    fread(&bpp_byte, 1, 1, file);
    bpp = static_cast<unsigned int>(bpp_byte) / 8; // convert bits to bytes per pixel

    fseek(file, 1, SEEK_CUR); // skip image descriptor byte (1 byte)

    dataLength = width * height * bpp;
    data = (ubyte *)malloc(dataLength);

    if (!data)
    {
        std::cerr << "Could not allocate memory for the TGA image." << std::endl;
        fclose(file);
        return false;
    }
    else
    {
        std::cout << dataLength << " bytes allocated" << std::endl;
    }

    fread(data, 1, dataLength, file);
    fclose(file);
    return true;
}


void FlipHorizontally(ubyte *&data, unsigned int width, unsigned int height, unsigned int bpp)
{
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width / 2; ++x)
        {
            // Calcula las posiciones de los píxeles que se intercambiarán
            ubyte* left = data + (y * width + x) * bpp;
            ubyte* right = data + (y * width + (width - 1 - x)) * bpp;

            // Intercambia cada componente del píxel
            for (unsigned int i = 0; i < bpp; ++i)
            {
                std::swap(left[i], right[i]);
            }
        }
    }
}

