#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(std::string _FilePath, std::string _PlayerName)
{
	setSprite(_FilePath);
	playerSprite.setOrigin(playerTexture.getSize().x / 2, playerTexture.getSize().y / 2);
	playerPosition = sf::Vector2f(400, 300);
	playerSprite.setPosition(playerPosition);
	playerName = _PlayerName;

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
	std::cout << playerName << " position: " << playerSprite.getPosition().x << " , " << playerSprite.getPosition().y << std::endl;
	playerSprite.move(playerSpeedScalar * sin(radiansRotation), playerSpeedScalar * -cos(radiansRotation));
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

void PlayerCharacter::setSprite(std::string _FilePath)
{
	playerTexture.loadFromFile(_FilePath);
	playerSprite.setTexture(playerTexture);
}
