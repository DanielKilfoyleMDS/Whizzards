#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(std::string _FilePath, std::string _PlayerName)
{
	setSprite(_FilePath);
	playerSprite.setOrigin(playerTexture.getSize().x / 2, playerTexture.getSize().y / 2);
	playerPosition = sf::Vector2f(400, 300);
	//playerSprite.setPosition(playerPosition);
	playerName = _PlayerName;

	//Default wand
	currentWand = WandType::Basic;

	if (playerName == "Player 1")
	{
		forwardMoveKey = sf::Keyboard::W;
		leftRotateKey = sf::Keyboard::A;
		rightRotateKey = sf::Keyboard::D;
		castSpellKey = sf::Keyboard::S;

	}
	else if (playerName == "Player 2")
	{
		forwardMoveKey = sf::Keyboard::Up;
		leftRotateKey = sf::Keyboard::Left;
		rightRotateKey = sf::Keyboard::Right;
		castSpellKey = sf::Keyboard::Down;
	}
}

void PlayerCharacter::Draw()
{
	windowRef->draw(playerSprite);
}

void PlayerCharacter::movePlayer()
{
	std::cout << playerName << " position: " << getPosition().x << " , " << getPosition().y << std::endl;
	
	//playerSprite.move(playerSpeedScalar * sin(radiansRotation), playerSpeedScalar * -cos(radiansRotation));
	sf::Vector2f newPos(playerSpeedScalar * sin(radiansRotation), playerSpeedScalar * -cos(radiansRotation));
	setPosition(getPosition() + newPos);
	//SetPosition(playerSprite.getPosition());
	
}

void PlayerCharacter::rotatePlayer(sf::Keyboard::Key _Key)
{

	if (_Key == leftRotateKey)
	{
		playerRotation -= 5.f;
		playerSprite.setRotation(playerRotation);
		convertRotation();
	}

	else if (_Key == rightRotateKey)
	{
		playerRotation += 5.f;
		playerSprite.setRotation(playerRotation);
		convertRotation();
	}
	//switch (_Key)
	//{
	//
	//case sf::Keyboard::A:
	//	playerRotation -= 2.f;
	//	playerSprite.setRotation(playerRotation);
	//	convertRotation();
	//	break;
	//case sf::Keyboard::D:
	//	playerRotation += 2.f;
	//	playerSprite.setRotation(playerRotation);
	//	convertRotation();
	//	break;
	//default:
	//	break;
	//}
}

void PlayerCharacter::castSpell()
{

}

void PlayerCharacter::convertRotation()
{
	radiansRotation =  playerRotation * (PI / 180);
}

void PlayerCharacter::processInput()
{
	
		// if (sf::Keyboard::isKeyPressed(forwardMoveKey))
		// {
		// 	movePlayer();
		// }
		// if (sf::Keyboard::isKeyPressed(leftRotateKey))
		// {
		// 	rotatePlayer(sf::Keyboard::A);
		// }
		// if (sf::Keyboard::isKeyPressed(rightRotateKey))
		// {
		// 	rotatePlayer(sf::Keyboard::D);
		// }

		if (sf::Keyboard::isKeyPressed(forwardMoveKey))
		{
			if (sf::Keyboard::isKeyPressed(leftRotateKey))
			{
				rotatePlayer(leftRotateKey);
			}
			else if (sf::Keyboard::isKeyPressed(rightRotateKey))
			{
				rotatePlayer(rightRotateKey);
			}
			movePlayer();
		}
	

}

void PlayerCharacter::setSprite(std::string _FilePath)
{
	playerTexture.loadFromFile(_FilePath);
	playerSprite.setTexture(playerTexture);
}

//wands

void PlayerCharacter::setCurrentWand(WandType wand) {
	// Comment out actual setting logic
	// currentWand = wand;

	// Replace with debug output
	std::cout << "Current wand set to: " << static_cast<int>(wand) << std::endl;
}

void PlayerCharacter::shoot() {
	// Comment out actual shooting logic
	/*
	switch (currentWand) {
		case WandType::Basic:
			shootSingle();
			break;
		case WandType::Spread:
			shootSpread();
			break;
		case WandType::Multi:
			shootMulti();
			break;
	}
	*/

	// Replace with debug output
	std::cout << "Shooting with wand type: " << static_cast<int>(currentWand) << std::endl;
}

void PlayerCharacter::shootSingle() {
	// Logic for single shot
	std::cout << "Single Shot Fired!" << std::endl;
}

void PlayerCharacter::shootSpread() {
	// Fire three projectiles at 45 degree angle differences
	std::cout << "Spread Shot Fired!" << std::endl;
	// Fire three projectiles at angles of -22.5, 0, and +22.5 degrees
	// Create three projectiles and rotate them by those angles
}

void PlayerCharacter::shootMulti() {
	// Fire three projectiles in quick succession
	std::cout << "Multi Shot Fired!" << std::endl;
	// Logic for rapid fire (add a timer or delay between shots)
}
