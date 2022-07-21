#include "pixel.h"

#ifndef BORDER_PIXEL_H // include guard
#define BORDER_PIXEL_H

class BorderPixel : public Pixel 
{
    private:
    static const int c_bordersCount = 2 * (HRZ_PIXEL_COUNT+VRT_PIXEL_COUNT);
    static BorderPixel s_borders[BorderPixel::c_bordersCount];

    public:
    BorderPixel();
    static void s_createBorders();
    static BorderPixel* s_getBorders();
};

#endif /* BORDER_PIXEL_H */