#pragma once
#include "PlayerCharacter.h" 
#include <SFML/Graphics.hpp>

enum class WandType { Basic, Spread, Multi };

class Wand {
public:
    Wand(WandType type, sf::Vector2f position);
    void applyEffect(PlayerCharacter& player);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds();
    void setPosition(sf::Vector2f position);

    WandType getType() const { return wandType; }

private:
    WandType wandType;
    sf::Sprite wandSprite;
    sf::Texture wandTexture;
    sf::Vector2f position;
};
