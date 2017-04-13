#include "Walker.hpp"



Walker::Walker()
{
	std::string type = "Walking";
	float mean_speed = 3.1;
	SYSTEMTIME time;
	GetLocalTime(&time);
	float curHour, curMin;
	curHour = time.wHour;
	curMin = time.wMinute;
	double departTimes = curHour + (curMin / 100);
}


Walker::~Walker()
{
}


float Walker::calcJourneyTime(float distance)
{
	setConstants(3.1, "Walk");
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

void Walker::setConstants(float speed, std::string mode)
{
	mean_speed = speed;
	type = mode;
}
