#include "Wand.h"
#include <iostream>  // For debug output

Wand::Wand(WandType type, sf::Vector2f pos) : wandType(type), position(pos) {
    // Commenting out the texture loading logic
    // Replace with debug output

    /*
    switch (wandType) {
        case WandType::Basic:
            wandTexture.loadFromFile("Resources/Wands/BasicWand.png");
            break;
        case WandType::Spread:
            wandTexture.loadFromFile("Resources/Wands/SpreadWand.png");
            break;
        case WandType::Multi:
            wandTexture.loadFromFile("Resources/Wands/MultiWand.png");
            break;
    }
    */
    std::cout << "Wand created at position: " << pos.x << ", " << pos.y << " with type: " << static_cast<int>(wandType) << std::endl;
    wandSprite.setPosition(position);
}

void Wand::applyEffect(PlayerCharacter& player) {
    // Comment out actual logic
    // player.setCurrentWand(wandType);

    // Replace with debug output
    std::cout << "Applying wand effect: " << static_cast<int>(wandType) << " to player" << std::endl;
}

void Wand::draw(sf::RenderWindow& window) {
    // Comment out the draw logic for now
    // window.draw(wandSprite);

    // Replace with debug output
    std::cout << "Drawing wand at position: " << position.x << ", " << position.y << std::endl;
}

sf::FloatRect Wand::getBounds() {
    // Comment out actual bounds logic
    // return wandSprite.getGlobalBounds();

    // Replace with a dummy bounding box for testing
    std::cout << "Returning dummy bounds for wand" << std::endl;
    return sf::FloatRect(position.x, position.y, 50.0f, 50.0f);  // Dummy bounding box
}

void Wand::setPosition(sf::Vector2f pos) {
    position = pos;
    wandSprite.setPosition(position);  // Still valid to set position
    std::cout << "Wand position set to: " << pos.x << ", " << pos.y << std::endl;
}
