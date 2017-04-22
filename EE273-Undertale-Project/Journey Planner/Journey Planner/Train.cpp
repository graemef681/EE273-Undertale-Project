#include "Train.hpp"

Train::Train()
{
	std::string type = "Train";
	float mean_speed = 50; //Metres per second
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

void Train::setConstants(float speed, std::string mode)
{
	mean_speed = speed;
	type = mode;
}



void Train::leaveAfter(float journeyTime)
{
	float hour, min;
	double departTimes[18] = { 6.15, 7.15, 8.15, 9.15, 10.15, 11.15, 12.15, 13.15, 14.15, 15.15, 16.15, 17.15, 18.15, 19.15, 20.15, 21.15, 22.15, 23.15 };
	//get the time the user wants to leave after
	std::cout << "Please give the hour you want to leave after:" << std::endl;
	std::cin >> hour;
	std::cout << "Please give the minutes you want to leave after:" << std::endl;
	std::cin >> min;
	float leaveTime = hour + (min / 100);


	//get current time
	SYSTEMTIME time;
	GetLocalTime(&time);
	float curHour, curMin;
	curHour = time.wHour;
	curMin = time.wMinute;
	float curTime = curHour + (curMin / 100);
	std::cout.precision(2);
	std::cout.setf(std::ios::fixed);
	std::cout << "The current time is " << curHour << ":" << curMin << std::endl;
	// compare the hours
	if (hour < curHour)
	{//if the leave after time is before the current time
		std::cout << "Invalid time : cannot choose time in the past." << std::endl;
	}
	else if (hour == curHour)
	{//if the leave after time is within the same hour, check the minutes
		if (min < curMin)
		{//if the minutes is before the current time
			std::cout << "Invalid time: cannot choose time in the past." << std::endl;
		}
		else if (min >= curMin)
		{// if the minutes is in the future, choose the next avaiable time
			std::cout << "The leave time is this hour" << std::endl;
			for (int i = 0; i < 20; i++)
			{
				std::cout.precision(2);
				std::cout.setf(std::ios::fixed);
				std::cout << "The leave time is " << leaveTime;
				std::cout << " -- The depart time is " << departTimes[i] << std::endl;
				if (departTimes[i] > leaveTime)
				{//if the departTime is in the future 
				 //set it as next available journey
					float totalTime = journeyTime + (departTimes[i] - leaveTime);
					float totMin, totHour;
					totMin = modf(totalTime, &totHour);
					if (totMin > 60)
					{
						totMin = totMin - 60;
						totHour = totHour + 1;
					}
					totalTime = totHour + totMin;
					std::cout << "The next available train leaves at " << departTimes[i] << std::endl;
					std::cout << "Your journey time is " << journeyTime << ". Including the wait for the train, the total journey time is " << totalTime << std::endl;
					break;
				}
			}
		}
	}
	else if (hour > curHour)
	{//if the leave after time is in a future hour
	 //the next available time is the first one that hour
		std::cout << "The leave time is a future hour" << std::endl;

		for (int i = 0; i < 20; i++)
		{
			std::cout.precision(2);
			std::cout.setf(std::ios::fixed);
			std::cout << "The leave time is " << leaveTime;
			std::cout << " -- The depart time is " << departTimes[i] << std::endl;
			if (departTimes[i] > leaveTime)
			{//if the departTime is in the future 
			 // if the time until then + journey time is < the time it arrives - current time
			 //set it as next available journey
				float totalTime = journeyTime + (departTimes[i] - leaveTime);
				float totMin, totHour;
				totMin = modf(totalTime, &totHour);
				if (totMin > 60)
				{
					totMin = totMin - 60;
					totHour = totHour + 1;
				}
				totalTime = totHour + totMin;
				std::cout << "The next available train leaves at " << departTimes[i] << std::endl;
				std::cout << "Your journey time is " << journeyTime << ". Including the wait for the train, the total journey time is " << totalTime << std::endl;
				break;
			}
		}
	}
}


void Train::leaveNow(float journeyTime)
{
	double departTimes[18] = { 6.15, 7.15, 8.15, 9.15, 10.15, 11.15, 12.15, 13.15, 14.15, 15.15, 16.15, 17.15, 18.15, 19.15, 20.15, 21.15, 22.15, 23.15 };
	//get current time
	SYSTEMTIME time;
	GetLocalTime(&time);
	float curHour, curMin;
	curHour = time.wHour;
	curMin = time.wMinute;
	float curTime = curHour + (curMin / 100);
	std::cout.precision(2);
	std::cout.setf(std::ios::fixed);
	std::cout << "The current time is " << curHour << ":" << curMin << std::endl;

	float hour, min;
	//get the current time + 10 minutes
	min = curMin + 10;
	hour = curHour;
	if (min > 60)
	{
		min = min - 60;
		hour = hour + 1;
	}
	float leaveTime = hour + (min / 100);

	// compare the hours
	if (hour < curHour)
	{//if the leave after time is before the current time
		std::cout << "Invalid time : cannot choose time in the past." << std::endl;
	}
	else if (hour == curHour)
	{//if the leave after time is within the same hour, check the minutes
		if (min < curMin)
		{//if the minutes is before the current time
			std::cout << "Invalid time: cannot choose time in the past." << std::endl;
		}
		else if (min >= curMin)
		{// if the minutes is in the future, choose the next avaiable time
			std::cout << "The leave time is this hour" << std::endl;
			for (int i = 0; i < 20; i++)
			{
				std::cout.precision(2);
				std::cout.setf(std::ios::fixed);
				std::cout << "The leave time is " << leaveTime;
				std::cout << " -- The depart time is " << departTimes[i] << std::endl;
				if (departTimes[i] > leaveTime)
				{//if the departTime is in the future 
				 //set it as next available journey
					float totalTime = journeyTime + (departTimes[i] - leaveTime);
					float totMin, totHour;
					totMin = modf(totalTime, &totHour);
					if (totMin > 60)
					{
						totMin = totMin - 60;
						totHour = totHour + 1;
					}
					totalTime = totHour + totMin;
					std::cout << "The next available " << type << " leaves at " << departTimes[i] << std::endl;
					std::cout << "Your journey time is " << journeyTime << ". Including the wait for the train, the total journey time is " << totalTime << std::endl;
					break;
				}
			}
		}
	}
	else if (hour > curHour)
	{//if the leave after time is in a future hour
	 //the next available time is the first one that hour
		std::cout << "The leave time is a future hour" << std::endl;

		for (int i = 0; i < 20; i++)
		{
			std::cout.precision(2);
			std::cout.setf(std::ios::fixed);
			std::cout << "The leave time is " << leaveTime;
			std::cout << " -- The depart time is " << departTimes[i] << std::endl;
			if (departTimes[i] > leaveTime)
			{//if the departTime is in the future 
			 // if the time until then + journey time is < the time it arrives - current time
			 //set it as next available journey
				float totalTime = journeyTime + (departTimes[i] - leaveTime);
				float totMin, totHour;
				totMin = modf(totalTime, &totHour);
				if (totMin > 60)
				{
					totMin = totMin - 60;
					totHour = totHour + 1;
				}
				totalTime = totHour + totMin;
				std::cout << "The next available " << type << " leaves at " << departTimes[i] << std::endl;
				std::cout << "Your journey time is " << journeyTime << ". Including the wait for the train, the total journey time is " << totalTime << std::endl;
				break;
			}
		}
	}
}

void Train::arriveBefore(float journeyTime)
{
	float hour, min;
	double departTimes[18] = { 6.15, 7.15, 8.15, 9.15, 10.15, 11.15, 12.15, 13.15, 14.15, 15.15, 16.15, 17.15, 18.15, 19.15, 20.15, 21.15, 22.15, 23.15 };
	//get the time the user wants to arrive before
	std::cout << "Please give the hour you want to arrive before:" << std::endl;
	std::cin >> hour;
	std::cout << "Please give the minutes you want to arrive before:" << std::endl;
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
	std::cout << "The current time is " << curTime << std::endl;
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
			std::cout << "The arrive before time is this hour" << std::endl;

			for (int i = 0; i < 20; i++)
			{
				std::cout.precision(2);
				std::cout.setf(std::ios::fixed);
				std::cout << "The arrive before time is " << beforeTime;
				std::cout << " -- The current time is " << curTime;
				std::cout << " -- The depart time is " << departTimes[i] << std::endl;
				if (departTimes[i] < beforeTime && departTimes[i]>curTime)
				{//if the departTime is in the future 
				 // if the time until then + journey time is < the time it arrives - current time
					if ((beforeTime - journeyTime) < curTime)
					{
						//this journey is ok
						float totalTime = journeyTime + (departTimes[i] - curTime);
						float totMin, totHour;
						totMin = modf(totalTime, &totHour);
						if (totMin > 60)
						{
							totMin = totMin - 60;
							totHour = totHour + 1;
						}
						totalTime = totHour + totMin;
						std::cout << "The next available " << type << " leaves at " << departTimes[i] << std::endl;
						std::cout << "Your journey time is " << journeyTime << ". Including the wait for the train, the total journey time is " << totalTime << std::endl;
						break;
					}
					else
					{
						std::cout << "There are no transports leaving before your desired times." << std::endl;
					}
				}
			}

		}
		else if (hour > curHour)
		{//if the arrive before time is in a future hour
		 //the next available time is the first one that hour
			std::cout << "The arrive before time is a future hour" << std::endl;

			for (int i = 0; i < 20; i++)
			{
				std::cout.precision(2);
				std::cout.setf(std::ios::fixed);
				std::cout << "The arrive before time is " << beforeTime;
				std::cout << " -- The current time is " << curTime;
				std::cout << " -- The depart time is " << departTimes[i] << std::endl;
				if (departTimes[i] < beforeTime && departTimes[i]>curTime)
				{//if the departTime is in the future 
				 // if the time until then + journey time is < the time it arrives - current time
					if ((beforeTime - journeyTime) < curTime)
					{
						//this journey is ok
						float totalTime = journeyTime + (departTimes[i] - curTime);
						float totMin, totHour;
						totMin = modf(totalTime, &totHour);
						if (totMin > 60)
						{
							totMin = totMin - 60;
							totHour = totHour + 1;
						}
						totalTime = totHour + totMin;
						std::cout << "The next available " << type << " leaves at " << departTimes[i] << std::endl;
						std::cout << "Your journey time is " << journeyTime << ". Including the wait for the train, the total journey time is " << totalTime << std::endl;
						break;
					}
					else
					{
						std::cout << "There are no transports leaving before your desired times." << std::endl;
					}
				}
			}
		}
	}
}