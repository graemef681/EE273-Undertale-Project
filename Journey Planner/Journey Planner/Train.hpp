#pragma once
#include "Travel.hpp"
class Train :
	public Travel
{
public:
	Train();
	~Train();
	void pathfinding_algorithm();
};

