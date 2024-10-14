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
