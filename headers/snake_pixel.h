#include <queue>

#include "pixel.h"

#ifndef SNAKE_PIXEL_H // include guard
#define SNAKE_PIXEL_H

class SnakePixel : public Pixel 
{
private:
    sf::Vector2i direction = sf::Vector2i(-1, 0);
    sf::Vector2i newDirection = sf::Vector2i(-1, 0);
    bool isHead=false;
    static int s_snakeLen;
    static SnakePixel s_snake[HRZ_PIXEL_COUNT*VRT_PIXEL_COUNT];

public:
    void markAsHead();
    SnakePixel();
    SnakePixel(sf::Vector2i direct);
    void move();
    void setNewDirection(sf::Vector2i newDirect);
    sf::Vector2i getDirection();
    static int s_getSnakeLen();
    static void s_cleanLen();
    static SnakePixel* s_getSnake();
    static SnakePixel s_getHead();
    static SnakePixel& s_getTail();
    static bool isOnSnake(Pixel pixel);
    static void createInitial();
};

#endif /* SNAKE_PIXEL_H */