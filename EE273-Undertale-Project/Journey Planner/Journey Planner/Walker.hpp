#pragma once
#include "Travel.hpp"
class Walker :
	public Travel
{
public:
	Walker();
	~Walker();
	float calcJourneyTime(float);
	//void pathfinding_algorithm();
	void setConstants(float, std::string);
};

