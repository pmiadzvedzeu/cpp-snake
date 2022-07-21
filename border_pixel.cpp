#include "headers/border_pixel.h"

BorderPixel::BorderPixel()
{
    setOutlineColor(sf::Color::Cyan);
    setFillColor(sf::Color::White);
}

void BorderPixel::s_createBorders()
{
    for(int i=0; i<HRZ_PIXEL_COUNT; i++)
    {
        BorderPixel::s_borders[HRZ_PIXEL_COUNT+i].setPixelPosition(i, VRT_PIXEL_COUNT - 1);
        BorderPixel::s_borders[i].setPixelPosition(i, 0);
    }
    for(int i=0; i<VRT_PIXEL_COUNT; i++)
    {
        BorderPixel::s_borders[2*HRZ_PIXEL_COUNT + VRT_PIXEL_COUNT+i].setPixelPosition(HRZ_PIXEL_COUNT-1, i);
        BorderPixel::s_borders[2*HRZ_PIXEL_COUNT + i].setPixelPosition(0, i);
    }
}

BorderPixel* BorderPixel::s_getBorders()
{
    return BorderPixel::s_borders;
}

BorderPixel BorderPixel::s_borders[BorderPixel::c_bordersCount];