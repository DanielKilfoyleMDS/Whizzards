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
#include "cMenu.h"
#include "cPauseMenu.h"

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

int main() {
    float deltaTime = gameClock.restart().asSeconds();

    srand(static_cast<unsigned>(time(0)));
    cGameManager Manager;
    cCollisionManager Collision;

    cBurstWand* wand = new cBurstWand();

    // Create the window with a set resolution
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Project");
    window.setFramerateLimit(60);

    // Load the menu
    cMenu menu(window.getSize().x, window.getSize().y);
    cPauseMenu pauseMenu(window.getSize().x, window.getSize().y);  // Pause menu
    bool isMenuActive = true;
    bool isPaused = false;  // Track if the game is paused

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

    // Load tile textures into a map (texture ID mapped to sf::Texture)
    const std::map<int, sf::Texture>& tileTextures = level.getTileTextures();  // Use the getter directly

    // Load the level data
    if (!level.LoadLevel("Resources/Levels/Level1.txt", level.getTileTextures(), tileMap, "Resources/Levels/spawn_points.txt", player1Pos, player2Pos, "Resources/Levels/wand_spawn_points.txt")) {
        std::cerr << "Failed to load level!" << std::endl;
    }

    // Create the Wand manager
    cWandManager wandManager(Manager.getWandPickupSprite(0), level.getWandSpawnPoints());

    // Create player instances
    cPlayer* Player1 = new cPlayer(Manager.getFirstPlayerSprite(0), "Player 1", sf::Vector2f(1000, 800), Manager.getCollisionList(), level);
    cPlayer* Player2 = new cPlayer(Manager.getSecondPlayerSprite(0), "Player 2", sf::Vector2f(1050, 800), Manager.getCollisionList(), level);
    Player1->setProjectileSprite(Manager.getFirstPlayerProjectile(0));
    Player2->setProjectileSprite(Manager.getSecondPlayerProjectile(0));
    Player1->setProjectileList(Manager.getProjectilesList());
    Player2->setProjectileList(Manager.getProjectilesList());

    sf::Texture blueProjectileTexture;
    if (!blueProjectileTexture.loadFromFile("Resources/Textures/Sprites/Projectile Blue.png")) {
        std::cerr << "Failed to load blue projectile texture!" << std::endl;
        return -1;
    }
    sf::Sprite blueProjectileSprite;
    blueProjectileSprite.setTexture(blueProjectileTexture);

    std::vector<cProjectile*> activeProjectiles;

    // Initialize game camera
    cGameCameras m_Cameras(&window, 3000, 3000, &Manager);
    cEnemyPool Pool(200, Manager.getEnemyDefaultSprite(), Manager.getCollisionList());
    Pool.setPlayers(Player1, Player2);

    // Load enemy spawn points from level
    cEnemySpawner Spawner(5, 2, &Pool, 20, 30);
    Spawner.setSpawnPoints(level.getEnemySpawnPoints());

    // Load tile textures
    LoadTileTextures(tileTextures);

    // Tile dimensions
    int tileWidth = 64;
    int tileHeight = 64;

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (isMenuActive) {
                // Menu navigation
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Up) {
                        menu.MoveUp();
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        menu.MoveDown();
                    }
                    else if (event.key.code == sf::Keyboard::Return) {
                        int selected = menu.GetPressedItem();
                        if (selected == 0) {
                            isMenuActive = false;  // Start game
                        }
                        else if (selected == 1) {
                            window.close();  // Quit game
                        }
                    }
                }
            }
            else if (isPaused) {
                // Pause menu navigation
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Up) {
                        pauseMenu.MoveUp();
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        pauseMenu.MoveDown();
                    }
                    else if (event.key.code == sf::Keyboard::Return) {
                        int selected = pauseMenu.GetPressedItem();
                        if (selected == 0) {
                            isPaused = false;  // Resume game
                        }
                        else if (selected == 1) {
                            window.close();  // Quit game
                        }
                    }
                }
            }
            else {
                // Game logic
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Escape) {
                        isPaused = !isPaused;  // Toggle pause
                    }
                }
            }
        }

        window.clear();

        if (isMenuActive) {
            // Render the menu
            menu.draw(window);
        }
        else if (isPaused) {
            // Render the pause menu
            pauseMenu.draw(window);
        }
        else {
            // Calculate deltaTime
            float deltaTime = gameClock.restart().asSeconds(); // Calculate deltaTime

            Player1->processInput();
            Player2->processInput();
            Player1->playerUpdate(deltaTime);
            Player2->playerUpdate(deltaTime);

            // Update projectiles
            for (auto projectile : *Manager.getProjectilesList()) {
                projectile->tick(deltaTime);
            }

            // Update camera positions based on player movements
            m_Cameras.UpdatePositions(Player1->getPosition(), Player2->getPosition());

            // Manage enemy waves
            Spawner.WaveManager(deltaTime);
            // Update the wand manager
            wandManager.update(deltaTime);

            // Render game objects
            if (m_Cameras.UseCombinedView())
            {
                m_Cameras.SetViewBothPlayers();
                RenderTileMap(window, tileMap, tileTextures, tileWidth, tileHeight); // Render the tile map
                m_Cameras.renderFullView(Player1,Player2,Pool.getActiveEnemies(),*Manager.getProjectilesList(),wandManager.getWandPickups());
            }
            else
            {
                // Render everything twice for individual views
                m_Cameras.setViewLeftSide();
                RenderTileMap(window, tileMap, tileTextures, tileWidth, tileHeight); // Render the tile map
                m_Cameras.setViewRightSide();
                RenderTileMap(window, tileMap, tileTextures, tileWidth, tileHeight);
                m_Cameras.renderSplitViews(Player1, Player2, Pool.getActiveEnemies(), *Manager.getProjectilesList(), wandManager.getWandPickups());
            }

            // Checking the collisions for all characters (Enemies and players) and then checking the projectiles
            Collision.collisionCheck(*Manager.getCollisionList());
            Collision.projectileCheck(*Manager.getCollisionList(), *Manager.getProjectilesList());
            Collision.wandCheck(*Manager.getCollisionList(), wandManager.getWandPickups());

            window.setView(uiViewPort);  // Switch to UI viewport for health and UI rendering

            firstPlayerHealthText.setString("Wizard 1 Health: " + std::to_string(int(Player1->getHealth())));
            secondPlayerHealthText.setString("Wizard 2 Health: " + std::to_string(int(Player2->getHealth())));

            window.draw(firstPlayerHealthText);
            window.draw(secondPlayerHealthText);
        }

        window.display();  // Always display after rendering
    }

    return 0;
}

// Helper function to render a single view
void RenderView(sf::RenderWindow& window, cGameCameras& cameras, cPlayer* Player1, cPlayer* Player2, const std::vector<std::vector<int>>& tileMap, const std::map<int, sf::Texture>& tileTextures, int tileWidth, int tileHeight, const std::vector<cEnemy*>& enemies, const std::vector<cProjectile*>& projectiles, bool firstPlayerView) {
    if (firstPlayerView) {
        cameras.setViewLeftSide();
    }
    else {
        cameras.setViewRightSide();
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
        cameras.Render(projectile, &window);
    }
}

// Helper function to render game objects
void RenderGameObjects(sf::RenderWindow& window, cGameCameras& cameras, cPlayer* Player1, cPlayer* Player2, const std::vector<cEnemy*>& enemies, const std::vector<cProjectile*>& projectiles) {
    cameras.Render(Player1, &window);
    cameras.Render(Player2, &window);
    for (auto enemy : enemies) {
        cameras.Render(enemy, &window);
    }
    for (auto projectile : projectiles) {
        cameras.Render(projectile, &window);
    }
}
