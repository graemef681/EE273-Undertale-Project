#include "Destination.hpp"
#include <string>
#include <iostream>

Destination::Destination()
{
	this->setSize({ 25,25 });
	this->setOrigin({ this->getSize().x / 2, this->getSize().y / 2 });
	this->setPosition({ 50,50 });
	this->setFillColor(sf::Color::White);
	speed_limit = 0;
}


Destination::Destination(sf::Vector2f size, sf::Vector2f position, std::string name, float speed_avg)
{
	this->name = name;
	this->setSize(size);
	this->setOrigin({ this->getSize().x / 2, this->getSize().y / 2 });
	this->setPosition(position);
	this->setFillColor(sf::Color::Cyan);
	speed_limit = speed_avg;
	std::cout << this->name << std::endl;
	std::cout << this->getPosition().x << "," << this->getPosition().y << std::endl;
	std::cout << this->speed_limit << std::endl;
}

Destination::~Destination()
{
}


float Destination::getSpeed()
{
	return speed_limit;
}

// calculates distance from another instance of destination
double Destination::distance_from(Destination d2)
{
	double distance;
	distance = sqrt(pow(abs(d2.getPosition().x - this->getPosition().x),2) + pow(abs(d2.getPosition().y - this->getPosition().y),2));
	return distance;
}

std::string Destination::getName()
{
	return name;
}

void Destination:: setNeighbours(std::string* neighboursArr)
{
	neighbours = neighboursArr;
}


