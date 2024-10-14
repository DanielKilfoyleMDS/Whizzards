#pragma once
#include "SFML/Graphics.hpp"
#include "cPlayer.h"
#include "cProjectile.h"

class cWand {
public:
    cWand();
    ~cWand();

    void loadTexture(const std::string& texturePath);
    virtual void draw(sf::RenderWindow& window) = 0;

    virtual void applyEffect(class cPlayer* _player) = 0; // Pure virtual for specific wand effects

    sf::Sprite getSprite() const; // Method to get the wand's sprite

    virtual void castSpell(sf::Vector2f _PlayerPos, float _playerRot, sf::Sprite _projSprite, std::vector<cProjectile*>* _ProjList) = 0;

    // Methods to set and get the position
    void setPosition(const sf::Vector2f& _position);
    sf::Vector2f getPosition() const;

    // Setters for base wand attributes
    void setDamage(float _damage);
    void setFireRate(float _fireRate);
    void setProjectileCount(int _projectileCount);

    // Getters for base wand attributes
    float getDamage();
    float getFireRate();
    int getProjectileCount();

protected:
    float m_fDamage;
    float m_fFireRate;
    int m_iProjectileCount;
    sf::Vector2f m_position;  // Add position to track the wand's position
    sf::Texture wandTex; // Declare wandTex here
    sf::Sprite wandSprite; // Add a sprite to represent the wand
};