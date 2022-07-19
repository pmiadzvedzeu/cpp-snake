#include <chrono>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <iostream>

#include "headers/border_pixel.h"
#include "headers/snake_pixel.h"
#include "headers/food_pixel.h"

int main()
{
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds

    srand (time(NULL));

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "The Snake");

    int tailLen;
    std::queue<SnakePixel> snake;
    BorderPixel borders[2 * (HRZ_PIXEL_COUNT+VRT_PIXEL_COUNT)];
    Food food = Food();

    auto initialize = [&] () {
        tailLen = 0;
        std::queue<SnakePixel> empty;
        std::swap(snake, empty);
        for (int i = 0; i < DEF_SNAKE_LEN; i++)
        {
            SnakePixel snakePixel = SnakePixel();
            snakePixel.setPixelPosition(HRZ_PIXEL_COUNT/2 + i, VRT_PIXEL_COUNT/2);
            snake.push(snakePixel);
        }
        snake.front().markAsHead();
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
        food = Food();

        return 0;
    };

    initialize();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        for (size_t i = 0; i < 200; i++)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                snake.front().setNewDirection(sf::Vector2i(0, -1));

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                snake.front().setNewDirection(sf::Vector2i(0, 1));

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                snake.front().setNewDirection(sf::Vector2i(-1, 0));

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                snake.front().setNewDirection(sf::Vector2i(1, 0));

            sleep_for(nanoseconds(10));
            sleep_until(system_clock::now() + milliseconds(1));
        }
        
        window.clear();

        for(int i=0; i < 2*(HRZ_PIXEL_COUNT+VRT_PIXEL_COUNT); i++)
        {
            window.draw(borders[i]);
        }

        for (size_t i = 0; i < DEF_SNAKE_LEN+tailLen; i++)
        {
            snake.push(snake.front());
            snake.pop();
            if (i < DEF_SNAKE_LEN+tailLen - 1)
                snake.front().setNewDirection(snake.back().getDirection());
            snake.back().move();
            window.draw(snake.back());
        }
        window.draw(snake.front());

        if (food.isMeet(snake.front()))
        {
            food.relocate();
            SnakePixel tail = SnakePixel(snake.back().getDirection());
            tail.setPixelPosition(snake.back().getPixelPosition() - tail.getDirection());
            snake.push(tail);
            window.draw(snake.back());
            tailLen++;
        }

        window.draw(food);

        for (size_t i = 0; i < 2*(HRZ_PIXEL_COUNT+VRT_PIXEL_COUNT); i++)
        {
            if (borders[i].isMeet(snake.front()))
                initialize();
        }

        SnakePixel head = snake.front();
        for (size_t i = 0; i < DEF_SNAKE_LEN+tailLen; i++)
        {
            snake.push(snake.front());
            snake.pop();
            if (i != 0)
                if (snake.back().isMeet(head))
                    initialize();
        }

        window.display();
    }
    return 0;
}