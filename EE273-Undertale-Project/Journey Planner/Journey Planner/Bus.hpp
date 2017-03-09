#pragma once
#include "Travel.hpp"
class Bus :
	public Travel
{
public:
	Bus();
	~Bus();
	void pathfinding_algorithm(Destination* start_dest, Destination* end_dest);
};

