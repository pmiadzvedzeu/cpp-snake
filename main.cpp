#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define WINDOW_HEIGHT               800
#define WINDOW_WIDTH                1200
#define PIXEL_SIZE                  20
#define HRZ_PIXEL_COUNT             (WINDOW_WIDTH/PIXEL_SIZE)
#define VRT_PIXEL_COUNT             (WINDOW_HEIGHT/PIXEL_SIZE)
#define PIXEL_BORDER_THICKNESS      1
#define DEF_SNAKE_LEN               3

class Pixel : public sf::RectangleShape 
{
public:
    Pixel()
    {
        setSize(sf::Vector2f(16, 16));
        setOutlineThickness(PIXEL_BORDER_THICKNESS);
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
    }

private:
    sf::Vector2f direction = sf::Vector2f(-PIXEL_SIZE, 0);
    static int speed;
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

    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
    BorderSquare borders[2 * (HRZ_PIXEL_COUNT+VRT_PIXEL_COUNT)];
    SnakePixel snake[DEF_SNAKE_LEN];
    Food food = Food();
    for (int i = 0; i < DEF_SNAKE_LEN; i++)
    {
        snake[i].setPosition(WINDOW_WIDTH/2 + i * PIXEL_SIZE + PIXEL_BORDER_THICKNESS, WINDOW_HEIGHT/2 + PIXEL_BORDER_THICKNESS);
    }
    
    
    for(int i=0; i<HRZ_PIXEL_COUNT; i++)
    {
        borders[HRZ_PIXEL_COUNT+i].setPosition(PIXEL_BORDER_THICKNESS + PIXEL_SIZE*i, WINDOW_HEIGHT - PIXEL_SIZE + PIXEL_BORDER_THICKNESS);
        borders[i].setPosition(PIXEL_BORDER_THICKNESS + PIXEL_SIZE*i, PIXEL_BORDER_THICKNESS);
    }

    for(int i=0; i<VRT_PIXEL_COUNT; i++)
    {
        borders[2*HRZ_PIXEL_COUNT + VRT_PIXEL_COUNT+i].setPosition(WINDOW_WIDTH - PIXEL_SIZE + PIXEL_BORDER_THICKNESS, PIXEL_BORDER_THICKNESS + PIXEL_SIZE*i);
        borders[2*HRZ_PIXEL_COUNT + i].setPosition(PIXEL_BORDER_THICKNESS, PIXEL_BORDER_THICKNESS + PIXEL_SIZE*i);
    }
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        for(int i=0; i < 2*(HRZ_PIXEL_COUNT+VRT_PIXEL_COUNT); i++)
        {
            window.draw(borders[i]);
        }
        
        for (size_t i = 0; i < DEF_SNAKE_LEN; i++)
        {
            snake[i].move();
            window.draw(snake[i]);
        }

        food.setPosition((rand() % HRZ_PIXEL_COUNT)*PIXEL_SIZE + PIXEL_BORDER_THICKNESS, (rand() % VRT_PIXEL_COUNT + 1)*PIXEL_SIZE + PIXEL_BORDER_THICKNESS);
        window.draw(food);

        window.display();

        sleep_for(nanoseconds(10));
        sleep_until(system_clock::now() + milliseconds(1000));
    }
    return 0;
}