#include "pixel.h"

#ifndef FOOD_PIXEL_H // include guard
#define FOOD_PIXEL_H

class Food : public Pixel 
{
public:
    Food();

    void relocate();
};

#endif /* FOOD_PIXEL_H */