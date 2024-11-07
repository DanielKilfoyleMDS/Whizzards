#include "cPauseMenu.h"
#include <iostream>

cPauseMenu::cPauseMenu(float width, float height) {
    // Load font
    if (!font.loadFromFile("Resources/Fonts/Wizard.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    // Load background texture
    if (!backgroundTexture.loadFromFile("Resources/Textures/PauseMenuBackground.png")) {
        std::cerr << "Failed to load pause menu background image!" << std::endl;
    }
    else {
        // Set background sprite and scale to fit window
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(
            width / backgroundTexture.getSize().x,
            height / backgroundTexture.getSize().y
        );
    }

    // Setup title
    title.setFont(font);
    title.setFillColor(sf::Color::White);
    title.setString("Paused");
    title.setCharacterSize(70);
    // Center the title at the top of the screen
    float titleX = (width - title.getGlobalBounds().width) / 2;
    float titleY = 20;  // Distance from the top of the window
    title.setPosition(sf::Vector2f(titleX, titleY));

    // Define the dimensions of the square (assuming it's at the center of the screen)
    float squareWidth = 400.0f;  // Adjust to the width of your square
    float squareHeight = 200.0f; // Adjust to the height of your square
    float squareX = (width - squareWidth) / 2;
    float squareY = (height - squareHeight) / 1.25;

    // Setup "Resume" button
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Yellow);
    menu[0].setString("Resume");
    menu[0].setCharacterSize(50);
    // Center the text within the square
    float resumeButtonX = squareX + (squareWidth - menu[0].getGlobalBounds().width) / 2;
    float resumeButtonY = squareY + 20; // Add some padding from the top
    menu[0].setPosition(sf::Vector2f(resumeButtonX, resumeButtonY));

    // Setup "Quit" button
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Quit");
    menu[1].setCharacterSize(50);
    // Center the text within the square
    float quitButtonX = squareX + (squareWidth - menu[1].getGlobalBounds().width) / 2;
    float quitButtonY = resumeButtonY + menu[0].getCharacterSize() + 30; // Position below "Resume" with some padding
    menu[1].setPosition(sf::Vector2f(quitButtonX, quitButtonY));

    selectedItemIndex = 0;
}


void cPauseMenu::draw(sf::RenderWindow& window) {
    // Draw background
    window.draw(backgroundSprite);

    // Draw title at the top
    window.draw(title);

    // Draw menu items
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(menu[i]);
    }
}

void cPauseMenu::MoveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

void cPauseMenu::MoveDown() {
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

int cPauseMenu::GetPressedItem() {
    return selectedItemIndex;
}
