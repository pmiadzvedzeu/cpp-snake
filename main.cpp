#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <queue>

#define WINDOW_HEIGHT               800
#define WINDOW_WIDTH                1200
#define PIXEL_SIZE                  20
#define HRZ_PIXEL_COUNT             (WINDOW_WIDTH/PIXEL_SIZE)
#define VRT_PIXEL_COUNT             (WINDOW_HEIGHT/PIXEL_SIZE)
#define PIXEL_BORDER_THICKNESS      2
#define DEF_SNAKE_LEN               3


class Pixel : public sf::RectangleShape 
{
private:
    int pixelX;
    int pixelY;

public:
    Pixel()
    {
        setSize(sf::Vector2f(PIXEL_SIZE - 2*PIXEL_BORDER_THICKNESS, PIXEL_SIZE - 2*PIXEL_BORDER_THICKNESS));
        setOutlineThickness(1);
    }

    void setPixelPosition(int x, int y)
    {
        pixelX = x;
        pixelY = y;
        setPosition(pixelX*PIXEL_SIZE + PIXEL_BORDER_THICKNESS, pixelY*PIXEL_SIZE + PIXEL_BORDER_THICKNESS);
    }
};


class BorderSquare : public Pixel 
{
public:
    BorderSquare()
    {
        setOutlineColor(sf::Color::Cyan);
        setFillColor(sf::Color::White);
    }
};

class SnakePixel : public Pixel 
{
public:
    sf::Vector2f direction = sf::Vector2f(-PIXEL_SIZE, 0);
    sf::Vector2f newDirection = sf::Vector2f(-PIXEL_SIZE, 0);

    SnakePixel()
    {
        setOutlineColor(sf::Color::White);
        setFillColor(sf::Color::Red);
    }

    void move()
    {
        const sf::Vector2f currntPosition = getPosition();
        const sf::Vector2f currentDirection = direction;

        setPosition(currntPosition + currentDirection);

        if (newDirection!=direction)
        {
            direction = newDirection;
        }
    }
};

class Food : public Pixel 
{
public:
    Food()
    {
        setOutlineColor(sf::Color::White);
        setFillColor(sf::Color::White);
    }
};

int main()
{
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds

    srand (time(NULL));

    sf::RenderWindow window(sf::VideoMode(1200, 800), "The Snake");

    std::queue <SnakePixel> snake;
    for (int i = 0; i < DEF_SNAKE_LEN; i++)
    {
        SnakePixel snakePixel = SnakePixel();
        snakePixel.setPixelPosition(HRZ_PIXEL_COUNT/2 + i, VRT_PIXEL_COUNT/2);
        snake.push(snakePixel);
    }
    
    BorderSquare borders[2 * (HRZ_PIXEL_COUNT+VRT_PIXEL_COUNT)];
    for(int i=0; i<HRZ_PIXEL_COUNT; i++)
    {
        borders[HRZ_PIXEL_COUNT+i].setPixelPosition(i, VRT_PIXEL_COUNT - 1);
        borders[i].setPixelPosition(i, 0);
    }
    for(int i=0; i<VRT_PIXEL_COUNT; i++)
    {
        borders[2*HRZ_PIXEL_COUNT + VRT_PIXEL_COUNT+i].setPixelPosition(HRZ_PIXEL_COUNT-1, i);
        borders[2*HRZ_PIXEL_COUNT + i].setPixelPosition(0, i);
    }

    Food food = Food();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        for (size_t i = 0; i < 1000; i++)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                snake.front().direction = sf::Vector2f(0, -PIXEL_SIZE);
                snake.front().newDirection = sf::Vector2f(0, -PIXEL_SIZE);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                snake.front().direction = sf::Vector2f(0, PIXEL_SIZE);
                snake.front().newDirection = sf::Vector2f(0, PIXEL_SIZE);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                snake.front().direction = sf::Vector2f(-PIXEL_SIZE, 0);
                snake.front().newDirection = sf::Vector2f(-PIXEL_SIZE, 0);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                snake.front().direction = sf::Vector2f(PIXEL_SIZE, 0);
                snake.front().newDirection = sf::Vector2f(PIXEL_SIZE, 0);
            }

            sleep_for(nanoseconds(10));
            sleep_until(system_clock::now() + milliseconds(1));
        }
        
        window.clear();

        for(int i=0; i < 2*(HRZ_PIXEL_COUNT+VRT_PIXEL_COUNT); i++)
        {
            window.draw(borders[i]);
        }

        for (size_t i = 0; i < DEF_SNAKE_LEN; i++)
        {
            snake.push(snake.front());
            snake.pop();
            if (i < DEF_SNAKE_LEN - 1)
            {
                snake.front().newDirection = snake.back().direction;
            }
            snake.back().move();
            window.draw(snake.back());
        }

        food.setPixelPosition(rand() % HRZ_PIXEL_COUNT, rand() % (VRT_PIXEL_COUNT));
        window.draw(food);

        window.display();
    }
    return 0;
}