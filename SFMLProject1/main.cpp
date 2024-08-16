#include <SFML/Graphics.hpp>
#include <iostream>
#include "cGameCameras.h"

int main()
{
    //Create the window with a set resolution:
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Project");

    cGameCameras Cameras(&window);


    //Players (temporary)
    sf::Vector2f playerSize(10, 10);
    sf::RectangleShape p1(playerSize), p2(playerSize);

    p1.setFillColor(sf::Color::Blue);
    p2.setFillColor(sf::Color::Red);

    const float PLAYERSPEED = 10.1f;

    //Temporary Map - Creates texture, loads temp file, changes positioning
    sf::Texture mapTex;
    mapTex.loadFromFile("Resources/map.jpg");
    sf::Sprite map(mapTex);
    map.setPosition(-sf::Vector2f(map.getLocalBounds().width / 2.f, map.getLocalBounds().height / 2.f));

    //Creating a convex shape:
    sf::ConvexShape Triangle;
    Triangle.setPointCount(3);
    Triangle.setPoint(0, sf::Vector2f(640.0f, 200.0f));
    Triangle.setPoint(1, sf::Vector2f(840.0f, 500.0f));
    Triangle.setPoint(2, sf::Vector2f(440.0f, 500.0f));
    Triangle.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        //Receive and deal with events here (mouse clicks, key events, window buttons etc).
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }


            //TEMPORARY User controls.
            sf::Vector2f move;
            //Player one input.
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                move.y += -1;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                move.y += 1;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                move.x += -1;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                move.x += 1;

            p1.move(move * PLAYERSPEED);

            //Reset the move vector.
            move = sf::Vector2f();
            //Player two input.
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                move.y += -1;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                move.y += 1;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                move.x += -1;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                move.x += 1;

            p2.move(move * PLAYERSPEED);

        }

        window.clear();
        //Do all your drawing in here/////

        Cameras.UpdatePositions(p1.getPosition(),p2.getPosition());

        Cameras.setView1();
        window.draw(map);
        window.draw(Triangle);
        window.draw(p1);
        window.draw(p2);
        Cameras.setView2();
        window.draw(map);
        window.draw(Triangle);
        window.draw(p1);
        window.draw(p2);

        //////////////////////////////////
        window.display();
    }

    return 0;
}