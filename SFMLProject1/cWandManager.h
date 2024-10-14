#pragma once
#include "cWand.h"
#include "cBurstWand.h"
#include "cWandPickup.h"
#include "cLevelLoader.h"
#include <vector>

class cWandManager {
public:
    cWandManager(sf::Sprite* _pickupSprite);
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

    sf::Sprite* m_wandPickupSprite;

    std::vector<cWand*> m_wandTypes; // Store wand instances
    std::vector<cWandPickup*>* m_wandDrops; // Store wand instances
};


