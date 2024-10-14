#pragma once
#include "cWand.h"
#include "cPlayer.h"

class cBurstWand : public cWand {
public:
    cBurstWand();
    virtual ~cBurstWand();

    // Apply burst effect on player
    void applyEffect(cPlayer* _player) override;

    // Implement the pure virtual function from cWand
    void draw(sf::RenderWindow& window) override {
        // Implement the draw function
        window.draw(wandSprite);
    }

//private:
//    sf::Sprite wandSprite; // Your sprite for the wand
};