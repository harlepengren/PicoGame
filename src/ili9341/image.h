#include <stdio.h>
#include <stdlib.h>

class Image{
    private:
        uint16_t* palette;
        uint16_t num_colors;
        uint8_t* image;
        FILE* fp;
        uint32_t image_position;
        uint16_t height;
        uint16_t width;
        uint offset;

    public:
        ~Image();
        void PrepareImage(const char* filename);
        void ImageBegin();
        bool EndOfFile();
        uint8_t ReadByte();
};