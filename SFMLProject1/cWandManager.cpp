#pragma once
#include "cWandManager.h"
#include "cBurstWand.h"
#include "cWandPickup.h"
#include "cCollisionManager.h"
#include <cmath>
#include "MathLibrary.h"

cWandManager::cWandManager(sf::Sprite* _pickupSprite)
{
    m_wandDrops = new std::vector<cWandPickup*>;
    m_wandPickupSprite = _pickupSprite;

    cBurstWand* BurstWandType = new cBurstWand;
    m_wandTypes.push_back(BurstWandType);
}

cWandManager::~cWandManager() {
    //for (auto wand : *m_wandTypes) {
    //    delete wand;
    //}
}

float distance(const sf::Vector2f& point1, const sf::Vector2f& point2) {
    return std::sqrt(std::pow(point1.x - point2.x, 2) + std::pow(point1.y - point2.y, 2));
}

std::vector<cWandPickup*> cWandManager::getWandPickups()
{
    return *m_wandDrops;
}

float cWandManager::distance(const sf::Vector2f& point1, const sf::Vector2f& point2)
{
    return 0.0f;
}



void cWandManager::spawnWand() {

    int Size = m_wandTypes.size();
    int WandChoice = 0;
    if (Size > 0)
    {
        if (Size == 1) WandChoice == 1;
        else WandChoice = randRangeInt(0, m_wandTypes.size() - 1);

        cWand* NewWand = m_wandTypes[WandChoice];

        cWandPickup* NewWandPickup = new cWandPickup(NewWand, sf::Vector2f(50, 50), m_wandPickupSprite);
        m_wandDrops->push_back(NewWandPickup);
    }
}

void cWandManager::addWandType(cWand* Wand)
{
    m_wandTypes.push_back(Wand);
}

void cWandManager::update(float _deltaTime) {
    // Handle wand updates (e.g., despawn logic)
    if (m_wandDrops->size() < 1)
    {
        spawnWand();
    }
}

// Usage in your checkCollision function
//void cWandManager::checkCollision(cPlayer* _player) {
//    const float collisionThreshold = 50.0f;  // Define the threshold
//    for (auto& wand : m_vWands) {
//        if (distance(_player->getPosition(), wand->getPosition()) < collisionThreshold) {
//            wand->applyEffect(_player);
//            // Optionally: remove the wand after collecting
//        }
//    }
//}

//void cWandManager::render(sf::RenderWindow& window) {
//    for (const auto& wand : m_vWands) {
//        sf::Sprite wandSprite = wand->getSprite();
//        wandSprite.setPosition(wand->getPosition());
//        window.draw(wandSprite);
//    }
//}

