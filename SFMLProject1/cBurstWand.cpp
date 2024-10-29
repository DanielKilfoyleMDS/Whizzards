#pragma once
#include "cBurstWand.h"

cBurstWand::cBurstWand() 
{
    // Set specific attributes for burst wand
    setDamage(15); // More damage
    setFireRate(0.5f); // Faster fire rate
    setProjectileCount(3); // Fires 3 projectiles
}

cBurstWand::~cBurstWand() {}

void cBurstWand::applyEffect(cPlayer* _player) {
    _player->setProjectileCount(getProjectileCount());
    _player->setFireRate(getFireRate());
    _player->setDamageStrength(getDamage());
}

void cBurstWand::castSpell(sf::Vector2f _PlayerPos, float _playerRot, sf::Sprite _projSprite, std::vector<cProjectile*>* _ProjList)
{


    for (int i = -1; i < m_iProjectileCount - 1; i++)
    {
        cProjectile* newProjectile = new cProjectile(_projSprite, _PlayerPos, _playerRot + (30 * i), false);
        _ProjList->push_back(newProjectile);
    }
}