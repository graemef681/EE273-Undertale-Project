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
	Destination(sf::Vector2f size, sf::Vector2f position, std::string name, float speed_avg, int noNeighbours);
	~Destination();
protected:
	std::string name;
	float speed_limit;
	std::list<Destination> neighbourList;
	int noNeighbours;
	double distance;
public:
	// calculates distance from another instance of destination
	double distance_from(Destination);
	float getSpeed();
	std::string getName();
	int getNoNeighbours();
	void setNoNeighbours(int);
	std::list<Destination>* getNeighbourList();
	void setNeighbourList( std::list<Destination>*,std::string*);
	double getDistance() { return distance; };
	void setDistance(double d) {	distance = d;	};
};