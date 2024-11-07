#include "cScoreMenu.h"
#include <fstream>
#include <iostream>
#include <algorithm>

cScoreMenu::cScoreMenu(float width, float height) : selectedItemIndex(0) {
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
    title.setString("Top Scores");
    title.setCharacterSize(100);
    title.setPosition(sf::Vector2f((width - title.getGlobalBounds().width) / 2, height / 20));

    // Setup "Back" button (centered at the bottom)
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Yellow);
    menu[0].setString("Back");
    menu[0].setCharacterSize(50);
    menu[0].setPosition(sf::Vector2f((width - menu[0].getGlobalBounds().width) / 2, height - 100));

    // Initialize score texts (shifted slightly to the left)
    float scoreOffset = 50.0f; // Adjust this value as needed
    for (int i = 0; i < MAX_SCORES; i++) {
        scoreTexts[i].setFont(font);
        scoreTexts[i].setFillColor(sf::Color::White);
        scoreTexts[i].setCharacterSize(40);
        // Adjust X position to move slightly left
        scoreTexts[i].setPosition(sf::Vector2f((width - scoreTexts[i].getGlobalBounds().width) / 2 - scoreOffset, height / 3 + i * 50));
    }
}

void cScoreMenu::loadScores(const std::string& filename) {
    scores.clear();
    std::ifstream file(filename);
    int score;
    while (file >> score) {
        scores.push_back(score);
    }
    file.close();

    // Sort scores in descending order and keep only the top 5
    std::sort(scores.rbegin(), scores.rend());
    scores.resize(std::min<int>(scores.size(), MAX_SCORES));

    // Update the score texts
    for (int i = 0; i < MAX_SCORES; i++) {
        if (i < scores.size()) {
            scoreTexts[i].setString(std::to_string(i + 1) + ". " + std::to_string(scores[i]));
        }
        else {
            scoreTexts[i].setString(std::to_string(i + 1) + ". ---");
        }
    }
}

void cScoreMenu::draw(sf::RenderWindow& window) {
    // Draw the background first
    window.draw(backgroundSprite);

    // Draw title, scores, and "Back" button
    window.draw(title);
    for (int i = 0; i < MAX_SCORES; i++) {
        window.draw(scoreTexts[i]);
    }
    window.draw(menu[0]);
}

void cScoreMenu::MoveUp() {
    if (selectedItemIndex > 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

void cScoreMenu::MoveDown() {
    if (selectedItemIndex < 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

int cScoreMenu::GetPressedItem() {
    return selectedItemIndex;
}
