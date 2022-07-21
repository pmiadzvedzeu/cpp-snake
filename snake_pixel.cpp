#include <iostream>

#include "headers/snake_pixel.h"

void SnakePixel::markAsHead() {
    isHead = true;
    setFillColor(sf::Color::Yellow);
}

SnakePixel::SnakePixel()
{
    setOutlineColor(sf::Color::White);
    setFillColor(sf::Color::Red);
    if (!SnakePixel::s_snakeLen)
        markAsHead();
    SnakePixel::s_snake[s_snakeLen] = *this;
    SnakePixel::s_snakeLen++;
}

SnakePixel::SnakePixel(sf::Vector2i direct)
{
    setOutlineColor(sf::Color::White);
    setFillColor(sf::Color::Red);
    direction = newDirection = direct;
    SnakePixel::s_snake[s_snakeLen] = *this;
    SnakePixel::s_snakeLen++;
}

void SnakePixel::move()
{
    const sf::Vector2i currntPosition = getPixelPosition();
    const sf::Vector2i currentDirection = direction;

    setPixelPosition(currntPosition + currentDirection);
    direction = newDirection;
}

void SnakePixel::setNewDirection(sf::Vector2i newDirect)
{
    newDirection = newDirect;
    if (isHead)
        direction = newDirection;
}

bool SnakePixel::isOnSnake(Pixel pixel)
{
    for (int i = 0; i < SnakePixel::s_snakeLen; i++)
        if (SnakePixel::s_snake[i].isMeet(pixel))
            return true;
    
    return false;
}

void SnakePixel::createInitial()
{
    SnakePixel::s_cleanLen();
    for (int i = 0; i < DEF_SNAKE_LEN; i++)
    {
        SnakePixel();
        SnakePixel::s_getSnake()[i].setPixelPosition(HRZ_PIXEL_COUNT/2 + i, VRT_PIXEL_COUNT/2);
    }
}

sf::Vector2i    SnakePixel::getDirection()      {return direction;}
SnakePixel*     SnakePixel::s_getSnake()        {return s_snake;}
int             SnakePixel::s_getSnakeLen()     {return SnakePixel::s_snakeLen;}
SnakePixel      SnakePixel::s_getHead()         {return SnakePixel::s_snake[0];}
SnakePixel&     SnakePixel::s_getTail()         {return (SnakePixel::s_snake[SnakePixel::s_snakeLen-1]);}

void            SnakePixel::s_cleanLen()        {SnakePixel::s_snakeLen = 0;}

int SnakePixel::s_snakeLen;
SnakePixel SnakePixel::s_snake[HRZ_PIXEL_COUNT*VRT_PIXEL_COUNT];