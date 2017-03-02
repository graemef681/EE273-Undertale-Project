#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class Destination : public sf::RectangleShape
{
public:
	//Default Constructor
	Destination();
	//Overloaded Constructor -- String must be of type sf::Color option for basic functionality
	Destination(sf::Vector2f size, sf::Vector2f position, std::string name, float speed_avg);
	~Destination();
protected:
	std::string name;
	float speed_limit;
public:
	// calculates distance from another instance of destination
	double distance_from(Destination d2);
	float getSpeed();
	std::string getName();
};