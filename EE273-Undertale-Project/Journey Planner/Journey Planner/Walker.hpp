#pragma once
#include "Travel.hpp"
class Walker :
	public Travel
{
public:
	Walker();
	~Walker();
	float calcJourneyTime(float);
	void setConstants(float, std::string);
	void arriveBefore(float);
};

