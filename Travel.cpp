#include "Travel.hpp"


Travel::Travel()
{
	total_route_time = 0.0;
	mean_speed= 0.0;
	no_stops = 0;
}


Travel::~Travel()
{
}


float Travel::pathfinding_algorithm(Destination start_dest, Destination end_dest, std::list<Destination>* Top)
{
		using namespace std;
		//create required sets
		list<Destination> journey, *neighbours=NULL;
		list<float> distance;
		//empty list before use
		journey.clear();
		//set start destination to be the first in the journey list
		journey.push_back(start_dest);
		double prevDistance = 10000000000000, curDistance, shortestDistance = 10000000000000, total = 0;
		Destination shortest, temp;
		shortest.setName("Temp Shortest");
		Destination curNode;
		curNode = start_dest;
		std::cout << "Start dest is:" << start_dest.getName() << endl;
		std::cout << "End dest is:" << end_dest.getName() << endl;
		int count = 1;
		while (shortest.getName() != end_dest.getName())
		{
			prevDistance = 10000000000000;
			shortestDistance = 10000000000000;
			bool visitedBefore = false;
			std::cout << "START OF WHILE" << endl;
			std::cout << "Current node is: " << curNode.getName();
			list<Destination>::iterator DestBegin = Top->begin(), DestEnd = Top->end(), DestIt;
			DestIt = DestBegin;
			while (DestIt != DestEnd)
			{
				if (DestIt->getName() == curNode.getName())
				{
					neighbours = DestIt->getNeighbourList();
					std::cout << neighbours->size() << endl;
				}
				DestIt++;
			}
			list<Destination>::iterator begin = neighbours->begin(), end = neighbours->end(), NIt;
			NIt = begin;
			while (NIt != end)
			{
					//If not visited before then check distance from. 
					curDistance = curNode.distance_from(*NIt);
					
					//**************************************************
					//Check if the current node has been visited before
					//If it has, then add a big number to its distance so it isn't picked

					/*list<Destination>::iterator Jbegin = journey.begin(), Jend = journey.end(), Jit;
					Jit = Jbegin;
					while (Jit != Jend)
					{
						if ((*Jit).getName() == curNode.getName() && (*Jit).getName() != start_dest.getName())
						{
							curDistance = curDistance + 1000000;
						}
						temp = *Jit;
						Jit++;
					}*/
					//**********************************************

					std::cout << "Distance from " << curNode.getName() << " to " << NIt->getName() << ":" << curDistance << endl;
					if (curDistance < prevDistance)
					{ //if the currentDistance is shorter than the previous
						

								shortest = *NIt;
								std::cout << "Number of neighbours for shortest is: " << shortest.getNoNeighbours();
								shortestDistance = curDistance;
					
					}
				prevDistance = curDistance;
				NIt++;
				
			}
			list<Destination>::iterator Jbegin = journey.begin(), Jend = journey.end(), Jit;
			Jit = Jbegin;
			while (Jit != Jend)
			{
				if ((*Jit).getName() == shortest.getName())
				{
					visitedBefore = true;
				}
				temp = *Jit;
				Jit++;
			}
			if (!visitedBefore)
			{
				journey.push_back(shortest);
				distance.push_back(shortestDistance);
				curNode = shortest;
				std::cout << "The current node is now:" << shortest.getName() << endl;
				//visitedBefore = false;
			}
		}
		journey.push_back(end_dest);
		distance.push_back((end_dest).distance_from(temp));
		list<Destination>::iterator jBegin = journey.begin(), jEnd = journey.end(), jIt;
		jIt = jBegin;
		std::cout << "THE SHORTEST JOURNEY IS" << endl;
		while (jIt != jEnd)
		{
			std::cout << jIt->getName() << endl;
			jIt++;
		}

		list<float>::iterator DBegin = distance.begin(), DEnd = distance.end(), DIt;
		DIt = DBegin;
		while (DIt != DEnd)
		{
			total = total + *DIt;
			DIt++;
		}
		std::cout << "THE DISTANCE IS :" << total << endl;

		calcJourneyTime(total);
		return total;
}

void Travel::leaveAfter(float journeyTime)
{
	float hour, min;
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
						std::cout << "The next available " << type << " leaves at " << departTimes[i] << std::endl;
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
						std::cout << "The next available " << type << " leaves at " << departTimes[i] << std::endl;
						break;
					}
				}
			}
	}

void Travel::arriveBefore(float journeyTime)
{
	float hour, min;
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
						std::cout << "The next available " << type << " getting to your destination is " << departTimes[i] << std::endl;
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
						std::cout << "The next available " << type << " getting to your destination is " << departTimes[i] << std::endl;
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


float Travel::calcJourneyTime(float distance)
{
	float time, hour=0, min=0, journeyTime;
	time = distance / mean_speed;

	if (time > 1)
	{//if time greater than 1 hour
		hour = int(time);
		min = time - 1 * 60;
	}
	journeyTime = hour + (min / 100);
	return journeyTime;
}