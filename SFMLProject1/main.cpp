/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : main.cpp
Description : Main program for Whizzards Game
Author : Jayden Burns, Jandre Cronje, Daniel Kilfoyle, William Kuzmic
**************************************************************************/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "cGameCameras.h"
#include "cLevel.h" 
#include "cPlayer.h"
#include "cProjectile.h"
#include <SFML/System/Clock.hpp>
#include "cGameManager.h"
#include "cEnemySpawner.h"
#include "cCollisionManager.h"
#include "cLevelLoader.h"
#include "cWandManager.h"


// Function to load spawn points from a file
std::vector<sf::Vector2f> LoadSpawnPoints(const std::string& filename) {
    std::vector<sf::Vector2f> spawnPoints;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open spawn points file: " << filename << std::endl;
        return spawnPoints;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        float x, y;
        char comma; // To skip the comma if you have a comma-separated format

        // Assuming the spawn points are in the format: x,y
        if (iss >> x >> comma >> y) // Read x and y values
        {
            spawnPoints.emplace_back(x, y); // Store the spawn point
            std::cout << "Loaded spawn point: (" << x << ", " << y << ")" << std::endl; // Debug output
        }
        else
        {
            std::cerr << "Invalid line format in spawn points file: " << line << std::endl; // Handle parsing errors
        }
    }

    file.close();
    std::cout << "Finished loading spawn points. Total spawn points loaded: " << spawnPoints.size() << std::endl;

    return spawnPoints;
}

// Load textures for Grass and Sand tiles
void LoadTileTextures(std::map<int, sf::Texture> textures) {
    textures[1].loadFromFile("Resources/Textures/Grass.png"); // Grass tile
    textures[2].loadFromFile("Resources/Textures/Sand.png");  // Sand tile
}

// Load the tile map from a text file
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
                row.push_back(0); // Empty or other tiles can be added later
            }
        }
        tileMap.push_back(row);
    }
    return tileMap;
}

// Render the tile map
void RenderTileMap(sf::RenderWindow& window, const std::vector<std::vector<int>>& tileMap, const std::map<int, sf::Texture>& textures, int tileWidth, int tileHeight) {
    for (size_t y = 0; y < tileMap.size(); ++y) {
        for (size_t x = 0; x < tileMap[y].size(); ++x) {
            int tileId = tileMap[y][x];
            if (tileId > 0) { // Only render non-empty tiles
                sf::Sprite tile;
                tile.setTexture(textures.at(tileId));
                tile.setPosition(x * tileWidth, y * tileHeight);
                window.draw(tile);
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
    cCollisionManager Collision;
    cWand wand;


    // Create the window with a set resolution
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Project");
    window.setFramerateLimit(60);

    // Loading the font for UI
    sf::Font WizardFont;
    WizardFont.loadFromFile("Resources/Fonts/Wizard.ttf");

    sf::Text firstPlayerHealthText;
    firstPlayerHealthText.setFont(WizardFont);
    firstPlayerHealthText.setFillColor(sf::Color::Red);
    firstPlayerHealthText.setCharacterSize(36);
    firstPlayerHealthText.setPosition(sf::Vector2f(100, 50));
    sf::Text secondPlayerHealthText;
    secondPlayerHealthText.setFont(WizardFont);
    secondPlayerHealthText.setFillColor(sf::Color::Red);
    secondPlayerHealthText.setCharacterSize(36);
    secondPlayerHealthText.setPosition(sf::Vector2f(100, 100));

    // View for UI drawing only
    sf::View uiViewPort(sf::Vector2f(640, 360), sf::Vector2f(1280, 720));


    // Initialize level and load textures internally
    cLevel level(3000, 3000);
    std::vector<std::vector<int>> tileMap;
    std::vector<sf::Vector2f> enemySpawnPoints;
    sf::Vector2f player1Pos, player2Pos;



    // Create the Wand manager
    cWandManager wandManager;

    // Load the level
    std::vector<sf::Vector2f> wandSpawnPoints; // Load this from your level

    // Load tile textures into a map (texture ID mapped to sf::Texture)
    const std::map<int, sf::Texture>& tileTextures = level.getTileTextures();  // Use the getter directly

    // Load the level data
    if (!level.LoadLevel("Resources/Levels/Level1.txt", level.getTileTextures(), tileMap, enemySpawnPoints, player1Pos, player2Pos)) {
        std::cerr << "Failed to load level!" << std::endl;
    }
    // Create player instances
    cPlayer* Player1 = new cPlayer(Manager.getFirstPlayerSprite(), "Player 1", sf::Vector2f(700, 500), Manager.getCollisionList(), level);
    cPlayer* Player2 = new cPlayer(Manager.getSecondPlayerSprite(), "Player 2", sf::Vector2f(800, 600), Manager.getCollisionList(), level);
    Player1->setProjectileSprite(Manager.getFirstPlayerProjectile());
    Player2->setProjectileSprite(Manager.getSecondPlayerProjectile());
    Player1->setProjectileList(Manager.getProjectilesList());
    Player2->setProjectileList(Manager.getProjectilesList());





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
    cEnemyPool Pool(200, Manager.getEnemyDefaultSprite(), Manager.getCollisionList());
    Pool.setBehaviourSprites(Manager.getEnemyAsteroidSprite(), Manager.getEnemyRandomSprite(), Manager.getEnemyChaseSprite());
    Pool.setPlayers(Player1,Player2);

    // Load enemy spawn points from file
    //std::vector<sf::Vector2f> enemySpawnPoints = LoadSpawnPoints("Resources/Levels/spawn_points.txt");
    cEnemySpawner Spawner(10, 5, &Pool, 20, 30);
    Spawner.setSpawnPoints(&enemySpawnPoints);

    // Load tile textures
    //std::map<int, sf::Texture> tileTextures;
    LoadTileTextures(tileTextures);

    // Load the level from the &text file
    //std::vector<std::vector<int>> tileMap = LoadLevel("Resources/Levels/level1.txt");


    // Tile dimensions
    int tileWidth = 64;
    int tileHeight = 64;


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
        

        // Update projectiles
        for (auto projectile : *Manager.getProjectilesList())
        {
            projectile->tick();
        }

        // Update camera positions based on player movements
        m_Cameras.UpdatePositions(Player1->getPosition(), Player2->getPosition());

        // Manage enemy waves
        Spawner.WaveManager();

        // Update the wand manager
        wandManager.update(deltaTime);

        wandManager.render(window);

        window.clear();

        // Render wands in the game loop
        for (auto& cWand : wandManager.getWands()) 
        {
            window.draw(cWand->getSprite());
        }

        // Checking the collisions for all characters (Enemies and players) and then checking the projectiles
        Collision.collisionCheck(*Manager.getCollisionList());
        Collision.projectileCheck(*Manager.getCollisionList(), *Manager.getProjectilesList());

        if (m_Cameras.UseCombinedView())
        {
            m_Cameras.SetViewBothPlayers();
            RenderTileMap(window, tileMap, tileTextures, tileWidth, tileHeight); // Render the tile map
            m_Cameras.Render(Player1, &window);
            m_Cameras.Render(Player2, &window);

            for (auto iter : Pool.getActiveEnemies())
            {
                m_Cameras.Render(iter, &window);
            }
            for (auto iter : *Manager.getProjectilesList())
            {
                window.draw(iter->m_sprite);
            }
        }
        else
        {
            // Render everything twice for individual views
            m_Cameras.setViewFirstPlayer();
            RenderTileMap(window, tileMap, tileTextures, tileWidth, tileHeight); // Render the tile map
            m_Cameras.Render(Player1, &window);
            m_Cameras.Render(Player2, &window);
            for (auto iter : Pool.getActiveEnemies())
            {
                m_Cameras.Render(iter, &window);
            }
            for (auto iter : *Manager.getProjectilesList())
            {
                window.draw(iter->m_sprite);
            }

            m_Cameras.setViewSecondPlayer();
            RenderTileMap(window, tileMap, tileTextures, tileWidth, tileHeight); // Render the tile map
            m_Cameras.Render(Player1, &window);
            m_Cameras.Render(Player2, &window);
            for (auto iter : Pool.getActiveEnemies())
            {
                m_Cameras.Render(iter, &window);
            }
            for (auto iter : *Manager.getProjectilesList())
            {
                window.draw(iter->m_sprite);
            }
        }

        
        window.setView(uiViewPort);

        firstPlayerHealthText.setString("Wizard 1 Health: " + std::to_string(int(Player1->getHealth())));
        secondPlayerHealthText.setString("Wizard 2 Health: " + std::to_string(int(Player2->getHealth())));

        window.draw(firstPlayerHealthText);
        window.draw(secondPlayerHealthText);

        // Draw the wand
        wand.draw(window);

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
        window.draw(projectile->m_sprite);
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
        window.draw(projectile->m_sprite);
    }
}
