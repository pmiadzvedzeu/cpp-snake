#include "config"
#include "headers/pixel.h"

Pixel::Pixel()
{
    setSize(sf::Vector2f(PIXEL_SIZE - 2*PIXEL_BORDER_THICKNESS, PIXEL_SIZE - 2*PIXEL_BORDER_THICKNESS));
    setOutlineThickness(1);
}

void Pixel::setPixelPosition(int x, int y)
{
    pixelX = x;
    pixelY = y;
    pixelPosition = sf::Vector2i(x, y);
    setPosition(pixelX*PIXEL_SIZE + PIXEL_BORDER_THICKNESS, pixelY*PIXEL_SIZE + PIXEL_BORDER_THICKNESS);
}

void Pixel::setPixelPosition(sf::Vector2i vector)
{
    setPixelPosition(vector.x, vector.y);
}

sf::Vector2i Pixel::getPixelPosition() {return pixelPosition;}

bool Pixel::isMeet(Pixel anotherPixel){
    return getPosition().x == anotherPixel.getPosition().x && getPosition().y == anotherPixel.getPosition().y;
}