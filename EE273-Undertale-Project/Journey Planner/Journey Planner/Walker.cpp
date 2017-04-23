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
	float time, hour = 0, min = 0, journeyTime;
	time = distance / mean_speed;

	if (time > 1)
	{//if time greater than 1 hour
		hour = int(time);
		min = (time - hour) * 60;
	}
	if (min > 60)
	{
		min = min - 60;
		hour = hour + 1;
	}
	journeyTime = hour + (min / 100);
	return journeyTime;
}

void Walker::setConstants(float speed, std::string mode)
{
	mean_speed = speed;
	type = mode;
}

void Walker::arriveBefore(float journeyTime)
{
	float hour, min;
	//get the time the user wants to arrive before
	std::cout << "Please give the hour you want to arrive before: ";
	std::cin >> hour;
	std::cout << "Please give the minutes you want to arrive before: ";
	std::cin >> min;
	float beforeTime = hour + (min / 100);

	//get current time
	SYSTEMTIME time;
	GetLocalTime(&time);
	float curHour, curMin;
	curHour = time.wHour;
	curMin = time.wMinute;
	float curTime = curHour + (curMin / 100);
	std::cout.precision(2);
	std::cout.setf(std::ios::fixed);
	// compare the hours
	if (hour < curHour)
	{//if the arrive before time is before the current time
		std::cout << "Invalid time : cannot choose time in the past (hours)." << std::endl;
	}
	else if (hour == curHour)
	{//if the arrive before time is within the same hour, check the minutes
		if (min < curMin)
		{//if the minutes is before the current time
			std::cout << "Invalid time: cannot choose time in the past (mins)." << std::endl;
		}
		else if (min > curMin)
		{// if the minutes is in the future, choose the next avaiable time
		 //greater than the current time

			for (int i = 0; i < 20; i++)
			{
				std::cout.precision(2);
				std::cout.setf(std::ios::fixed);
				if ((beforeTime - journeyTime) < curTime)
				{
					std::cout << "It is possible to walk to your destination before the desired time. The journey will take you " << journeyTime << std::endl;
				}
				else
				{
					std::cout << "You cannot walk to your destination before your desired time." << std::endl;
				}
			}

		}
	}
	else if (hour > curHour)
	{//if the arrive before time is in a future hour
		 //the next available time is the first one that hour
			for (int i = 0; i < 20; i++)
			{
				std::cout.precision(2);
				std::cout.setf(std::ios::fixed);
				if ((beforeTime - journeyTime) < curTime)
				{
					std::cout << "It is possible to walk to your destination before the desired time. The journey will take you " << journeyTime << std::endl;
					break;
				}
				else
				{
					std::cout << "You cannot walk to your destination before your desired time." << std::endl;
				}
			}
		
	}
}