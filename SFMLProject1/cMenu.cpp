#include "cMenu.h"
#include <iostream>

cMenu::cMenu(float width, float height) {
    if (!font.loadFromFile("Resources/Fonts/Wizard.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    // Setup title
    title.setFont(font);
    title.setFillColor(sf::Color::Yellow);
    title.setString("WHIZZARDS");
    title.setCharacterSize(100);
    title.setPosition(sf::Vector2f(width / 2 - 300, height / 6));

    // Setup "Play" button
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);  // Initially selected
    menu[0].setString("Play");
    menu[0].setCharacterSize(50);
    menu[0].setPosition(sf::Vector2f(width / 2 - 100, height / 2));

    // Setup "Scores" button
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Scores");
    menu[1].setCharacterSize(50);
    menu[1].setPosition(sf::Vector2f(width / 2 - 100, height / 2 + 100));

    // Setup "Quit" button
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Quit");
    menu[2].setCharacterSize(50);
    menu[2].setPosition(sf::Vector2f(width / 2 - 100, height / 2 + 200));

    selectedItemIndex = 0;
}

void cMenu::draw(sf::RenderWindow& window) {
    window.draw(title);
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(menu[i]);
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
