#pragma once
#include "cWand.h"
#include "cBurstWand.h"
#include "cWandPickup.h"
#include "cLevelLoader.h"
#include <vector>

class cWandManager {
public:
    cWandManager(sf::Sprite* _pickupSprite, std::vector<sf::Vector2f>* _wandSpawns);
    ~cWandManager();

    std::vector<cWand*> getWands() const {
        return m_wandTypes; // wands should be a member variable holding the wand instances
    }

    std::vector<cWandPickup*> getWandPickups();

    float distance(const sf::Vector2f& point1, const sf::Vector2f& point2);

    void spawnWand();
    void addWandType(cWand* Wand);

    void update(float _deltaTime);

private:

    int m_maxWandSpawns = 5;
    float m_spawnTimeMin = 20;
    float m_spawnTimeMax = 60;
    float m_spawnTick = 5; //also sets time before first wand

    sf::Sprite* m_wandPickupSprite;

    std::vector<cWand*> m_wandTypes; // Store wand instances
    std::vector<cWandPickup*> m_wandDrops; // Store wand instances
    std::vector<sf::Vector2f> m_wandSpawnPoints;
};


