#pragma once
#include "cWandManager.h"
#include "cBurstWand.h"
#include "cCollisionManager.h"
#include <cmath>

cWandManager::cWandManager() {}

cWandManager::~cWandManager() {
    for (auto wand : m_vWands) {
        delete wand;
    }
}

float distance(const sf::Vector2f& point1, const sf::Vector2f& point2) {
    return std::sqrt(std::pow(point1.x - point2.x, 2) + std::pow(point1.y - point2.y, 2));
}

float cWandManager::distance(const sf::Vector2f& point1, const sf::Vector2f& point2)
{
    return 0.0f;
}

sf::Vector2f cWandManager::getPosition() const
{
    return sf::Vector2f();
}

void cWandManager::spawnWand(sf::Vector2f _position) {
    cWand* newWand = new cBurstWand();
    newWand->setPosition(_position);  // Now this method exists in cWand
    m_vWands.push_back(newWand);
}

void cWandManager::update(float _deltaTime) {
    // Handle wand updates (e.g., despawn logic)
}

// Usage in your checkCollision function
void cWandManager::checkCollision(cPlayer* _player) {
    const float collisionThreshold = 50.0f;  // Define the threshold
    for (auto& wand : m_vWands) {
        if (distance(_player->getPosition(), wand->getPosition()) < collisionThreshold) {
            wand->applyEffect(_player);
            // Optionally: remove the wand after collecting
        }
    }
}

void cWandManager::render(sf::RenderWindow& window) {
    for (const auto& wand : m_vWands) {
        sf::Sprite wandSprite = wand->getSprite();
        wandSprite.setPosition(wand->getPosition());
        window.draw(wandSprite);
    }
}

