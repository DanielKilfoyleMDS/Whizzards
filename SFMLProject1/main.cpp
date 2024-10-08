#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <fstream>
#include "cGameCameras.h"
#include "cLevelLoader.h"
#include "cPlayer.h"
#include "cProjectile.h"
#include <SFML/System/Clock.hpp>
#include "cGameManager.h"
#include "cEnemySpawner.h"

// Function to create a projectile
cProjectile* CreateProjectile(sf::Sprite _sprite, sf::Vector2f _pos, float _rotation)
{
    cProjectile* proj = new cProjectile(_sprite, _pos, _rotation);
    return proj;
}

void LoadTileTextures(std::map<int, sf::Texture>& textures) {
    // Load your textures based on identifiers
    textures[1].loadFromFile("Resources/Textures/Grass.png");
    textures[2].loadFromFile("Resources/Textures/Sand.png");
    // Add more textures as needed
}

std::vector<std::vector<int>> LoadLevel(const std::string& filename) {
    std::vector<std::vector<int>> tileMap;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open level file!" << std::endl;
        return tileMap;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        for (char tile : line) {
            if (tile == 'G') {
                row.push_back(1); // Grass
            }
            else if (tile == 'S') {
                row.push_back(2); // Sand
            }
            else {
                row.push_back(0); // Empty
            }
        }
        tileMap.push_back(row);
    }
    return tileMap;
}

void RenderTileMap(sf::RenderWindow& window, const std::vector<std::vector<int>>& tileMap, const std::map<int, sf::Texture>& textures, int tileWidth, int tileHeight) {
    for (size_t y = 0; y < tileMap.size(); ++y) {
        for (size_t x = 0; x < tileMap[y].size(); ++x) {
            int tileId = tileMap[y][x];
            if (tileId > 0) { // Assuming 0 is no tile
                sf::Sprite tile;
                tile.setTexture(textures.at(tileId));
                tile.setPosition(x * tileWidth, y * tileHeight);
                window.draw(tile);
            }
        }
    }
}

sf::Clock castTimer;

int main()
{
    srand(static_cast<unsigned>(time(0)));
    cGameManager Manager;

    // Create the window with a set resolution
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Project");
    window.setFramerateLimit(60);

    // Load player textures
    sf::Texture firstPlayerTexture;
    if (!firstPlayerTexture.loadFromFile("Resources/Textures/Sprites/Blue Player.png")) {
        std::cerr << "Failed to load first player texture!" << std::endl;
        return -1;
    }
    sf::Texture secondPlayerTexture;
    if (!secondPlayerTexture.loadFromFile("Resources/Textures/Sprites/Red Player.png")) {
        std::cerr << "Failed to load second player texture!" << std::endl;
        return -1;
    }

    // Create player instances
    cPlayer* Player1 = new cPlayer(&Manager.m_firstPlayerSprite, "Player 1", sf::Vector2f(400, 300));
    cPlayer* Player2 = new cPlayer(&Manager.m_secondPlayerSprite, "Player 2", sf::Vector2f(500, 300));

    // Load projectile texture
    sf::Texture blueProjectileTexture;
    if (!blueProjectileTexture.loadFromFile("Resources/Textures/Sprites/Projectile Blue.png")) {
        std::cerr << "Failed to load blue projectile texture!" << std::endl;
        return -1;
    }
    sf::Sprite blueProjectileSprite;
    blueProjectileSprite.setTexture(blueProjectileTexture);

    std::vector<cProjectile*> activeProjectiles;

    cGameCameras m_Cameras(&window, 3000, 3000);
    cEnemyPool Pool(200, &Manager.m_defaultEnemySprite);
    cEnemySpawner Spawner(10, 5, &Pool);

    // Load tile textures
    std::map<int, sf::Texture> tileTextures;
    LoadTileTextures(tileTextures);

    // Load the level from the text file
    std::vector<std::vector<int>> tileMap = LoadLevel("Resources/Levels/level1.txt");

    int tileWidth = 64;  // Width of the tile
    int tileHeight = 64; // Height of the tile

    // Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        Player1->processInput();
        Player2->processInput();
        bool bfired = false;

        // Handle projectile firing
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (castTimer.getElapsedTime().asMilliseconds() >= 500.0f && !bfired)
            {
                activeProjectiles.push_back(CreateProjectile(blueProjectileSprite, Player1->getPosition(), Player1->getRotation()));
                std::cout << "castTimer duration: " << castTimer.getElapsedTime().asMilliseconds() << std::endl;
                castTimer.restart();
                bfired = true;
            }
        }

        // Update projectiles
        for (auto projectile : activeProjectiles)
        {
            projectile->tick();
        }

        m_Cameras.UpdatePositions(Player1->getPosition(), Player2->getPosition());
        Spawner.WaveManager();

        window.clear();

        if (m_Cameras.UseCombinedView())
        {
            m_Cameras.SetViewBothPlayers();
            RenderTileMap(window, tileMap, tileTextures, tileWidth, tileHeight); // Render the tile map
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
            // Render everything twice for individual views
            m_Cameras.setViewFirstPlayer();
            RenderTileMap(window, tileMap, tileTextures, tileWidth, tileHeight); // Render the tile map
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
            RenderTileMap(window, tileMap, tileTextures, tileWidth, tileHeight); // Render the tile map
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

        window.display();
    }

    return 0;
}
