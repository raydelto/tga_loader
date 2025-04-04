#pragma once

#include "types.h"

bool BGRtoRGB(ubyte *&data, const unsigned int dataLength);
bool BGRtoBGRA(ubyte *&data, const unsigned int dataLength);

bool LoadTga(const char *filename, ubyte *&data, unsigned int &dataLength, unsigned int &width, unsigned int &height, unsigned int &bpp);
void FlipHorizontally(ubyte *&data, unsigned int width, unsigned int height, unsigned int bpp);
