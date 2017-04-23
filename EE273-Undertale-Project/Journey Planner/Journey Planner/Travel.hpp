#pragma once
#include "Destination.hpp"
#include<iostream>
#include<windows.h>


class Travel
{
public:
	Travel();
	~Travel();
	double pathfinding_algorithm(Destination* start_dest, Destination* end_dest, std::list<Destination>*);
	double pathfinding_algorithm(Destination* start_dest, Destination* end_dest, std::list<Destination>*, std::string);


protected:
	double total_route_time;
	int no_stops;
	Destination* array_of_avoids;
	std::string type;
	float mean_speed;
	double departTimes[20];
};