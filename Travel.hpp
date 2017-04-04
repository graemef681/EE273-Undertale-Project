#pragma once
#include "Destination.hpp"
#include<iostream>
#include<windows.h>


class Travel
{
public:
	Travel();
	~Travel();
	virtual float pathfinding_algorithm(Destination start_dest, Destination end_dest, std::list<Destination>*);
	void leaveAfter(float);
	void arriveBefore(float);
	float calcJourneyTime(float);


protected:
	double total_route_time;
	//double mean_speed=0;
	int no_stops;
	//float departTimes[1];
	//std::string type = "NULL";
	Destination* array_of_avoids;
	std::string type = "Bus";
	float mean_speed = 20;
	double departTimes[20] = { 8.05, 9.12, 10.15, 10.40, 11.15, 12.01, 12.21, 12.41, 13.01, 13.19, 13.56, 14.14, 15.08, 15.47, 16.00, 16.17, 16.38, 17.00, 17.05, 18.30 };
};

