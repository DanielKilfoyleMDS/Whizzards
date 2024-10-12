#include "cEnemySpawner.h"
#include "MathLibrary.h"
#include <fstream>
#include <sstream>
#include <filesystem>

void cEnemySpawner::LoadSpawnPoints(const std::string& filename)
{
	std::string fullPath = "Resources/Levels/" + filename; // Build the full path
	std::ifstream file(fullPath);
	if (!file.is_open())
	{
		std::cerr << "Failed to open spawn points file: " << fullPath << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		float x, y;
		char comma; // To skip the comma if you have a comma-separated format

		// Assuming the spawn points are in the format: x,y
		if (iss >> x >> comma >> y) // Read x and y values
		{
			m_SpawnPoints.emplace_back(x, y); // Store the spawn point
			std::cout << "Loaded spawn point: (" << x << ", " << y << ")" << std::endl; // Debug output
		}
		else
		{
			std::cerr << "Invalid line format in spawn points file: " << line << std::endl; // Handle parsing errors
		}
	}

	file.close();
	std::cout << "Finished loading spawn points. Total spawn points loaded: " << m_SpawnPoints.size() << std::endl;
}


//cEnemySpawner::cEnemySpawner(int _basePoints, int _wavePointGain, cEnemyPool* _Pool, int _enemiesOnScreen, int _enemiesTotal)
//{
//	m_icurrentWave = 0;
//	m_iwavePointGain = _wavePointGain;
//	m_ibasePoints = _basePoints;
//	m_icurrentPoints = CalculateWavePoints();
//
//	m_EnemyPoolRef = _Pool;
//	m_imaxEnemiesAtOnce = _enemiesOnScreen;
//	m_imaxEnemiesInWave = _enemiesTotal;
//}
cEnemySpawner::cEnemySpawner(int _basePoints, int _wavePointGain, cEnemyPool* _Pool)
{
	m_icurrentWave = 0;
	m_iwavePointGain = _wavePointGain;
	m_ibasePoints = _basePoints;
	m_icurrentPoints = CalculateWavePoints();

	m_EnemyPoolRef = _Pool;
	m_imaxEnemiesAtOnce = m_EnemyPoolRef->GetInactiveEnemies().size();
	m_imaxEnemiesInWave = m_imaxEnemiesAtOnce * 2;

	// Load spawn points from the file
	LoadSpawnPoints("spawn_points.txt");
}


cEnemySpawner::~cEnemySpawner()
{
}

void cEnemySpawner::WaveManager()
{
	m_EnemyPoolRef->tickEnemies();

	//Check if there are no enemies left on screen
	if (m_EnemyPoolRef->GetActiveEnemies().size() == 0)
	{
		m_icurrentWave++;
		std::cout << "StartingWave" << std::endl;
		StartWave();
	}
	
	//Check if there are still points to spawn and room for another enemy
	if (m_icurrentPoints > 0 && m_EnemyPoolRef->GetActiveEnemies().size() < m_imaxEnemiesAtOnce) 
	{
		//Spawning additional enemies per wave can go here - BETA SPRINT GOAL
	}

}


int cEnemySpawner::CalculateWavePoints()
{
	int Points = m_ibasePoints + (m_icurrentWave * m_iwavePointGain);
	if (Points > m_imaxEnemiesAtOnce * 2) //Set to highest cost enemy - maybe make these const member variables
	{
		Points = m_imaxEnemiesAtOnce * 2;
	}
	return Points;
}

void cEnemySpawner::StartWave() {
	m_icurrentPoints = CalculateWavePoints();
	int EnemiesSpawned = 0;
	bool CanSpawn = true;

	while (CanSpawn) {
		if (m_icurrentPoints > 0 && m_EnemyPoolRef->GetActiveEnemies().size() < m_imaxEnemiesAtOnce) {
			// Ensure there are spawn points available
			if (!m_SpawnPoints.empty()) {
				// Get a random spawn position
				int spawnIndex = randRangeInt(0, m_SpawnPoints.size() - 1);
				sf::Vector2f spawnPosition = m_SpawnPoints[spawnIndex];

				// Call SpawnEnemy with the position
				SpawnEnemy(spawnPosition); // Pass the spawn position
				EnemiesSpawned++;
			}
			else {
				CanSpawn = false; // No spawn points available
			}
		}
		else {
			CanSpawn = false; // No more points or too many enemies on screen
		}
	}
}



//bool cEnemySpawner::SpawnEnemy()
//{
//	int EnemyChoice = 0;
//	EnemyChoice = randRangeInt(0, 1);
//	if (EnemyChoice == 0 && m_icurrentPoints >= 1)
//	{
//		return SpawnAsteroidEnemy();
//	} else if (EnemyChoice == 1 && m_icurrentPoints >= 2)
//	{
//		return SpawnRandomEnemy();
//	}
//	else if (m_icurrentPoints <= 0)
//	{
//		return false;
//	}
//	else {
//		std::cout << "Reroll" << std::endl;
//		return SpawnEnemy(); //If we reach this point, we still have points to spend.
//	}
//	
//}

bool cEnemySpawner::SpawnEnemy(sf::Vector2f position) {
	if (m_SpawnPoints.empty()) {
		std::cerr << "No spawn points available!" << std::endl;
		return false; // No spawn points available
	}

	// Get a random spawn point from the loaded list
	int spawnIndex = randRangeInt(0, m_SpawnPoints.size() - 1);
	sf::Vector2f spawnPosition = m_SpawnPoints[spawnIndex];

	// Assuming you have a way to get a sprite for the enemy
	sf::Sprite* enemySprite = new sf::Sprite(); // Create a new sprite (make sure to set texture later)

	// Create a new enemy with the required parameters
	cEnemy* newEnemy = new cEnemy(enemySprite, spawnPosition); // Use spawnPosition instead of position

	// Use the EnemyChoice to determine which enemy type to spawn
	int EnemyChoice = randRangeInt(0, 1);
	if (EnemyChoice == 0 && m_icurrentPoints >= 1) {
		if (SpawnAsteroidEnemy(spawnPosition)) {
			m_EnemyPoolRef->AddEnemy(newEnemy); // Add enemy to the pool
			return true; // Successfully spawned an asteroid enemy
		}
	}
	else if (EnemyChoice == 1 && m_icurrentPoints >= 2) {
		if (SpawnRandomEnemy(spawnPosition)) {
			m_EnemyPoolRef->AddEnemy(newEnemy); // Add enemy to the pool
			return true; // Successfully spawned a random enemy
		}
	}

	delete newEnemy; // Clean up if not spawned
	return false; // Failed to spawn an enemy
}


bool cEnemySpawner::SpawnAsteroidEnemy(sf::Vector2f spawnPosition)
{
	return m_EnemyPoolRef->loadAsteroidEnemy(spawnPosition, sf::Vector2f(1, 1), 1);
}

bool cEnemySpawner::SpawnRandomEnemy(sf::Vector2f spawnPosition)
{
	return m_EnemyPoolRef->loadRandomEnemy(spawnPosition);
}
