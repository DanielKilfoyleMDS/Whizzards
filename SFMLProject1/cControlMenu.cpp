#include "cControlMenu.h"
#include <fstream>
#include <iostream>
#include <algorithm>

cControlMenu::cControlMenu(float width, float height) : selectedItemIndex(0) {
    // Load font
    if (!font.loadFromFile("Resources/Fonts/Wizard.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    // Load background texture
    if (!backgroundTexture.loadFromFile("Resources/Textures/ScoreMenuBackground.png")) {
        std::cerr << "Failed to load score menu background image!" << std::endl;
    }
    else {
        // Set background sprite and scale to fit window
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(
            width / backgroundTexture.getSize().x,
            height / backgroundTexture.getSize().y
        );
    }

    // Setup title (centered at the top)
    title.setFont(font);
    title.setFillColor(sf::Color::White);
    title.setString("Controls");
    title.setCharacterSize(100);
    title.setPosition(sf::Vector2f((width - title.getGlobalBounds().width) / 2, height / 20));

    // Setup "Back" button (centered at the bottom)
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Yellow);
    menu[0].setString("Back");
    menu[0].setCharacterSize(50);
    menu[0].setPosition(sf::Vector2f((width - menu[0].getGlobalBounds().width) / 2, height - 100));

    // Square background for control instructions
    float squareSize = std::min(width, height) / 1.5; // square size to fit within screen dimensions
    controlSquare.setSize(sf::Vector2f(squareSize, squareSize));
    controlSquare.setFillColor(sf::Color(0, 0, 0, 0));  // Semi-transparent black
    controlSquare.setPosition((width - squareSize) / 2, (height - squareSize) / 1.5);

    // Player 1 Controls text (inside the square)
    player1Controls.setFont(font);
    player1Controls.setFillColor(sf::Color::White);
    player1Controls.setString("Player 1: WAD to move\nS to shoot");
    player1Controls.setCharacterSize(30);
    player1Controls.setPosition(
        controlSquare.getPosition().x + (squareSize - player1Controls.getGlobalBounds().width) / 2,
        controlSquare.getPosition().y + squareSize / 4 - player1Controls.getGlobalBounds().height
    );

    // Player 2 Controls text (inside the square)
    player2Controls.setFont(font);
    player2Controls.setFillColor(sf::Color::White);
    player2Controls.setString("Player 2: Arrow keys to move\nDown arrow to shoot");
    player2Controls.setCharacterSize(30);
    player2Controls.setPosition(
        controlSquare.getPosition().x + (squareSize - player2Controls.getGlobalBounds().width) / 2,
        controlSquare.getPosition().y + squareSize / 2
    );
}

void cControlMenu::draw(sf::RenderWindow& window) {
    // Draw the background first
    window.draw(backgroundSprite);

    // Draw title, square, control instructions, and "Back" button
    window.draw(title);
    window.draw(controlSquare);
    window.draw(player1Controls);
    window.draw(player2Controls);
    for (int i = 0; i < MAX_SCORES; i++) {
        window.draw(scoreTexts[i]);
    }
    window.draw(menu[0]);
}

void cControlMenu::MoveUp() {
    if (selectedItemIndex > 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

void cControlMenu::MoveDown() {
    if (selectedItemIndex < 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

int cControlMenu::GetPressedItem() {
    return selectedItemIndex;
}
