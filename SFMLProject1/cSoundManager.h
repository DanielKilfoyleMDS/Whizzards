#pragma once
#include "SFML/Audio.hpp"
#include <iostream>

class cSoundManager
{
public:
	cSoundManager();


	void playDamageSound();
	void playDeathSound();
	void playIdleSound();

	void playFireSound();
	void playHitSound();

	bool soundPlayingCheck(sf::Sound* _Sound);
	void endMusic();
private:

	// Player Sounds
	sf::SoundBuffer m_PlayerDamageBuffer;
	sf::Sound m_PlayerDamageSound;

	sf::SoundBuffer m_PlayerDeathBuffer;
	sf::Sound m_PlayerDeathSound;

	sf::SoundBuffer m_MotorcycleMoveBuffer;
	sf::Sound m_MotorcycleMoveSound;

	sf::SoundBuffer m_MotorcycleIdleBuffer;
	sf::Sound m_MotorcycleIdleSound;

	// Enemy Sounds
	sf::SoundBuffer m_EnemyDamageBuffer;
	sf::Sound m_EnemyDamageSound;

	sf::SoundBuffer m_EnemyDeathBuffer;
	sf::Sound m_EnemyDeathSound;

	// Shared Sounds
	sf::SoundBuffer m_FireProjBuffer;
	sf::Sound m_FireProjSound;

	sf::SoundBuffer m_HitProjBuffer;
	sf::Sound m_HitProjSound;


	sf::Music m_backgroundMusic;


};

