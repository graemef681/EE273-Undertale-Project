#pragma once
#include "Destination.hpp"
class Travel
{
public:
	Travel();
	~Travel();
	virtual void pathfinding_algorithm(Destination* start_dest, Destination* end_dest);
protected:
	double total_route_time;
	double medium_speed;
	int no_stops;
	Destination* array_of_avoids;

};

