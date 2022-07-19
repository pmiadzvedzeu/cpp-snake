#include "headers/snake_pixel.h"

void SnakePixel::markAsHead() {
    isHead = true;
    setFillColor(sf::Color::Yellow);
}

SnakePixel::SnakePixel()
{
    setOutlineColor(sf::Color::White);
    setFillColor(sf::Color::Red);
}

SnakePixel::SnakePixel(sf::Vector2i direct)
{
    setOutlineColor(sf::Color::White);
    setFillColor(sf::Color::Red);
    direction = newDirection = direct;
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

sf::Vector2i SnakePixel::getDirection() {return direction;}