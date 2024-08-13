#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

float M_PI = 3.141592653589793; //15 places because idk why not

float VectorLength(sf::Vector2f _Vector)
{
	if (_Vector.x == 0 && _Vector.y == 0)
	{
		return 0;
	}
	else if (_Vector.x == 0)
	{
		return sqrt(_Vector.y * _Vector.y);
	}
	else if (_Vector.y == 0)
	{
		return sqrt(_Vector.x * _Vector.x);
	}
	return sqrt((_Vector.x * _Vector.x) + (_Vector.y * _Vector.y));
}

sf::Vector2f Normalize(sf::Vector2f _Vector)
{
	float Magnitude = VectorLength(_Vector);
	return sf::Vector2f(_Vector.x / Magnitude, _Vector.y / Magnitude);
}

sf::Vector2f SetVectorToLength(sf::Vector2f _Vector, float Length)
{
	sf::Vector2f Vector = Normalize(_Vector);
	return sf::Vector2f(Vector.x * Length, Vector.y * Length);
}

sf::Vector2f PerpendicularVector(sf::Vector2f _Vector)
{
	return sf::Vector2f(-_Vector.x, -_Vector.y);
}

float SignedAngleBetweenVectors(sf::Vector2f _Vector1, sf::Vector2f _Vector2)
{
	sf::Vector2f A = Normalize(_Vector1);
	sf::Vector2f B = Normalize(_Vector2);

	float C = (A.x * B.x) + (A.y * B.y);
	std::cout << C << std::endl;
	return C;

	//float Angle1 = atan2(_Vector1.y, _Vector1.x);
	//float Angle2 = atan2(_Vector2.y, _Vector2.x);

	//float Angle3 = Angle2 - Angle1;
	//if (Angle3 > M_PI) {
	//	Angle3 -= 2 * M_PI;
	//}
	//else if (Angle3 <= -M_PI) {
	//	Angle3 += 2 * M_PI;
	//}

	//return Angle3;
}