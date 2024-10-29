#pragma once
#include "cWand.h"
#include "cPlayer.h"

class cBurstWand : public cWand {
public:
    cBurstWand();
    virtual ~cBurstWand();

    std::string getName() const override { return "Burst Wand"; }

    // Apply burst effect on player
    void applyEffect(cPlayer* _player) override;

    void castSpell(sf::Vector2f _PlayerPos, float _playerRot, sf::Sprite _projSprite, std::vector<cProjectile*>* _ProjList) override;

    // Implement the pure virtual function from cWand
    void draw(sf::RenderWindow& window) override {
        // Implement the draw function
        window.draw(wandSprite);
    }

//private:
//    sf::Sprite wandSprite; // Your sprite for the wand
};