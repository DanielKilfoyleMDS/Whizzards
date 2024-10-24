#include "cMenu.h"
#include <iostream>

cMenu::cMenu(float width, float height) {
    if (!font.loadFromFile("Resources/Fonts/Wizard.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    // Setup "Play" button
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Play");
    menu[0].setCharacterSize(50);  // Increase text size for visibility
    menu[0].setPosition(sf::Vector2f(200, 150));  // Adjust these values

    // Setup "Quit" button
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Quit");
    menu[1].setCharacterSize(50);  // Increase text size for visibility
    menu[1].setPosition(sf::Vector2f(200, 300));  // Adjust these values


    selectedItemIndex = 0;
}

void cMenu::draw(sf::RenderWindow& window) {
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(menu[i]);  // Draw menu items
    }
}


void cMenu::MoveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void cMenu::MoveDown() {
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

int cMenu::GetPressedItem() {
    return selectedItemIndex;
}
