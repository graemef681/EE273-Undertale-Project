#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class Destination
{
public:
	//Default Constructor
	Destination();
	//Overloaded Constructor -- String must be of type sf::Color option for basic functionality
	Destination(sf::Vector2f size, sf::Vector2f position);
	~Destination();
protected:
	std::string name;
	sf::RectangleShape location_entity;
	int speed_limit;
public:
	// calculates distance from another instance of destination
	double distance_from(Destination d2);
	sf::RectangleShape Draw();
};

