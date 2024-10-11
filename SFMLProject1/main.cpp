#include <SFML/Graphics.hpp>
#include <iostream>
#include "cGameCameras.h"
#include "cLevelLoader.h"
#include "cPlayer.h"
#include "vector"
#include <cstdlib>
#include <ctime>
#include "cProjectile.h"
#include <SFML/System/Clock.hpp>
#include "cGameManager.h"
#include "cEnemySpawner.h"


cProjectile* CreateProjectile(sf::Sprite _sprite, sf::Vector2f _pos, float _rotation)
{
    cProjectile* proj = new cProjectile(_sprite, _pos, _rotation);
    return proj;
}

sf::Clock castTimer;

int main()
{
    srand(static_cast <unsigned> (time(0)));
    cGameManager Manager;
    //Create the window with a set resolution:
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Project");
    window.setFramerateLimit(60);

    // Test sprites for players.
    sf::Texture firstPlayerTexture;
    firstPlayerTexture.loadFromFile("Resources/Textures/Sprites/Blue Player.png");
    sf::Sprite* firstPlayerSprite = nullptr;   
    //firstPlayerSprite->setTexture(firstPlayerTexture);

    sf::Texture secondPlayerTexture;
    secondPlayerTexture.loadFromFile("Resources/Textures/Sprites/Red Player.png");
    sf::Sprite* secondPlayerSprite = nullptr;
    //secondPlayerSprite->setTexture(secondPlayerTexture);

    

    cPlayer* Player1 = new cPlayer(&Manager.m_firstPlayerSprite, "Player 1", sf::Vector2f(400, 300), Manager.GetCollisionList());
    cPlayer* Player2 = new cPlayer(&Manager.m_secondPlayerSprite, "Player 2", sf::Vector2f(500, 300), Manager.GetCollisionList());

    sf::Texture blueProjectileTexture;
    blueProjectileTexture.loadFromFile("Resources/Textures/Sprites/Projectile Blue.png");
    sf::Sprite blueProjectileSprite;
    blueProjectileSprite.setTexture(blueProjectileTexture);
    

    std::vector<cProjectile* > activeProjectiles;

    cGameCameras m_Cameras(&window, 3000, 3000);
    cEnemyPool Pool(200, &Manager.m_defaultEnemySprite, Manager.GetCollisionList());
    cEnemySpawner Spawner(10, 5, &Pool);

    //Temporary Map - Creates texture, loads temp file, changes positioning
    sf::Texture mapTex;
    mapTex.loadFromFile("Resources/map.jpg");
    sf::Sprite map(mapTex);
    map.setPosition(-sf::Vector2f(map.getLocalBounds().width / 2.f, map.getLocalBounds().height / 2.f));


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
 
        }

        Player1->processInput();
        Player2->processInput();
        bool bfired = false;

        //castTimer.restart();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            

            if ((castTimer.getElapsedTime().asMilliseconds() >= 500.0f) && !bfired)
            {
                if (!bfired)
                {
                    
                    activeProjectiles.push_back(CreateProjectile(blueProjectileSprite, Player1->getPosition(), Player1->getRotation()));
                    std::cout << "castTimer duration: " << castTimer.getElapsedTime().asMilliseconds() << std::endl;
                    //std::cout << "ProjectileSpawned: Number of active projectiles: " << activeProjectiles.size() << std::endl;
                    castTimer.restart();
                    bfired = true;
                }
                else if (castTimer.getElapsedTime().asMilliseconds() >= 500.0f && bfired)
                {
                    bfired = false;
                }

            }

        }




        for (auto projectile : activeProjectiles)
        {
            projectile->tick();
        }

        m_Cameras.UpdatePositions(Player1->getPosition(), Player2->getPosition());
        Spawner.WaveManager();

        window.clear();

        if (m_Cameras.UseCombinedView())
        {
            //Render everything once
            m_Cameras.SetViewBothPlayers();
            m_Cameras.Render(&map, &window);
            m_Cameras.Render(Player1, &window);
            m_Cameras.Render(Player2, &window);

            for (auto iter : Pool.GetActiveEnemies())
            {
                m_Cameras.Render(iter, &window);
            }
            for (auto iter : activeProjectiles)
            {
                window.draw(iter->m_Sprite);
            }
        }
        else
        {
            //Render everything twice
            m_Cameras.setViewFirstPlayer();
            m_Cameras.Render(&map, &window);
            m_Cameras.Render(Player1, &window);
            m_Cameras.Render(Player2, &window);
            for (auto iter : Pool.GetActiveEnemies())
            {

                m_Cameras.Render(iter, &window);
            }
            for (auto iter : activeProjectiles)
            {
                window.draw(iter->m_Sprite);
            }
            m_Cameras.setViewSecondPlayer();

            m_Cameras.Render(&map, &window);
            m_Cameras.Render(Player1, &window);
            m_Cameras.Render(Player2, &window);
            for (auto iter : Pool.GetActiveEnemies())
            {
                m_Cameras.Render(iter, &window);
            }
            for (auto iter : activeProjectiles)
            {
                window.draw(iter->m_Sprite);
            }
        }

        //////////////////////////////////
        window.display();
    }

    return 0;
}