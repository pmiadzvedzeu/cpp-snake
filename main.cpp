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
    using namespace std::this_thread;
    using namespace std::chrono;
    srand (time(NULL));

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "The Snake");

    Food food = Food();

    auto initialize = [&] () 
    {
        SnakePixel::createInitial();
        BorderPixel::s_createBorders();
        food.relocate();
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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                one_step_time+=2;
            }

            sleep_for(milliseconds(1));
        }

        sleep_until(system_clock::now() + milliseconds(SPEED - one_step_time));
        
        window.clear();

        for(int i=0; i < 2*(HRZ_PIXEL_COUNT+VRT_PIXEL_COUNT); i++)
        {
            window.draw(BorderPixel::s_getBorders()[i]);
        }

        if (food.isMeet(SnakePixel::s_getSnake()[0]))
        {
            SnakePixel oldTail = SnakePixel::s_getTail();
            food.relocate();
            SnakePixel(SnakePixel::s_getTail().getDirection());
            SnakePixel tail = SnakePixel::s_getTail();
            SnakePixel::s_getTail().setPixelPosition(oldTail.getPixelPosition() - tail.getDirection());
        }

        for (size_t i = 0; i < SnakePixel::s_getSnakeLen(); i++)
        {
            if (i < SnakePixel::s_getSnakeLen() - 1)
                SnakePixel::s_getSnake()[i+1].setNewDirection(SnakePixel::s_getSnake()[i].getDirection());
            SnakePixel::s_getSnake()[i].move();
            window.draw(SnakePixel::s_getSnake()[i]);
        }

        window.draw(food);

        SnakePixel head = SnakePixel::s_getSnake()[0];
        for (size_t i = 0; i < 2*(HRZ_PIXEL_COUNT+VRT_PIXEL_COUNT); i++)
        {
            if (BorderPixel::s_getBorders()[i].isMeet(head))
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