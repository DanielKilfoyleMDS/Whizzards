#pragma once
#include "Wand.h"

class Powerup {
public:
    Powerup(WandType wandType, sf::Vector2f position); // Create a wand powerup
    void update(float deltaTime);                      // Update movement
    void draw(sf::RenderWindow& window);               // Draw the powerup
    sf::FloatRect getBounds();                         // Get bounding box

    Wand& getWand();  // Retrieve the wand object

private:
    Wand wand;  // The wand this powerup represents
    sf::Vector2f velocity;
};
