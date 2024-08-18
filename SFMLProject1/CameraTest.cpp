#include "SFML/Graphics.hpp"
#include "MathLibrary.h"

//Jayden's Notes:
//
// Some of this logic is working, but it's not working how I want just yet.
//
//
//
//


//Window resolution
const int HEIGHT = 600;
const int WIDTH = 800;


//Determines if Views should be split based on distance between player positions
bool CamerasSplit(sf::Vector2f position1, sf::Vector2f position2)
{
	//THE LOGIC: if two positions are more than half of the average of the screen width and height

	sf::Vector2f DistanceBetweenPlayers = position1 - position2;
	//Compare to half of Width and Height Average - start by converting into length
	if (VectorLength(DistanceBetweenPlayers) > (WIDTH + HEIGHT) / 4)
	{
		return true;
	}
	
	return false;
}

//Calculate camera position for the object at position 1, moving camera in the direction of position 2
sf::Vector2f viewPosition(sf::Vector2f position1, sf::Vector2f position2)
{
	//OG code states that this uses a circular area of the screen, but should probably use elipitical.
	//We'll do circle until it works, and then look at improving it

	sf::Vector2f out = position1;
	const float MAX_DISTANCE = (WIDTH + HEIGHT) / 5; //The halfway point between players. Why 5? I have no idea.
	sf::Vector2f direction = (position2 - position1) / 2.f;

	if (VectorLength(direction) > MAX_DISTANCE)
	{
		//Set the length of direction to max length... huh. 
		SetVectorToLength(direction, MAX_DISTANCE);
	}

	return out + direction;

}


int Notmain()
{
	//Basic SFML stuff
	sf::RenderWindow window;
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Testing SplitScreen");
	window.setFramerateLimit(60);

	//Players (temporary)
	sf::Vector2f playerSize(10, 10);
	sf::RectangleShape p1(playerSize), p2(playerSize);

	p1.setFillColor(sf::Color::Blue);
	p2.setFillColor(sf::Color::Red);

	const float PLAYERSPEED = 10.1f;

	//Temporary Map - Creates texture, loads temp file, changes positioning
	sf::Texture mapTex;
	mapTex.loadFromFile("Resources/map.jpg");
	sf::Sprite map(mapTex);
	map.setPosition(-sf::Vector2f(map.getLocalBounds().width / 2.f, map.getLocalBounds().height / 2.f));

	//Create two views, one for each player
	sf::View p1View = window.getView();
	sf::View p2View = window.getView();
	const float VIEWSPEED = .2f;

	//Renders other view to rendertexture
	sf::RenderTexture p2Tex;
	p2Tex.create(WIDTH, HEIGHT);
	sf::Sprite p2Sprite;

	//Rectangle - draws the divide and also blends the views
	sf::RectangleShape eraser;
	eraser.setOutlineColor(sf::Color::Black);
	eraser.setFillColor(sf::Color::Transparent);
	eraser.setOutlineThickness(3);
	eraser.setSize(sf::Vector2f(WIDTH * 2, HEIGHT * 2)); //Double the size of the width and height?
	//eraser.setOrigin(WIDTH,HEIGHT);

	while (window.isOpen())
	{
		//Handle events.
		sf::Event e;
		if (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}

		//TEMPORARY User controls.
		sf::Vector2f move;
		//Player one input.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			move.y += -1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			move.y += 1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			move.x += -1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			move.x += 1;

		p1.move(move * PLAYERSPEED);

		//Reset the move vector.
		move = sf::Vector2f();
		//Player two input.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			move.y += -1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			move.y += 1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			move.x += -1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			move.x += 1;

		p2.move(move * PLAYERSPEED);

		//Decide on splitting view
		bool singleView = true;
		sf::Vector2f IdealPosition; //The ideal location to be
		if (CamerasSplit(p1.getPosition(), p2.getPosition()))
		{
			//Split == true! Calculate ideal position
			singleView = false;
			IdealPosition = viewPosition(p1.getPosition(), p2.getPosition());
			p1View.move((IdealPosition - p1View.getCenter()) * VIEWSPEED);

			IdealPosition = viewPosition(p2.getPosition(), p1.getPosition());
			p2View.move((IdealPosition - p2View.getCenter()) * VIEWSPEED);
		}
		else
		{
			//If no split, ideal point is halfway between players
	
			IdealPosition = (p1.getPosition() + p2.getPosition()) / 2.f;
			p1View.move((IdealPosition - p1View.getCenter()) * VIEWSPEED);
			//Set Player two camera to the same as player one's
			p2View.setCenter(p1View.getCenter());
		}

		//Draw to player 1's view
		window.clear();
		window.setView(p1View);
		window.draw(map);
		window.draw(p1);
		window.draw(p2);

		//Draw to Player 2's view IF it's split
		if (!singleView)
		{
			p2Tex.clear();
			p2Tex.setView(p2View);
			p2Tex.draw(map);
			p2Tex.draw(p1);
			p2Tex.draw(p2);


			//Now placing the rectangle
			eraser.setPosition(window.mapPixelToCoords(sf::Vector2i(WIDTH / 2, HEIGHT / 2), p2View));

			//Get Perpendicular vector to line between players
			sf::Vector2f Angle = PerpendicularVector(p1.getPosition() - p2.getPosition());
			SetVectorToLength(Angle, static_cast<float>(HEIGHT));

			eraser.move(Angle); //Move Eraser along this line to stretch across screen... wrong, or above is wronf

			//Set Rotation - Uhoh, this one will be complicated.
			eraser.setRotation(-(SignedAngleBetweenVectors(Angle, sf::Vector2f(1, 1)) + 135));

			
			p2Tex.draw(eraser); //Blendmode none? 
			p2Tex.display();



			p2Sprite.setTexture(p2Tex.getTexture());
			//Draw it over the origin point
			window.setView(window.getDefaultView());
			//and Finally, Draw it to the window.
			window.draw(p2Sprite);

		}

		window.display();

	}
	return 0;
}