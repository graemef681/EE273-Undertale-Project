#include "Travel.hpp"
#include "Bus.hpp"
#include "Train.hpp"
#include "Walker.hpp"


Travel::Travel()
{
	total_route_time = 0.0;
	no_stops = 0;
	//std::string type = "Travel Class";
	//float mean_speed = 20;
	//double departTimes[20] = { 8.05, 9.12, 10.15, 10.40, 11.15, 12.01, 12.21, 12.41, 13.01, 13.19, 13.56, 14.14, 15.08, 15.47, 16.00, 16.17, 16.38, 17.00, 17.05, 18.30 };
}


Travel::~Travel()
{
}


double Travel::pathfinding_algorithm(Destination* start_dest, Destination* end_dest, std::list<Destination>* Topology)
{
	using namespace std;
	list<Destination>* top = Topology; //Topology for unvisited set
	list<Destination> visited;
	list<double> distances{0};
	list<Destination>::iterator DestBegin = top->begin(), DestEnd = top->end(), DestIt;
	double curDistance, shortestDistance = 0, prevDistance = 1000000000000000, total = 0;
	string shortestNodeName;
	bool DestVisited = false;
	DestIt = DestBegin;
	while (DestIt != DestEnd)
	{ //Set all nodes distance to effective infinite
		DestIt->setDistance(1000000000000);
		DestIt++;
	}
	start_dest->setDistance(0); //Current source node distance to 0
	Destination curNode;
	curNode = *start_dest; //Initial current node to source node.

	while (curNode.getName() != end_dest->getName())
	{
		prevDistance = 1000000000000000;
		list<Destination>* neighbours = curNode.getNeighbourList(); //Consider all unvisited neighbours and calculate their tentative distances
		list<Destination>::iterator Nbegin = neighbours->begin(), Nend = neighbours->end(), Nit;
		Nit = Nbegin;
		while (Nit != Nend)
		{
			if (visited.empty())
			{
				curDistance = curNode.distance_from(*Nit);
				cout << "Distance from " << curNode.getName() << " to " << Nit->getName() << ":" << curDistance << endl; //Calculate distance from cur to Neighbour
				//If calculated neighbour distance through current node is smaller than currently assigned neighbour distance
				if ((curNode.getDistance() + curDistance) < Nit->getDistance())
					Nit->setDistance(curDistance); //Then set calculated distance as neighbour distance
				//Otherwise keep neighbour assigned distance value
				//Find neighbour with shortest curdistance
				if (Nit->getName() == end_dest->getName())
				{//if one of the neighbours is the end destination, go there, regardless of distance
					shortestNodeName = Nit->getName();
					shortestDistance = curDistance;
					break;
				}
				else if (curDistance < prevDistance)
				{
					prevDistance = curDistance;
					shortestNodeName = Nit->getName(); //After all neighbours curDistances have been checked, this will have the name of the shortest
					shortestDistance = curDistance;
				}
			}
			else
			{
				list<Destination>::iterator Vbegin = visited.begin(), Vend = visited.end(), Vit;
				Vit = Vbegin;
				while (Vit != Vend)
				{
					if (Vit->getName() == Nit->getName())
					{
						DestVisited = true;
					}
					else
					{
						DestVisited = false;
					}
					Vit++;
				}
				if (DestVisited==false)
				{
					curDistance = curNode.distance_from(*Nit);
					cout << "Distance from " << curNode.getName() << " to " << Nit->getName() << ":" << curDistance << endl; //Calculate distance from cur to Neighbour
					//If calculated neighbour distance through current node is smaller than currently assigned neighbour distance
					if ((curNode.getDistance() + curDistance) < Nit->getDistance())
					{
						Nit->setDistance(curDistance); //Then set calculated distance as neighbour distance
													   //Otherwise keep neighbour assigned distance value
					}
						
					//Find neighbour with shortest curdistance
					if (Nit->getName() == end_dest->getName())
					{//if one of the neighbours is the end destination, go there, regardless of distance
						shortestNodeName = Nit->getName();
						shortestDistance = curDistance;
						break;
					}
					else if (curDistance < prevDistance)
					{
						prevDistance = curDistance;
						shortestNodeName = Nit->getName(); //After all neighbours curDistances have been checked, this will have the name of the shortest
						shortestDistance = curDistance;
					}
				}
			}
			Nit++;
		}
		//After checking all neighbours
		visited.push_back(curNode);//Mark curNode as visited
		distances.push_back(shortestDistance); //Add shortest Distance
		cout << "Shortest Distance: " << shortestDistance << endl;
		cout << "Shortest Node Name: " << shortestNodeName << endl;
		//Use ShortestNodeName to select next current node
		DestIt = DestBegin;
		while (DestIt != DestEnd) //Use topology pointer to set current node.
		{
			if (shortestNodeName == DestIt->getName())
			{
				curNode = *DestIt;
			}
			DestIt++;
		}
	}
	visited.push_back(curNode); //Put end destination into visited list
	//Now find the journey path by visited list
	list<Destination>::iterator Vbegin = visited.begin(), Vend = visited.end(), Vit;
	list<double>::iterator Dbegin = distances.begin(), Dend = distances.end(), Dit;
	Vit = Vbegin;
	Dit = Dbegin;
	while (Vit != Vend)
	{
		cout << "Visited: " << Vit->getName() << endl;
		//Get distance for each visited node from topology
		Vit->setDistance(*Dit); //Also set distance for each journey node
		total = total + *Dit;
		cout << "Total Distance: " << total << endl;
		Vit++;
		Dit++;
	}
	return total;
}

//PATHFINDING OVERLOAD FOR AVOIDING DESTINATION
double Travel::pathfinding_algorithm(Destination* start_dest, Destination* end_dest, std::list<Destination>* Topology, std::string avoidName)
{
	using namespace std;
	list<Destination>* top = Topology; //Topology for unvisited set
	list<Destination> visited;
	list<double> distances{ 0 };
	list<Destination>::iterator DestBegin = top->begin(), DestEnd = top->end(), DestIt;
	double curDistance, shortestDistance = 0, prevDistance = 1000000000000000, total = 0;
	string shortestNodeName;
	bool DestVisited = false;
	DestIt = DestBegin;
	while (DestIt != DestEnd)
	{ //Set all nodes distance to effective infinite
		DestIt->setDistance(1000000000000);
		DestIt++;
	}
	start_dest->setDistance(0); //Current source node distance to 0
	Destination curNode;
	curNode = *start_dest; //Initial current node to source node.

	while (curNode.getName() != end_dest->getName())
	{
		list<Destination>* neighbours = curNode.getNeighbourList(); //Consider all unvisited neighbours and calculate their tentative distances
		list<Destination>::iterator Nbegin = neighbours->begin(), Nend = neighbours->end(), Nit;
		Nit = Nbegin;
		while (Nit != Nend)
		{
			if (visited.empty())
			{
				if (Nit->getName() != avoidName)
				{
					curDistance = curNode.distance_from(*Nit);
					cout << "Distance from " << curNode.getName() << " to " << Nit->getName() << ":" << curDistance << endl; //Calculate distance from cur to Neighbour
																															 //If calculated neighbour distance through current node is smaller than currently assigned neighbour distance
					if ((curNode.getDistance() + curDistance) < Nit->getDistance())
						Nit->setDistance(curDistance); //Then set calculated distance as neighbour distance
													   //Otherwise keep neighbour assigned distance value
													   //Find neighbour with shortest curdistance
					if (Nit->getName() == end_dest->getName())
					{//if one of the neighbours is the end destination, go there, regardless of distance
						shortestNodeName = Nit->getName();
						shortestDistance = curDistance;
						break;
					}
					else if (curDistance < prevDistance)
					{
						prevDistance = curDistance;
						shortestNodeName = Nit->getName(); //After all neighbours curDistances have been checked, this will have the name of the shortest
						shortestDistance = curDistance;
					}
				}
			}
			else
			{
				list<Destination>::iterator Vbegin = visited.begin(), Vend = visited.end(), Vit;
				Vit = Vbegin;
				while (Vit != Vend)
				{
					if (Vit->getName() == Nit->getName())
					{
						DestVisited = true;
					}
					else
					{
						DestVisited = false;
					}
					Vit++;
				}
				if (!DestVisited&& Nit->getName() != avoidName)
				{
					curDistance = curNode.distance_from(*Nit);
					cout << "Distance from " << curNode.getName() << " to " << Nit->getName() << ":" << curDistance << endl; //Calculate distance from cur to Neighbour
																															 //If calculated neighbour distance through current node is smaller than currently assigned neighbour distance
					if ((curNode.getDistance() + curDistance) < Nit->getDistance())
					{
						Nit->setDistance(curDistance); //Then set calculated distance as neighbour distance
													   //Otherwise keep neighbour assigned distance value
					}

					//Find neighbour with shortest curdistance
					if (Nit->getName() == end_dest->getName())
					{//if one of the neighbours is the end destination, go there, regardless of distance
						shortestNodeName = Nit->getName();
						shortestDistance = curDistance;
						break;
					}
					else if (curDistance < prevDistance)
					{
						prevDistance = curDistance;
						shortestNodeName = Nit->getName(); //After all neighbours curDistances have been checked, this will have the name of the shortest
						shortestDistance = curDistance;
					}
				}
			}
			Nit++;
		}
		//After checking all neighbours
		visited.push_back(curNode);//Mark curNode as visited
		distances.push_back(shortestDistance); //Add shortest Distance
		cout << "Shortest Distance: " << shortestDistance << endl;
		cout << "Shortest Node Name: " << shortestNodeName << endl;
		//Use ShortestNodeName to select next current node
		DestIt = DestBegin;
		while (DestIt != DestEnd) //Use topology pointer to set current node.
		{
			if (shortestNodeName == DestIt->getName())
			{
				curNode = *DestIt;
			}
			DestIt++;
		}
	}
	visited.push_back(curNode); //Put end destination into visited list
								//Now find the journey path by visited list
	list<Destination>::iterator Vbegin = visited.begin(), Vend = visited.end(), Vit;
	list<double>::iterator Dbegin = distances.begin(), Dend = distances.end(), Dit;
	Vit = Vbegin;
	Dit = Dbegin;
	while (Vit != Vend)
	{
		cout << "Visited: " << Vit->getName() << endl;
		//Get distance for each visited node from topology
		Vit->setDistance(*Dit); //Also set distance for each journey node
		total = total + *Dit;
		cout << "Total Distance: " << total << endl;
		Vit++;
		Dit++;
	}
	return total;
}

/*
double Travel::pathfinding_algorithm(Destination* start_dest, Destination* end_dest, std::list<Destination>*Topology, char stops)
{
	using namespace std;
	list<Destination>* top = Topology; //Topology for unvisited set
	list<Destination> visited;
	list<double> distances{ 0 };
	list<Destination>::iterator DestBegin = top->begin(), DestEnd = top->end(), DestIt;
	double curDistance, shortestDistance = 0, prevDistance = 1000000000000000, total = 0;
	string shortestNodeName;
	bool DestVisited = false;
	DestIt = DestBegin;
	while (DestIt != DestEnd)
	{ //Set all nodes distance to effective infinite
		DestIt->setDistance(1000000000000);
		DestIt++;
	}
	start_dest->setDistance(0); //Current source node distance to 0
	Destination curNode;
	curNode = *start_dest; //Initial current node to source node.

	while (curNode.getName() != end_dest->getName())
	{
		list<Destination>* neighbours = curNode.getNeighbourList(); //Consider all unvisited neighbours and calculate their tentative distances
		list<Destination>::iterator Nbegin = neighbours->begin(), Nend = neighbours->end(), Nit;
		Nit = Nbegin;
		while (Nit != Nend)
		{
			if (visited.empty())
			{
				curDistance = curNode.distance_from(*Nit);
				cout << "Distance from " << curNode.getName() << " to " << Nit->getName() << ":" << curDistance << endl; //Calculate distance from cur to Neighbour
																														 //If calculated neighbour distance through current node is smaller than currently assigned neighbour distance
				if ((curNode.getDistance() + curDistance) < Nit->getDistance())
					Nit->setDistance(curDistance); //Then set calculated distance as neighbour distance
												   //Otherwise keep neighbour assigned distance value
												   //Find neighbour with shortest curdistance
				if (curDistance < prevDistance)
				{
					prevDistance = curDistance;
					shortestNodeName = Nit->getName(); //After all neighbours curDistances have been checked, this will have the name of the shortest
					shortestDistance = curDistance;
				}
			}
			else
			{
				list<Destination>::iterator Vbegin = visited.begin(), Vend = visited.end(), Vit;
				Vit = Vbegin;
				while (Vit != Vend)
				{
					if (Vit->getName() == Nit->getName())
					{
						DestVisited = true;
					}
					else
					{
						DestVisited = false;
					}
					Vit++;
				}
				if (!DestVisited)
				{
					curDistance = curNode.distance_from(*Nit);
					cout << "Distance from " << curNode.getName() << " to " << Nit->getName() << ":" << curDistance << endl; //Calculate distance from cur to Neighbour
																															 //If calculated neighbour distance through current node is smaller than currently assigned neighbour distance
					if ((curNode.getDistance() + curDistance) < Nit->getDistance())
					{
						Nit->setDistance(curDistance); //Then set calculated distance as neighbour distance
													   //Otherwise keep neighbour assigned distance value
					}

					//Find neighbour with shortest curdistance
					if (curDistance < prevDistance)
					{
						prevDistance = curDistance;
						shortestNodeName = Nit->getName(); //After all neighbours curDistances have been checked, this will have the name of the shortest
						shortestDistance = curDistance;
					}
				}
			}
			Nit++;
		}
		//After checking all neighbours
		visited.push_back(curNode);//Mark curNode as visited
		distances.push_back(shortestDistance); //Add shortest Distance
		cout << "Shortest Distance: " << shortestDistance << endl;
		cout << "Shortest Node Name: " << shortestNodeName << endl;
		//Use ShortestNodeName to select next current node
		DestIt = DestBegin;
		while (DestIt != DestEnd) //Use topology pointer to set current node.
		{
			if (shortestNodeName == DestIt->getName())
			{
				curNode = *DestIt;
			}
			DestIt++;
		}
	}
	visited.push_back(curNode); //Put end destination into visited list
								//Now find the journey path by visited list
	list<Destination>::iterator Vbegin = visited.begin(), Vend = visited.end(), Vit;
	list<double>::iterator Dbegin = distances.begin(), Dend = distances.end(), Dit;
	Vit = Vbegin;
	Dit = Dbegin;
	while (Vit != Vend)
	{
		cout << "Visited: " << Vit->getName() << endl;
		//Get distance for each visited node from topology
		Vit->setDistance(*Dit); //Also set distance for each journey node
		total = total + *Dit;
		cout << "Total Distance: " << total << endl;
		Vit++;
		Dit++;
	}
	return total;
}
double Travel::pathfinding_algorithm(Destination* start_dest, Destination* end_dest, std::list<Destination>* Topology, char stops, std::string avoidName)
{
	using namespace std;
	list<Destination>* top = Topology; //Topology for unvisited set
	list<Destination> visited;
	list<double> distances{ 0 };
	list<Destination>::iterator DestBegin = top->begin(), DestEnd = top->end(), DestIt;
	double curDistance, shortestDistance = 0, prevDistance = 1000000000000000, total = 0;
	string shortestNodeName;
	bool DestVisited = false;
	DestIt = DestBegin;
	while (DestIt != DestEnd)
	{ //Set all nodes distance to effective infinite
		DestIt->setDistance(1000000000000);
		DestIt++;
	}
	start_dest->setDistance(0); //Current source node distance to 0
	Destination curNode;
	curNode = *start_dest; //Initial current node to source node.

	while (curNode.getName() != end_dest->getName())
	{
		list<Destination>* neighbours = curNode.getNeighbourList(); //Consider all unvisited neighbours and calculate their tentative distances
		list<Destination>::iterator Nbegin = neighbours->begin(), Nend = neighbours->end(), Nit;
		Nit = Nbegin;
		while (Nit != Nend)
		{
			if (visited.empty())
			{
				curDistance = curNode.distance_from(*Nit);
				cout << "Distance from " << curNode.getName() << " to " << Nit->getName() << ":" << curDistance << endl; //Calculate distance from cur to Neighbour
																														 //If calculated neighbour distance through current node is smaller than currently assigned neighbour distance
				if ((curNode.getDistance() + curDistance) < Nit->getDistance())
					Nit->setDistance(curDistance); //Then set calculated distance as neighbour distance
												   //Otherwise keep neighbour assigned distance value
												   //Find neighbour with shortest curdistance
				if (curDistance < prevDistance)
				{
					prevDistance = curDistance;
					shortestNodeName = Nit->getName(); //After all neighbours curDistances have been checked, this will have the name of the shortest
					shortestDistance = curDistance;
				}
			}
			else
			{
				list<Destination>::iterator Vbegin = visited.begin(), Vend = visited.end(), Vit;
				Vit = Vbegin;
				while (Vit != Vend)
				{
					if (Vit->getName() == Nit->getName())
					{
						DestVisited = true;
					}
					else
					{
						DestVisited = false;
					}
					Vit++;
				}
				if (!DestVisited)
				{
					curDistance = curNode.distance_from(*Nit);
					cout << "Distance from " << curNode.getName() << " to " << Nit->getName() << ":" << curDistance << endl; //Calculate distance from cur to Neighbour
																															 //If calculated neighbour distance through current node is smaller than currently assigned neighbour distance
					if ((curNode.getDistance() + curDistance) < Nit->getDistance())
					{
						Nit->setDistance(curDistance); //Then set calculated distance as neighbour distance
													   //Otherwise keep neighbour assigned distance value
					}

					//Find neighbour with shortest curdistance
					if (curDistance < prevDistance)
					{
						prevDistance = curDistance;
						shortestNodeName = Nit->getName(); //After all neighbours curDistances have been checked, this will have the name of the shortest
						shortestDistance = curDistance;
					}
				}
			}
			Nit++;
		}
		//After checking all neighbours
		visited.push_back(curNode);//Mark curNode as visited
		distances.push_back(shortestDistance); //Add shortest Distance
		cout << "Shortest Distance: " << shortestDistance << endl;
		cout << "Shortest Node Name: " << shortestNodeName << endl;
		//Use ShortestNodeName to select next current node
		DestIt = DestBegin;
		while (DestIt != DestEnd) //Use topology pointer to set current node.
		{
			if (shortestNodeName == DestIt->getName())
			{
				curNode = *DestIt;
			}
			DestIt++;
		}
	}
	visited.push_back(curNode); //Put end destination into visited list
								//Now find the journey path by visited list
	list<Destination>::iterator Vbegin = visited.begin(), Vend = visited.end(), Vit;
	list<double>::iterator Dbegin = distances.begin(), Dend = distances.end(), Dit;
	Vit = Vbegin;
	Dit = Dbegin;
	while (Vit != Vend)
	{
		cout << "Visited: " << Vit->getName() << endl;
		//Get distance for each visited node from topology
		Vit->setDistance(*Dit); //Also set distance for each journey node
		total = total + *Dit;
		cout << "Total Distance: " << total << endl;
		Vit++;
		Dit++;
	}
	return total;
}
*/