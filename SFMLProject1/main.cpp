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
#include <SFML/Audio.hpp>
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
#include "cScoreMenu.h"
#include "cScore.h"

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

// Function to save score to a file
void SaveScoreToFile(int score) {
    std::ofstream scoreFile("Resources/scores.txt", std::ios::app);
    if (scoreFile.is_open()) {
        scoreFile << score << std::endl;  // Append the score to the file
        scoreFile.close();
    }
    else {
        std::cerr << "Could not open score file!" << std::endl;
    }
}

sf::Clock castTimer;
sf::Clock gameClock;

int main() {
    float deltaTime = gameClock.restart().asSeconds();

    srand(static_cast<unsigned>(time(0)));
    cGameManager Manager;
    cCollisionManager Collision;
    cSoundManager Sounds;
    Collision.setSoundManager(&Sounds);

    cBurstWand* wand = new cBurstWand();



    // Initialize level and load textures internally
    cLevel level(3000, 3000);
    std::vector<std::vector<int>> tileMap;
    std::vector<sf::Vector2f> enemySpawnPoints;
    sf::Vector2f player1Pos, player2Pos;


    // Initialize cScore object
    cScore gameScore;

    // Create player instances
    cPlayer* Player1 = new cPlayer(Manager.getFirstPlayerSprite(0), "Player 1", sf::Vector2f(1000, 800), Manager.getCollisionList(), level);
    cPlayer* Player2 = new cPlayer(Manager.getSecondPlayerSprite(0), "Player 2", sf::Vector2f(1050, 800), Manager.getCollisionList(), level);
    Player1->setProjectileSprite(Manager.getFirstPlayerProjectile(0));
    Player2->setProjectileSprite(Manager.getSecondPlayerProjectile(0));
    Player1->setProjectileList(Manager.getProjectilesList());
    Player2->setProjectileList(Manager.getProjectilesList());

    // Set all player sounds

    Player1->setProjectileSound(Manager.getProjectileFireSound());
    Player1->setDamageSound(Manager.getPlayerDamageSound());
    Player1->setDeathSound(Manager.getPlayerDeathSound());
    Player1->setIdleSound(Manager.getPlayerIdleSound());
    Player1->setProjectileHitSound(Manager.getProjectileHitSound());
    
    Player2->setProjectileSound(Manager.getProjectileFireSound());
    Player2->setDamageSound(Manager.getPlayerDamageSound());
    Player2->setDeathSound(Manager.getPlayerDeathSound());
    Player2->setIdleSound(Manager.getPlayerIdleSound());
    Player2->setProjectileHitSound(Manager.getProjectileHitSound());

    Player1->setSoundManager(&Sounds);
    Player2->setSoundManager(&Sounds);

    // Create the window with a set resolution
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Project");
    window.setFramerateLimit(60);

    // Load the menu
    cMenu menu(window.getSize().x, window.getSize().y);
    cPauseMenu pauseMenu(window.getSize().x, window.getSize().y);  // Pause menu
    cScoreMenu scoreMenu(window.getSize().x, window.getSize().y);
    bool isMenuActive = true;
    bool isScoreMenuActive = false;
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

    sf::Text PlayerscoreText;
    PlayerscoreText.setFont(WizardFont);
    PlayerscoreText.setFillColor(sf::Color::White);
    PlayerscoreText.setCharacterSize(24);
    PlayerscoreText.setPosition(600, 50);  // Position below the health bar
    PlayerscoreText.setString("Score: 0");  // Initial score


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


    // Initialize game camera
    cGameCameras m_Cameras(&window, 3000, 3000, &Manager);
    cEnemyPool Pool(200, Manager.getEnemyDefaultSprite(), Manager.getCollisionList());
    Pool.setPlayers(Player1, Player2);
    Pool.setProjectiles(Manager.getFireProjectile(0), Manager.getProjectilesList());

    // Load enemy spawn points from level
    cEnemySpawner Spawner(15, 10, &Pool, 20, 30, Player1, Player2);
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
                            isScoreMenuActive = true;  // Open score menu
                            isMenuActive = false;
                            scoreMenu.loadScores("Resources/scores.txt");  // Load scores when score menu opens
                        }
                        else if (selected == 2) {  // Assuming Quit is option 2

                            window.close();
                        }
                    }
                }
            }
            else if (isScoreMenuActive) {
                // Score menu navigation
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Return) {
                        isScoreMenuActive = false;  // Return to main menu
                        isMenuActive = true;
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

        float deltaTime = gameClock.restart().asSeconds(); // Calculate deltaTime

        if (isMenuActive) {
            // Render the menu
            menu.draw(window);
        }
        else if (isScoreMenuActive) {
            scoreMenu.draw(window);  // Draw score menu if active
        }
        else if (isPaused) {
            // Render the pause menu
            pauseMenu.draw(window);
        }
        else {
            // Calculate deltaTime
            

            Player1->processInput();
            Player2->processInput();
            Player1->playerUpdate(deltaTime);
            Player2->playerUpdate(deltaTime);

            // Check for player health
            if (Player1->getHealth() <= 0 && Player2->getHealth() <= 0) {
                // Both players are dead, save score and show score menu
                SaveScoreToFile(gameScore.getScore());  // Save the score to file
                isScoreMenuActive = true;                // Show score menu
                isPaused = true;                         // Optional: pause the game
            }

            // Update projectiles
            for (auto projectile : *Manager.getProjectilesList()) {
                projectile->tick(deltaTime);
            }

            // Update camera positions based on player movements
            m_Cameras.UpdatePositions(Player1->getPosition(), Player2->getPosition());

            // Manage enemy waves
            Spawner.WaveManager(deltaTime, gameScore, level);

           
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

            firstPlayerHealthText.setString("Wizard 1 Health: ");
            secondPlayerHealthText.setString("Wizard 2 Health: ");

            player1WandText.setString("Wand: "+ Player1->getCurrentWandName());
            player2WandText.setString("Wand: "+ Player2->getCurrentWandName());

            Spawner.WaveManager(deltaTime, gameScore, level); 
            PlayerscoreText.setString("Score: " + std::to_string(gameScore.getScore()));

            window.draw(firstPlayerHealthText);
            window.draw(secondPlayerHealthText);

            window.draw(PlayerscoreText);


            window.draw(player1WandText);
            window.draw(player2WandText);


            //// Update health bar sizes based on player health

            float player1HealthPercentage = Player1->getHealth() / Player1->getMaxHealth(); // Correct calculation
            firstPlayerHealthBar.setSize(sf::Vector2f(healthBarWidth* player1HealthPercentage, healthBarHeight));

            float player2HealthPercentage = Player2->getHealth() / Player2->getMaxHealth(); // Correct calculation
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


