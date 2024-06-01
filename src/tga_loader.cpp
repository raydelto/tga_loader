#include <iostream>
#include <cstdio>
#include <utility>
#include "tga_loader.h"

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

bool LoadTga(const char *filename, ubyte *&data, unsigned int &dataLength)
{
    FILE *file = fopen(filename, "rb");

    if (!file)
    {
        std::cerr << "Could not open file" << filename << "." << std::endl;
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

    unsigned short width;
    unsigned short height;
    ubyte bpp; // bytes per pixel

    fread(&width, 1, sizeof(short), file);
    fread(&height, 1, sizeof(short), file);
    fread(&bpp, 1, sizeof(ubyte), file);

    bpp /= BITS_PER_BYTE;

    printf("%d\n", bpp);
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
