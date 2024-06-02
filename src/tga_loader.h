#pragma once

using ubyte = unsigned char;

bool BGRtoRGB(ubyte *&data, const unsigned int dataLength);
bool BGRtoBGRA(ubyte *&data, const unsigned int dataLength);

bool LoadTga(const char *filename, ubyte *&data, unsigned int &dataLength);