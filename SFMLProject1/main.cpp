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

    // Initialize level and load textures internally
    cLevel level(3000, 3000);
    std::vector<std::vector<int>> tileMap;
    std::vector<sf::Vector2f> enemySpawnPoints;
    sf::Vector2f player1Pos, player2Pos;

    // Create player instances
    cPlayer* Player1 = new cPlayer(Manager.getFirstPlayerSprite(0), "Player 1", sf::Vector2f(1000, 800), Manager.getCollisionList(), level);
    cPlayer* Player2 = new cPlayer(Manager.getSecondPlayerSprite(0), "Player 2", sf::Vector2f(1050, 800), Manager.getCollisionList(), level);
    Player1->setProjectileSprite(Manager.getFirstPlayerProjectile(0));
    Player2->setProjectileSprite(Manager.getSecondPlayerProjectile(0));
    Player1->setProjectileList(Manager.getProjectilesList());
    Player2->setProjectileList(Manager.getProjectilesList());


    // Create the window with a set resolution
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Project");
    window.setFramerateLimit(60);

    // Load the menu
    cMenu menu(window.getSize().x, window.getSize().y);
    cPauseMenu pauseMenu(window.getSize().x, window.getSize().y);  // Pause menu
    bool isMenuActive = true;
    bool isPaused = false;  // Track if the game is paused

    // Health bar dimensions and positioning
    const float healthBarWidth = 200.f;  // Full width of the health bar
    const float healthBarHeight = 20.f;  // Height of the health bar

    // Loading the font for UI
    sf::Font WizardFont;
    WizardFont.loadFromFile("Resources/Fonts/Wizard.ttf");

    // Render wand names for Player 1
    sf::Text player1WandText(Player1->getCurrentWandName(), WizardFont, 20);
    player1WandText.setPosition(50, 100);  // Adjust this to your UI layout
    player1WandText.setFillColor(sf::Color::Blue);
    player1WandText.setCharacterSize(24);

    // Render wand names for Player 2
    sf::Text player2WandText(Player2->getCurrentWandName(), WizardFont, 20);
    player2WandText.setPosition(950, 100);  // Adjust this to your UI layout
    player2WandText.setFillColor(sf::Color::Red);
    player2WandText.setCharacterSize(24);

    sf::Text firstPlayerHealthText;
    firstPlayerHealthText.setFont(WizardFont);
    firstPlayerHealthText.setFillColor(sf::Color::Blue);
    firstPlayerHealthText.setCharacterSize(36);
    firstPlayerHealthText.setPosition(sf::Vector2f(50, 25));

    sf::Text secondPlayerHealthText;
    secondPlayerHealthText.setFont(WizardFont);
    secondPlayerHealthText.setFillColor(sf::Color::Red);
    secondPlayerHealthText.setCharacterSize(36);
    secondPlayerHealthText.setPosition(sf::Vector2f(950, 25));

    // Set up health bars for each player
    sf::RectangleShape firstPlayerHealthBarBackground(sf::Vector2f(healthBarWidth, healthBarHeight));
    firstPlayerHealthBarBackground.setPosition(50, 75);  // Position on screen
    firstPlayerHealthBarBackground.setFillColor(sf::Color(50, 50, 50));  // Background color (dark gray)

    sf::RectangleShape firstPlayerHealthBar(sf::Vector2f(healthBarWidth, healthBarHeight));
    firstPlayerHealthBar.setPosition(50, 75);  // Same position as background
    firstPlayerHealthBar.setFillColor(sf::Color::Blue);  // Health bar color

    sf::RectangleShape secondPlayerHealthBarBackground(sf::Vector2f(healthBarWidth, healthBarHeight));
    secondPlayerHealthBarBackground.setPosition(950, 75);
    secondPlayerHealthBarBackground.setFillColor(sf::Color(50, 50, 50));

    sf::RectangleShape secondPlayerHealthBar(sf::Vector2f(healthBarWidth, healthBarHeight));
    secondPlayerHealthBar.setPosition(950, 75);
    secondPlayerHealthBar.setFillColor(sf::Color::Red);

    sf::Text Player1scoreText;
    Player1scoreText.setFont(WizardFont);
    Player1scoreText.setFillColor(sf::Color::White);
    Player1scoreText.setCharacterSize(24);
    Player1scoreText.setPosition(50, 130);  // Position below the health bar
    Player1scoreText.setString("Score: 0");  // Initial score

    sf::Text Player2scoreText;
    Player2scoreText.setFont(WizardFont);
    Player2scoreText.setFillColor(sf::Color::White);
    Player2scoreText.setCharacterSize(24);
    Player2scoreText.setPosition(950, 130);  // Position below the health bar
    Player2scoreText.setString("Score: 0");  // Initial score

    // Set up the UI view for drawing
    sf::View uiViewPort(sf::Vector2f(640, 360), sf::Vector2f(1280, 720));



    // Load tile textures into a map (texture ID mapped to sf::Texture)
    const std::map<int, sf::Texture>& tileTextures = level.getTileTextures();  // Use the getter directly

    // Load the level data
    if (!level.LoadLevel("Resources/Levels/Level1.txt", level.getTileTextures(), tileMap, "Resources/Levels/spawn_points.txt", player1Pos, player2Pos, "Resources/Levels/wand_spawn_points.txt")) {
        std::cerr << "Failed to load level!" << std::endl;
    }

    // Create the Wand manager
    cWandManager wandManager(Manager.getWandPickupSprite(0), level.getWandSpawnPoints());



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
    cEnemySpawner Spawner(10, 5, &Pool, 20, 30);
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
                m_Cameras.Render(Player1, &window);
                m_Cameras.Render(Player2, &window);

                for (auto iter : Pool.getActiveEnemies())
                {
                    m_Cameras.Render(iter, &window);
                }
                for (auto iter : *Manager.getProjectilesList())
                {
                    m_Cameras.Render(iter, &window);
                }
                for (auto& wandPickup : wandManager.getWandPickups())
                {
                    m_Cameras.Render(wandPickup, &window);

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
                    m_Cameras.Render(iter, &window);
                }
                for (auto& wandPickup : wandManager.getWandPickups())
                {
                    m_Cameras.Render(wandPickup, &window);
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
                    m_Cameras.Render(iter, &window);
                }
                for (auto& wandPickup : wandManager.getWandPickups())
                {
                    m_Cameras.Render(wandPickup, &window);
                }
            }

            // Checking the collisions for all characters (Enemies and players) and then checking the projectiles
            Collision.collisionCheck(*Manager.getCollisionList());
            Collision.projectileCheck(*Manager.getCollisionList(), *Manager.getProjectilesList());
            Collision.wandCheck(*Manager.getCollisionList(), wandManager.getWandPickups());

            window.setView(uiViewPort);  // Switch to UI viewport for health and UI rendering

            firstPlayerHealthText.setString("Wizard 1 Health: ");
            secondPlayerHealthText.setString("Wizard 2 Health: ");

            player1WandText.setString("Wand: ");
            player2WandText.setString("Wand: ");

            // Update the score
            int score = 100;  // Example score, update this based on game logic
            Player1scoreText.setString("Score: " + std::to_string(score));
            Player2scoreText.setString("Score: " + std::to_string(score));

            window.draw(firstPlayerHealthText);
            window.draw(secondPlayerHealthText);

            window.draw(Player1scoreText);
            window.draw(Player2scoreText);


            window.draw(player1WandText);
            window.draw(player2WandText);



            // Update health bar sizes based on player health
            float player1HealthPercentage = Player1->getHealth() / Player1->getHealth();
            firstPlayerHealthBar.setSize(sf::Vector2f(healthBarWidth* player1HealthPercentage, healthBarHeight));

            float player2HealthPercentage = Player2->getHealth() / Player2->getHealth();
            secondPlayerHealthBar.setSize(sf::Vector2f(healthBarWidth* player2HealthPercentage, healthBarHeight));

            // Draw health bars
            window.draw(firstPlayerHealthBarBackground);
            window.draw(firstPlayerHealthBar);

            window.draw(secondPlayerHealthBarBackground);
            window.draw(secondPlayerHealthBar);
        }

        window.display();  // Always display after rendering
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
