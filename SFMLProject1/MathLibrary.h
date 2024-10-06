#pragma once

#include "SFML/Graphics.hpp"

static float M_PI = 3.141592653f; 

inline float VectorLength(sf::Vector2f _Vector)
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

inline sf::Vector2f Normalize(sf::Vector2f _Vector)
{
	float Magnitude = VectorLength(_Vector);
	return sf::Vector2f(_Vector.x / Magnitude, _Vector.y / Magnitude);
}

inline sf::Vector2f SetVectorToLength(sf::Vector2f _Vector, float Length)
{
	sf::Vector2f Vector = Normalize(_Vector);
	return sf::Vector2f(Vector.x * Length, Vector.y * Length);
}

inline sf::Vector2f PerpendicularVector(sf::Vector2f _Vector)
{
	return sf::Vector2f(-_Vector.x, -_Vector.y);
}

inline float SignedAngleBetweenVectors(sf::Vector2f _Vector1, sf::Vector2f _Vector2)
{
	sf::Vector2f A = Normalize(_Vector1);
	sf::Vector2f B = Normalize(_Vector2);

	float C = (A.x * B.x) + (A.y * B.y);
	std::cout << C << std::endl;


	return C * 180.0f / 3.14f;

}

inline float DegreesToRadians(float _Degrees)
{
	return _Degrees * (M_PI /180);
}

inline float RadiansToDegrees(float _Radians)
{
	return _Radians * (180/ M_PI);
}

inline float randRangeFloat(float _min, float _max)
{
	return _min + static_cast <float>(rand() / (RAND_MAX / (_max - _min)));
}

inline float randRangeInt(int _min, int _max)
{
	return _min + fmod(rand(), (_max + 1) - _min);
}
