#pragma once
#include "Travel.hpp"
class Train :
	public Travel
{
public:
	Train();
	~Train();
	float calcJourneyTime(float);
	//void pathfinding_algorithm();
	void setConstants(float, std::string);
	void leaveAfter(float);
	void arriveBefore(float);
	void leaveNow(float);
};


