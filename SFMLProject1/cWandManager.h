#pragma once
#include "cWand.h"
#include "cLevelLoader.h"
#include <vector>

class cWandManager {
public:
    cWandManager();
    ~cWandManager();

    std::vector<std::shared_ptr<cWand>> getWands() const {
        return cWands; // wands should be a member variable holding the wand instances
    }

    float distance(const sf::Vector2f& point1, const sf::Vector2f& point2);

    sf::Vector2f getPosition() const;
    void spawnWand(sf::Vector2f _position);
    void update(float _deltaTime);
    void checkCollision(cPlayer* _player);

    void render(sf::RenderWindow& window);

private:
    std::vector<cWand*> m_vWands;
    sf::Vector2f position;
    std::vector<std::shared_ptr<cWand>> cWands; // Store wand instances
};


