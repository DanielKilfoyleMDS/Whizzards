#include "cMenu.h"
#include <iostream>

cMenu::cMenu(float width, float height) {
    if (!font.loadFromFile("Resources/Fonts/Wizard.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    // Setup title
    title.setFont(font);
    title.setFillColor(sf::Color::Yellow);  // Set color
    title.setString("WHIZZARDS");           // Set the title text
    title.setCharacterSize(100);            // Set a larger size for the title
    title.setPosition(sf::Vector2f(width / 2 - 300, height / 6));  // Adjust position

    // Setup "Play" button
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Play");
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

void cMenu::draw(sf::RenderWindow& window) {
    window.draw(title);  // Draw the title first
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(menu[i]);  // Draw the menu items
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
