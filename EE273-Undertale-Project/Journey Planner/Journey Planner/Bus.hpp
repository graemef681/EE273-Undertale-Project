#pragma once
#include "Travel.hpp"
class Bus :
	public Travel
{
public:
	Bus();
	~Bus();
	float calcJourneyTime(float);
	void setConstants(float, std::string);
	void leaveAfter(float);
	void arriveBefore(float);
	void leaveNow(float);
};

