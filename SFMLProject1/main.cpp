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
#include "PowerupManager.h"
#include "cEnemySpawner.h"
#include "cWandManager.h"

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
sf::Clock gameClock;

void RenderGameObjects(sf::RenderWindow& window, cGameCameras& cameras, cPlayer* Player1, cPlayer* Player2, const std::vector<cEnemy*>& enemies, const std::vector<cProjectile*>& projectiles);

void RenderView(sf::RenderWindow& window, cGameCameras& cameras, cPlayer* Player1, cPlayer* Player2, const std::vector<std::vector<int>>& tileMap, const std::map<int, sf::Texture>& tileTextures, int tileWidth, int tileHeight, const std::vector<cEnemy*>& enemies, const std::vector<cProjectile*>& projectiles, bool firstPlayerView);


int main()
{

    float deltaTime = gameClock.restart().asSeconds();

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

    // Initialize level and load textures internally
    cLevel level(3000, 3000);
    std::vector<std::vector<int>> tileMap;
    std::vector<sf::Vector2f> enemySpawnPoints;
    sf::Vector2f player1Pos, player2Pos;

    // Create the power-up manager
    PowerupManager powerupManager;

    // Create the Wand manager
    cWandManager wandManager;

    // Initialize power-ups with spawn points from the level
    powerupManager.initializePowerUps(level.getPowerUpSpawnPoints());

    // Load the level
    std::vector<sf::Vector2f> wandSpawnPoints; // Load this from your level
    wandManager.initializeWands(wandSpawnPoints);

    // Load tile textures into a map (texture ID mapped to sf::Texture)
    const std::map<int, sf::Texture>& tileTextures = level.getTileTextures();  // Use the getter directly

    // Load the level data
    if (!level.LoadLevel("Resources/Levels/Level1.txt", level.getTileTextures(), tileMap, enemySpawnPoints, player1Pos, player2Pos)) {
        std::cerr << "Failed to load level!" << std::endl;
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

        // Calculate deltaTime
        float deltaTime = gameClock.restart().asSeconds(); // Calculate deltaTime

        Player1->processInput();
        Player2->processInput();
        bool bfired = false;

        // Check for player collision with wands
        wandManager.collectWand(Player1->getPosition());
        wandManager.collectWand(Player2->getPosition());

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

        // Update the wand manager
        wandManager.update(deltaTime);

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

        wandManager.render(window);
        powerupManager.render(window);
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
