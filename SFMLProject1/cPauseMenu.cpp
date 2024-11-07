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

    // Setup "Resume" button
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Resume");
    menu[0].setCharacterSize(50);
    menu[0].setPosition(sf::Vector2f(width / 2 - 100, height / 2));

    // Setup "Quit" button
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Quit");
    menu[1].setCharacterSize(50);
    menu[1].setPosition(sf::Vector2f(width / 2 - 100, height / 2 + 100));

    selectedItemIndex = 0;
}

void cPauseMenu::draw(sf::RenderWindow& window) {
    // Draw the background first
    window.draw(backgroundSprite);

    // Draw menu items on top of the background
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(menu[i]);
    }
}

void cPauseMenu::MoveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void cPauseMenu::MoveDown() {
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

int cPauseMenu::GetPressedItem() {
    return selectedItemIndex;
}
