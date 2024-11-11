#include "cMenu.h"
#include <iostream>

cMenu::cMenu(float width, float height) {
    // Load font
    if (!font.loadFromFile("Resources/Fonts/Wizard.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    // Load background texture
    if (!backgroundTexture.loadFromFile("Resources/Textures/MainMenuBackground.png")) {
        std::cerr << "Failed to load main menu background image!" << std::endl;
    }
    else {
        // Set background sprite and scale to fit window
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(
            width / backgroundTexture.getSize().x,
            height / backgroundTexture.getSize().y
        );
    }

    float TitleMargin = 50.0f;
    float rightMargin = 225.0f;

    // Setup title
    title.setFont(font);
    title.setFillColor(sf::Color::White);
    title.setString("WHIZZARDS");
    title.setCharacterSize(100);
    title.setPosition(sf::Vector2f(width - title.getGlobalBounds().width - TitleMargin, height / 60));

    // Setup menu items
    std::string labels[] = { "Play", "Scores", "Control", "Quit"};
    float maxWidth = 0.0f;

    // Determine the maximum width of the menu items
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        menu[i].setFont(font);
        menu[i].setString(labels[i]);
        menu[i].setCharacterSize(50);
        float itemWidth = menu[i].getGlobalBounds().width;
        if (itemWidth > maxWidth) {
            maxWidth = itemWidth;
        }
    }

    // Center-align menu items based on maxWidth
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        menu[i].setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::Black);  // Highlight the first item
        menu[i].setPosition(sf::Vector2f(width - maxWidth - rightMargin, height / 3 + i * 100));
    }

    selectedItemIndex = 0;
}

void cMenu::draw(sf::RenderWindow& window) {
    // Draw the background first
    window.draw(backgroundSprite);

    // Draw title and menu items
    window.draw(title);
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(menu[i]);
    }
}

void cMenu::MoveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::Black);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

void cMenu::MoveDown() {
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
        menu[selectedItemIndex].setFillColor(sf::Color::Black);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

int cMenu::GetPressedItem() {
    return selectedItemIndex;
}
