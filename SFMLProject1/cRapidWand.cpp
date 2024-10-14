#include "cRapidWand.h"

cRapidWand::cRapidWand()
{
    setDamage(2); // Less damage
    setFireRate(0.1f); // Faster fire rate
    setProjectileCount(1); // Fires 3 projectiles
}

cRapidWand::~cRapidWand()
{
}

void cRapidWand::applyEffect(cPlayer* _player)
{
    _player->setProjectileCount(getProjectileCount());
    _player->setFireRate(getFireRate());
    _player->setDamageStrength(getDamage());
}

void cRapidWand::castSpell(sf::Vector2f _PlayerPos, float _playerRot, sf::Sprite _projSprite, std::vector<cProjectile*>* _ProjList)
{
    cProjectile* newProjectile = new cProjectile(_projSprite, _PlayerPos, _playerRot, false);
    _ProjList->push_back(newProjectile);
}


