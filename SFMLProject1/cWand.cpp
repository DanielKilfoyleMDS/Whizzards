#pragma once
#include "cWand.h"

cWand::cWand() : m_fDamage(10), m_fFireRate(1.0f), m_iProjectileCount(1) 
{
    if (!wandTex.loadFromFile("Resources/Textures/Wand.png")) {
        std::cerr << "Failed to load wand texture!" << std::endl;
    }
    wandSprite.setTexture(wandTex);
    

}

cWand::~cWand() {}

void cWand::loadTexture(const std::string& texturePath)
{
}

void cWand::draw(sf::RenderWindow& window)
{
    window.draw(wandSprite);
}

void cWand::setDamage(float _damage) {
    m_fDamage = _damage;
}

void cWand::setFireRate(float _fireRate) {
    m_fFireRate = _fireRate;
}

void cWand::setProjectileCount(int _projectileCount) {
    m_iProjectileCount = _projectileCount;
}

float cWand::getDamage() {
    return m_fDamage;
}

float cWand::getFireRate() {
    return m_fFireRate;
}

int cWand::getProjectileCount() {
    return m_iProjectileCount;
}

sf::Sprite cWand::getSprite() const {
    sf::Sprite wandSprite;
    wandSprite.setTexture(wandTex); // Make sure to load the wand texture in your wand class
    return wandSprite;
}


void cWand::setPosition(const sf::Vector2f& _position) {
    m_position = _position;  // Set the position of the wand
}

sf::Vector2f cWand::getPosition() const {
    return m_position;  // Return the wand's position
}

