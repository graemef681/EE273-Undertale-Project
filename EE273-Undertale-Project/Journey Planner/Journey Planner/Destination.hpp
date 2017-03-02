#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include<list>
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
	std::string* neighbours;
public:
	// calculates distance from another instance of destination
	double distance_from(Destination d2);
	float getSpeed();
	std::string getName();
	void setNeighbours(std::string*);
};