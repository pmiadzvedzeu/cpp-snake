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

    BorderPixel borders[2 * (HRZ_PIXEL_COUNT+VRT_PIXEL_COUNT)];
    Food food = Food();

    auto initialize = [&] () {
        SnakePixel::s_cleanLen();
        for (int i = 0; i < DEF_SNAKE_LEN; i++)
        {
            SnakePixel();
            SnakePixel::s_getSnake()[i].setPixelPosition(HRZ_PIXEL_COUNT/2 + i, VRT_PIXEL_COUNT/2);
        }

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
        size_t one_step_time;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        for (one_step_time = 0; one_step_time < SPEED; one_step_time++)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                SnakePixel::s_getSnake()[0].setNewDirection(sf::Vector2i(0, -1));
                break;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                SnakePixel::s_getSnake()[0].setNewDirection(sf::Vector2i(0, 1));
                break;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                SnakePixel::s_getSnake()[0].setNewDirection(sf::Vector2i(-1, 0));
                break;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                SnakePixel::s_getSnake()[0].setNewDirection(sf::Vector2i(1, 0));
                break;
            }

            sleep_for(milliseconds(1));
        }

        sleep_until(system_clock::now() + milliseconds(SPEED - one_step_time));
        
        window.clear();

        for(int i=0; i < 2*(HRZ_PIXEL_COUNT+VRT_PIXEL_COUNT); i++)
        {
            window.draw(borders[i]);
        }

        for (size_t i = 0; i < SnakePixel::s_getSnakeLen(); i++)
        {
            if (i < SnakePixel::s_getSnakeLen() - 1)
                SnakePixel::s_getSnake()[i+1].setNewDirection(SnakePixel::s_getSnake()[i].getDirection());
            SnakePixel::s_getSnake()[i].move();
            window.draw(SnakePixel::s_getSnake()[i]);
        }

        if (food.isMeet(SnakePixel::s_getSnake()[0]))
        {
            SnakePixel oldTail = SnakePixel::s_getTail();
            food.relocate();
            SnakePixel(SnakePixel::s_getTail().getDirection());
            SnakePixel tail = SnakePixel::s_getTail();
            SnakePixel::s_getTail().setPixelPosition(oldTail.getPixelPosition() - tail.getDirection());
            window.draw(SnakePixel::s_getTail());
        }

        window.draw(food);

        SnakePixel head = SnakePixel::s_getSnake()[0];
        for (size_t i = 0; i < 2*(HRZ_PIXEL_COUNT+VRT_PIXEL_COUNT); i++)
        {
            if (borders[i].isMeet(head))
                initialize();
        }

        for (size_t i = 1; i < SnakePixel::s_getSnakeLen(); i++)
        {
            if (SnakePixel::s_getSnake()[i].isMeet(head))
                initialize();
        }

        window.display();

    }
    return 0;
}