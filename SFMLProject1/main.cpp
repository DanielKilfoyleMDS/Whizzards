#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <fstream>
#include "cGameCameras.h"
#include "cLevel.h" 
#include "cPlayer.h"
#include "cProjectile.h"
#include <SFML/System/Clock.hpp>
#include "cGameManager.h"
#include "cEnemySpawner.h"

// Function to create a projectile
cProjectile* CreateProjectile(sf::Sprite _sprite, sf::Vector2f _pos, float _rotation)
{
    return new cProjectile(_sprite, _pos, _rotation);
}

// Renders the tile map
void RenderTileMap(sf::RenderWindow& window, const std::vector<std::vector<int>>& tileMap, const std::map<int, sf::Texture>& tileTextures, int tileWidth, int tileHeight) {
    for (size_t i = 0; i < tileMap.size(); ++i) {
        for (size_t j = 0; j < tileMap[i].size(); ++j) {
            int tileId = tileMap[i][j];
            if (tileTextures.find(tileId) != tileTextures.end()) {
                sf::Sprite tileSprite;
                tileSprite.setTexture(tileTextures.at(tileId));
                tileSprite.setPosition(static_cast<float>(j * tileWidth), static_cast<float>(i * tileHeight));
                window.draw(tileSprite);
            }
        }
    }
}

sf::Clock castTimer;

void RenderGameObjects(sf::RenderWindow& window, cGameCameras& cameras, cPlayer* Player1, cPlayer* Player2, const std::vector<cEnemy*>& enemies, const std::vector<cProjectile*>& projectiles);

void RenderView(sf::RenderWindow& window, cGameCameras& cameras, cPlayer* Player1, cPlayer* Player2, const std::vector<std::vector<int>>& tileMap, const std::map<int, sf::Texture>& tileTextures, int tileWidth, int tileHeight, const std::vector<cEnemy*>& enemies, const std::vector<cProjectile*>& projectiles, bool firstPlayerView);


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

    // Initialize level loader
    cLevel level(3000.f, 3000.f);

    // Load tile textures into a map (texture ID mapped to sf::Texture)
    std::map<int, sf::Texture> tileTextures;
    level.LoadTileTextures(tileTextures);

    // Load the level (tile map, spawn points, player positions)
    std::vector<std::vector<int>> tileMap;
    std::vector<sf::Vector2f> enemySpawnPoints;
    sf::Vector2f player1Pos, player2Pos;
    if (!level.LoadLevel("Resources/Levels/level1.txt", tileTextures, tileMap, enemySpawnPoints, player1Pos, player2Pos)) {
        return -1;
    }

    // Create player instances
    cPlayer* Player1 = new cPlayer(&Manager.m_firstPlayerSprite, "Player 1", sf::Vector2f(600, 500), level);
    cPlayer* Player2 = new cPlayer(&Manager.m_secondPlayerSprite, "Player 2", sf::Vector2f(400, 500), level);


    // Load projectile texture
    sf::Texture blueProjectileTexture;
    if (!blueProjectileTexture.loadFromFile("Resources/Textures/Sprites/Projectile Blue.png")) {
        std::cerr << "Failed to load blue projectile texture!" << std::endl;
        return -1;
    }
    sf::Sprite blueProjectileSprite;
    blueProjectileSprite.setTexture(blueProjectileTexture);

    std::vector<cProjectile*> activeProjectiles;

    // Initialize game camera
    cGameCameras m_Cameras(&window, 3000, 3000);

    // Initialize enemy pool and spawner
    cEnemyPool Pool(200, &Manager.m_defaultEnemySprite);
    cEnemySpawner Spawner(10, 5, &Pool);

    // Tile dimensions
    int tileWidth = 64;
    int tileHeight = 64;

    // Spawn enemies at the loaded spawn points
    for (const auto& spawnPoint : enemySpawnPoints) {
        Spawner.SpawnEnemy(spawnPoint);
    }

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

        // Update camera positions based on player movements
        m_Cameras.UpdatePositions(Player1->getPosition(), Player2->getPosition());

        // Manage enemy waves
        Spawner.WaveManager();

        window.clear();

        // Check if combined view or individual views should be used
        if (m_Cameras.UseCombinedView())
        {
            m_Cameras.SetViewBothPlayers();
            RenderTileMap(window, tileMap, tileTextures, tileWidth, tileHeight);
            RenderGameObjects(window, m_Cameras, Player1, Player2, Pool.GetActiveEnemies(), activeProjectiles);
        }
        else
        {
            // Render everything twice for individual views
            RenderView(window, m_Cameras, Player1, Player2, tileMap, tileTextures, tileWidth, tileHeight, Pool.GetActiveEnemies(), activeProjectiles, true);
            RenderView(window, m_Cameras, Player1, Player2, tileMap, tileTextures, tileWidth, tileHeight, Pool.GetActiveEnemies(), activeProjectiles, false);
        }

        window.display();
    }

    return 0;
}


// Helper function to render a single view
void RenderView(sf::RenderWindow& window, cGameCameras& cameras, cPlayer* Player1, cPlayer* Player2, const std::vector<std::vector<int>>& tileMap, const std::map<int, sf::Texture>& tileTextures, int tileWidth, int tileHeight, const std::vector<cEnemy*>& enemies, const std::vector<cProjectile*>& projectiles, bool firstPlayerView) {
    if (firstPlayerView) {
        cameras.setViewFirstPlayer();
    }
    else {
        cameras.setViewSecondPlayer();
    }

    // Render the tile map
    RenderTileMap(window, tileMap, tileTextures, tileWidth, tileHeight);

    // Render game objects
    cameras.Render(Player1, &window);
    cameras.Render(Player2, &window);
    for (auto enemy : enemies) {
        cameras.Render(enemy, &window);
    }
    for (auto projectile : projectiles) {
        window.draw(projectile->m_Sprite);
    }
}

// Helper function to render game objects
void RenderGameObjects(sf::RenderWindow& window, cGameCameras& cameras, cPlayer* Player1, cPlayer* Player2, const std::vector<cEnemy*>& enemies, const std::vector<cProjectile*>& projectiles)
{
    cameras.Render(Player1, &window);
    cameras.Render(Player2, &window);
    for (auto enemy : enemies) {
        cameras.Render(enemy, &window);
    }
    for (auto projectile : projectiles) {
        window.draw(projectile->m_Sprite);
    }
}
