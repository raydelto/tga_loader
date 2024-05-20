#include <iostream>
#include <cstdio>

using namespace std;
using ubyte = unsigned char;

constexpr int SIGNATURE_SIZE = 12;
constexpr int ATTRIBUTES_SIZE = 6;
constexpr int BITS_PER_BYTE = 8;

bool loadTga(const char *filename, ubyte *&data, unsigned int &dataLength)
{
    FILE *file = fopen(filename, "rb");

    if (!file)
    {
        cerr << "Could not open file" << filename << "." << endl;
        return false;
    }

    constexpr ubyte CORRECT_SIGNATURE[] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ubyte *attr;
    ubyte signature[SIGNATURE_SIZE];

    fread(signature, 1, SIGNATURE_SIZE, file);

    if (memcmp(signature, CORRECT_SIGNATURE, SIGNATURE_SIZE) != 0)
    {
        cerr << filename << " is an invalid TGA file." << endl;
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

    cout << "width = " << width << endl;
    cout << "height = " << height << endl;
    printf("%d\n", bpp);
    dataLength = width * height * bpp;
    data = (ubyte *)malloc(dataLength);
    if (!data)
    {
        cerr << "Could not allocate memory for the TGA image." << endl;
        fclose(file);
        return false;
    }
    else
    {
        cout << dataLength << " bytes allocated" << endl;
    }
    fread(data, 1, dataLength, file);

    fclose(file);
    return true;
}

int main()
{
    ubyte *data;
    unsigned int dataLength;

    cout << "Empty project" << endl;
    loadTga("img/female.tga", data, dataLength);
    free(data);
    cout << "exit" << endl;
    return 0;
}