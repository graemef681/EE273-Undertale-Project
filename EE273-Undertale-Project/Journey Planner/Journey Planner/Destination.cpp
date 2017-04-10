#include "Destination.hpp"
#include <string>
#include <iostream>
#include <list>

Destination::Destination()
{
	this->setSize({ 25,25 });
	this->setOrigin({ this->getSize().x / 2, this->getSize().y / 2 });
	this->setPosition({ 50,50 });
	this->setFillColor(sf::Color::Green);
	this->setDistance(100000000000);
	speed_limit = 0;
}


Destination::Destination(sf::Vector2f size, sf::Vector2f position, std::string name, float speed_avg, int no_Neighbours)
{
	this->name = name;
	this->setSize(size);
	this->setOrigin({ this->getSize().x / 2, this->getSize().y / 2 });
	this->setPosition(position);
	speed_limit = speed_avg;
	noNeighbours = no_Neighbours;
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

int Destination::getNoNeighbours()
{
	return noNeighbours;
}

void Destination::setNoNeighbours(int n)
{
	noNeighbours = n;
}

std::list<Destination>* Destination::getNeighbourList()
{
	return &neighbourList;
}

void Destination:: setNeighbourList(std::list<Destination>* top, std::string* neighbours)
{
	//clear list first
	neighbourList.clear();
	for (int i = 0; i < noNeighbours; i++)
	{
		std::list<Destination>::iterator begin = (*top).begin(), end = (*top).end(), It;
		It = begin;
		while (It != end)
		{
			if ((neighbours[i]) == It->getName())
			{
				neighbourList.push_back(*It);
			}
			It++;
		}
	}
}

