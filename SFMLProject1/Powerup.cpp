#include "Powerup.h"
#include <iostream>

Powerup::Powerup(WandType wandType, sf::Vector2f pos) : wand(wandType, pos), velocity(sf::Vector2f(0.f, 20.f)) {
    std::cout << "Powerup created at: " << pos.x << ", " << pos.y << " with WandType: " << static_cast<int>(wandType) << std::endl;
}

void Powerup::update(float deltaTime) {
    // Comment out movement logic
    // sf::Vector2f pos = sf::Vector2f(wand.getBounds().left, wand.getBounds().top);
    // pos.y += velocity.y * deltaTime;
    // wand.setPosition(pos);

    // Replace with debug output
    std::cout << "Powerup updated. Delta time: " << deltaTime << std::endl;
}

void Powerup::draw(sf::RenderWindow& window) {
    // Comment out draw logic
    // wand.draw(window);

    // Replace with debug output
    std::cout << "Drawing powerup" << std::endl;
}

sf::FloatRect Powerup::getBounds() {
    // Replace with dummy bounds for testing
    std::cout << "Returning dummy bounds for powerup" << std::endl;
    return sf::FloatRect(0, 0, 50.0f, 50.0f);  // Dummy bounding box
}

Wand& Powerup::getWand() {
    return wand;  // Return the wand object
}
