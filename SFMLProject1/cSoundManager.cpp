#include "cSoundManager.h"

cSoundManager::cSoundManager()
{
	if (!m_backgroundMusic.openFromFile("Resources/Audio/Music/Whizzards-BackgroundMusic.WAV"))
		std::cout << "Failed to load background music." << std::endl; // error
	m_backgroundMusic.play();

	if (!m_PlayerDamageBuffer.loadFromFile("Resources/Audio/Player/PlayerHealth/Damage.WAV"))
		std::cout << "Error Loading Damage Sound";
	m_PlayerDamageSound.setBuffer(m_PlayerDamageBuffer);

	if (!m_PlayerDeathBuffer.loadFromFile("Resources/Audio/Player/PlayerHealth/Death.WAV"))
		std::cout << "Error Loading Death Sound";
	m_PlayerDeathSound.setBuffer(m_PlayerDeathBuffer);

	if (!m_MotorcycleIdleBuffer.loadFromFile("Resources/Audio/Player/Motorcycle/NewIdle.wav"))
		std::cout << "Error Loading Motorcycle Idle Sound";
	m_MotorcycleIdleSound.setBuffer(m_MotorcycleIdleBuffer);

	if (!m_FireProjBuffer.loadFromFile("Resources/Audio/Projectile/FireSpellCast.WAV"))
		std::cout << "Error Loading Projectile Fire Sound";
	m_FireProjSound.setBuffer(m_FireProjBuffer);


	if (!m_HitProjBuffer.loadFromFile("Resources/Audio/Projectile/ProjectileHit.WAV"))
		std::cout << "Error Loading Projectile Hit Sound";
	m_HitProjSound.setBuffer(m_HitProjBuffer);

}



void cSoundManager::playDamageSound()
{
	if (!soundPlayingCheck(&m_PlayerDamageSound))
	{
		m_PlayerDamageSound.play();
	}
}

void cSoundManager::playDeathSound()
{
	if (!soundPlayingCheck(&m_PlayerDeathSound))
	{
		m_PlayerDeathSound.play();
	}
}

void cSoundManager::playIdleSound()
{
	if (!soundPlayingCheck(&m_MotorcycleIdleSound))
	{
		m_MotorcycleIdleSound.play();
	}
}

void cSoundManager::playFireSound()
{
	if (!soundPlayingCheck(&m_FireProjSound))
	{
		m_FireProjSound.play();
	}
}

void cSoundManager::playHitSound()
{
	if (!soundPlayingCheck(&m_HitProjSound))
	{
		m_HitProjSound.play();
	}
}

bool cSoundManager::soundPlayingCheck(sf::Sound* _Sound)
{
	return (_Sound->getStatus() == sf::SoundSource::Playing);
}

void cSoundManager::endMusic()
{
	m_backgroundMusic.~Music();
}

