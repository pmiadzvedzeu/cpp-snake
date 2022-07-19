#include "headers/food_pixel.h"

Food::Food()
{
    setOutlineColor(sf::Color::White);
    setFillColor(sf::Color::White);
    relocate();
}

void Food::relocate(){
    setPixelPosition(rand() % (HRZ_PIXEL_COUNT - 2) + 1, rand() % (VRT_PIXEL_COUNT - 2) + 1);
}
