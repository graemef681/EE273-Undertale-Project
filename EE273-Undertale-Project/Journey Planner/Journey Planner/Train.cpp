#include "Train.hpp"

Train::Train()
{
	std::string type = "Train";
	float mean_speed = 50;
	double departTimes[18] = { 6.15, 7.15, 8.15, 9.15, 10.15, 11.15, 12.15, 13.15, 14.15, 15.15, 16.15, 17.15, 18.15, 19.15, 20.15, 21.15, 22.15, 23.15 };
}


Train::~Train()
{
}

float Train::calcJourneyTime(float distance)
{
	setConstants(50, "Train");
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

void Train::setConstants(float speed, std::string mode)
{
	mean_speed = speed;
	type = mode;
}


