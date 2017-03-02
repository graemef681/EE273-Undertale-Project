#pragma once
#include "Travel.hpp"
class Walker :
	public Travel
{
public:
	Walker();
	~Walker();
	void pathfinding_algorithm(Destination* start_dest, Destination* end_dest);
};

