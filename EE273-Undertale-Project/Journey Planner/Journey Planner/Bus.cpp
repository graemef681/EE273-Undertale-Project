#include "Bus.hpp"



Bus::Bus()
{
	std::string type = "Bus";
	float mean_speed = 20;
	double departTimes[20] = { 8.05, 9.12, 10.15, 10.40, 11.15, 12.01, 12.21, 12.41, 13.01, 13.19, 13.56, 14.14, 15.08, 15.47, 16.00, 16.17, 16.38, 17.00, 17.05, 18.30 };
}


Bus::~Bus()
{
}

float Bus::calcJourneyTime(float distance)
{
	setConstants(20, "Bus");
	std::cout << "CalcJourneyTime called: distance = " << distance << std::endl;
	std::cout << "Type is :" << type << std::endl;
	std::cout << "Mean speed is :" << mean_speed << std::endl;

	float time, hour = 0, min = 0, journeyTime;
	time = distance / mean_speed;

	if (time > 1)
	{//if time greater than 1 hour
		hour = int(time);
		min = time - hour * 60;
	}
	journeyTime = hour + (min / 100);
	return journeyTime;
}

void Bus::setConstants(float speed, std::string mode)
{
	mean_speed = speed;
	type = mode;
}

