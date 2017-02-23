#pragma once
class Destination
{
public:
	Destination();
	~Destination();
protected:
	string name;
	vector location_vector;
	int speed_limit;
public:
	// calculates distance from another instance of destination
	double distance_from(Destination d2);
};

