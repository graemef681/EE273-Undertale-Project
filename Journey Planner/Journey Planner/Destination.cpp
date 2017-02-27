#include "Destination.hpp"

Destination::Destination()
{
	
	location_entity.setSize({ 50,50 });
	location_entity.setOrigin({ location_entity.getSize().x / 2, location_entity.getSize().y / 2 });
	location_entity.setPosition({ 250,250 });
	location_entity.setFillColor(sf::Color::Red);
	speed_limit = 0;
}


Destination::Destination(sf::Vector2f size, sf::Vector2f position)
{
	location_entity.setSize(size);
	location_entity.setOrigin({ location_entity.getSize().x / 2, location_entity.getSize().y / 2 });
	location_entity.setPosition(position);
	location_entity.setFillColor(sf::Color::Cyan);
	speed_limit = 0;
}

Destination::~Destination()
{
}


// calculates distance from another instance of destination
double Destination::distance_from(Destination d2)
{
	double distance;
	distance = sqrt(abs(d2.location_entity.getPosition().x - this->location_entity.getPosition().x) + abs(d2.location_entity.getPosition().y - this->location_entity.getPosition().y));
	return distance;
}

//Returns type Rectangleshape for window to draw the Destination (Can return texture types too if set correctly)
sf::RectangleShape Destination::Draw()
{
	return location_entity;
}
