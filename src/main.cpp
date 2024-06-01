#include <iostream>
#include "tga_loader.h"

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