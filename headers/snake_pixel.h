#include "pixel.h"

#ifndef SNAKE_PIXEL_H // include guard
#define SNAKE_PIXEL_H

class SnakePixel : public Pixel 
{
private:
    sf::Vector2i direction = sf::Vector2i(-1, 0);
    sf::Vector2i newDirection = sf::Vector2i(-1, 0);
    bool isHead=false;

public:
    void markAsHead();

    SnakePixel();

    SnakePixel(sf::Vector2i direct);

    void move();

    void setNewDirection(sf::Vector2i newDirect);

    sf::Vector2i getDirection();
};

#endif /* SNAKE_PIXEL_H */