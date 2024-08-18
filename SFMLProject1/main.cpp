#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayerCharacter.h"

int main()
{
    //Create the window with a set resolution:
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Project");
    
    PlayerCharacter* Player1 = new PlayerCharacter("Resources/Textures/Sprites/Blue Player.png", "Player 1");
    PlayerCharacter* Player2 = new PlayerCharacter("Resources/Textures/Sprites/Red Player.png", "Player 2");

    Player2->SetPosition(sf::Vector2f(500, 400));


    while (window.isOpen())
    {
        //Receive and deal with events here (mouse clicks, key events, window buttons etc).
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                Player1->movePlayer();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                Player1->rotatePlayer(sf::Keyboard::A);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                Player1->rotatePlayer(sf::Keyboard::D);
            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                Player2->rotatePlayer(sf::Keyboard::Left);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                Player2->rotatePlayer(sf::Keyboard::Right);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                Player2->movePlayer();
            }

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
                
            }
        }

        window.clear();
        //Do all your drawing in here/////

        //Player1->Draw();
        
        window.draw(Player1->playerSprite);
        window.draw(Player2->playerSprite);


        //////////////////////////////////
        window.display();
    }

    return 0;
}