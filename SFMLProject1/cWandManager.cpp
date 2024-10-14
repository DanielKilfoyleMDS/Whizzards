#pragma once
#include "cWandManager.h"
#include "cBurstWand.h"
#include "cWandPickup.h"
#include "cCollisionManager.h"
#include <cmath>
#include "MathLibrary.h"

cWandManager::cWandManager(sf::Sprite* _pickupSprite, std::vector<sf::Vector2f>* _wandSpawns)
{
    m_wandDrops = new std::vector<cWandPickup*>;
    m_wandPickupSprite = _pickupSprite;

    cBurstWand* BurstWandType = new cBurstWand;
    m_wandTypes.push_back(BurstWandType);
    m_wandSpawnPoints = *_wandSpawns;
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

    int WandsSize = m_wandTypes.size();
    int SpawnsSize = m_wandSpawnPoints.size();
    int WandChoice = 0;
    int SpawnPointChoice = 0;
    if (WandsSize > 0 && SpawnsSize > 0)
    {
        if (WandsSize == 1) WandChoice == 1;
        else WandChoice = randRangeInt(0, WandsSize - 1);

        if (SpawnsSize == 1) SpawnPointChoice = 1;
        else SpawnPointChoice = randRangeInt(0, SpawnsSize - 1);

        cWand* NewWand = m_wandTypes[WandChoice];
        sf::Vector2f SpawnPoint = m_wandSpawnPoints[SpawnPointChoice];

        cWandPickup* NewWandPickup = new cWandPickup(NewWand, SpawnPoint, m_wandPickupSprite);
        m_wandDrops->push_back(NewWandPickup);
    }
}

void cWandManager::addWandType(cWand* Wand)
{
    m_wandTypes.push_back(Wand);
}

void cWandManager::update(float _deltaTime) {
    // Handle wand updates (e.g., despawn logic)

    if (m_wandDrops->size() < m_maxWandSpawns)
    {
        m_spawnTick -= _deltaTime;

        if (m_spawnTick <= 0)
        {
            spawnWand();
            m_spawnTick = randRangeFloat(m_spawnTimeMin, m_spawnTimeMax);
        }

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

