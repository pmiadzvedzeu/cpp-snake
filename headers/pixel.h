#include "../config"
#include <SFML/Graphics.hpp>

#ifndef PIXEL_H // include guard
#define PIXEL_H

class Pixel : public sf::RectangleShape 
{
private:
    int pixelX;
    int pixelY;
    sf::Vector2i pixelPosition;

public:
    Pixel();

    void setPixelPosition(int x, int y);

    void setPixelPosition(sf::Vector2i vector);

    sf::Vector2i getPixelPosition();

    bool isMeet(Pixel anotherPixel);
};

#endif /* PIXEL_H */