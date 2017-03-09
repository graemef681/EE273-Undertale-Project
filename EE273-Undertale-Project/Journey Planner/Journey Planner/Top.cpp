#include"Top.hpp"
using namespace std;

list<Destination> ReadFile(string filename)
{
start:
	//check notes on how to resize arrays to make sure this is correct
	string *ptrneighbour = NULL;
	list<Destination> Topology;
	ifstream inFile;
	inFile.open(filename+".txt");
	if (inFile.is_open())
	{
		if (checkNetworkTop(filename))
		{

			while (!inFile.eof())
			{
				string temp;
				string name;
				getline(inFile, name, ';');
				cout << "Name is:" << name << endl;
				float x;
				getline(inFile, temp, ',');
				cout << "X is:" << temp << endl;
				x = stof(temp);
				float y;
				getline(inFile, temp, ';');
				y = stof(temp);
				cout << "Y is:" << temp << endl;
				float speed_avg;
				getline(inFile, temp, ';');
				speed_avg = stof(temp);
				cout << "Speed average is: " << temp << endl;
				int no_neighbours;
				getline(inFile, temp, ';');
				cout << "No neighbours: " << temp << endl;
				no_neighbours = stoi(temp);
				ptrneighbour = new string[no_neighbours];
				for (int i = 0; i < no_neighbours; i++)
				{
					if (i < no_neighbours - 1)
					{
						getline(inFile, temp, ',');
						ptrneighbour[i] = temp;
						cout << "Neighbour " << i + 1 << " is " << temp << endl;
					}
					else if (i==no_neighbours-1)
					{
						cout << "Else called" << endl;
						getline(inFile, temp);
						ptrneighbour[i] = temp;
						cout << "Last Neighbour " << i + 1 << " is " << temp << endl;
					}
					
				}
			


				Destination D({ 25, 25 }, { x, y }, name, speed_avg, no_neighbours);
				Topology.push_back(D);
			}
			inFile.close();
			list<Destination>::iterator begin = Topology.begin(), end = Topology.end(), It;
			It = begin;
			while (It != end)
			{
				//set neighbour list for all destinations
				(*It).setNeighbourList(&Topology,ptrneighbour);
				cout << "Neighbours list set for: " << It->getName() << endl;
				It++;

			}
			return Topology;
		}
	}
	else
	{
		cout << "Failed to read file, please try again" << endl;
		cout << "Enter a new filename: ";
		cin >> filename;
		goto start;
	}
}


void addNewDest(string fileName,list<Destination>* currentTop)
{
	//open the output file in append mode
	ofstream outFile(fileName +".txt", ios::app);

	string newName, curNeighbour;
	float newX, newY;
	float newSpeed;
	string* neighbours;
	int noNeighbours;

	do
	{
		cout << "Please enter the name for the new destination:" << endl;
		cin >> newName;
	} while (newName.empty());

	do
	{
		cout << "Please enter the x position for " << newName << ":" << endl;
		cin >> newX;
	} while (newX > 0);
	
	do
	{
		cout << "Please enter the y position for " << newName << ":" << endl;
		cin >> newY;
	} while (newY > 0);

	do
	{
		cout << "Please enter the average speed for " << newName << ":" << endl;
		cin >> newSpeed;
	} while (newSpeed > 0);

	do
	{
		cout << "Please enter the number of neighbours that " << newName << " has:" << endl;
		cin >> noNeighbours;
	} while (noNeighbours > 0);

	neighbours = new string[noNeighbours];
	for (int j = 0; j < noNeighbours; j++)
	{
		do
		{
			cout << "Please enter the name of neighbour number " << j + 1 << " :" << endl;
			cin >> curNeighbour;
		} while (!curNeighbour.empty());//Will also need to check that neighbour is valid destiantion
		neighbours[j] = curNeighbour;
	}


	outFile <<"\n"<< newName << ";" << newX << "," << newY << ";" << newSpeed << endl;
	outFile.close();
	//add this to the list
	Destination newDest({ 25, 25 }, { newX, newY }, newName, newSpeed,noNeighbours);
	//newDest.setNeighbours(neighbours);
	(*currentTop).push_back(newDest);

	//redo the neighbour lists
	list<Destination>::iterator begin = (*currentTop).begin(), end = (*currentTop).end(), It, It2;
	It = begin;
	while (It != end)
	{
		//set neighbour list for all destinations
		(*It).setNeighbourList(currentTop,neighbours);
		It++;
	}
}

void deleteDest(list<Destination>* top, string nodeToDelete, string fileName)
{
	list<Destination>::iterator begin = (*top).begin(), end = (*top).end(), It;

	It = begin;
	while (It != end)
	{
		if (It->getName() == nodeToDelete)
		{
			(*top).erase(It);
			break;
		}
		It++;
	}

	ofstream outFile;
	outFile.open(fileName + ".txt");
	It = begin;
	while (It != end)
	{
		//loop through neighbours array when rewriting text file, if the name found is equal to the name of the deleted node, ignore it
		//-1 from no neighbours 
		outFile << It->getName() << ";" << It->getPosition().x << "," << It->getPosition().y << ";" << It->getSpeed() << ";";

		list<Destination> neighbour = *((*It).getNeighbourList());
		list<Destination>::iterator begin = neighbour.begin(), end = neighbour.end(), It2;
		It2 = begin;
		bool removedNeighbour = false;
		while (It2 != end)
		{
			if (It2->getName() == nodeToDelete)
			{
				//if the current item in the neighbour list is the destination that was removed
				//delete it from the neighbour list
				neighbour.erase(It2);
				break;
			}
			It2++;
		}

		//output new neighbour number to file
		int noNeighbours = 0;
		if (removedNeighbour)
		{//if a neighbour was removed, reduce the number of neighbours by 1
			int newNoNeighbours = (It->getNoNeighbours()) - 1;
			outFile << newNoNeighbours << ";";
			noNeighbours = newNoNeighbours;
		}
		else
		{
			noNeighbours = It->getNoNeighbours();
			outFile << noNeighbours << ";";
		}

		//output the names of the destinations to the file
		It2 = begin;
		int curSize = 1;
		int counter = 1;
		while (It2 != end)
		{
			if (counter = noNeighbours&& It2->getName() != It->getName())
			{
				cout << "HOTLAND OUTPUT:" << It2->getName() << endl;
				outFile << It2->getName() <<endl;
			}
			else 
			{
				if (It2->getName() != It->getName())
				{
					outFile << It2->getName() << ",";
					counter = counter + 1;
				}
			}
			
			It2++;
		}
		It++;
	}
}

bool checkNetworkTop(string filename)
{
	string checkName, checkX, checkY, checkSpeed, checkNoNeighbours, checkNeighbour;
	ifstream inFile;
	filename = filename + ".txt";
	inFile.open(filename);
	//check to see there is a name
	getline(inFile, checkName, ';');
	getline(inFile, checkX, ',');
	getline(inFile, checkY, ';');
	getline(inFile, checkSpeed, ';');
	getline(inFile, checkNoNeighbours, ';');
	getline(inFile, checkNeighbour);
	if(checkName.empty() || checkX.empty() || checkY.empty() || checkSpeed.empty()||checkNoNeighbours.empty()||checkNeighbour.empty())
	{
		std::cout << "1  The topology given is invalid. Please provide another topology." << endl;
		return false;
	}
	else
	{
		try
		{
			stof(checkX);
			stof(checkY);
			stof(checkSpeed);
			stoi(checkNoNeighbours);
		}
		catch(invalid_argument)
		{
		std::cout << " 2 The topology given is invalid. Please provide another topology." << endl;
		return false;
		}
	}
	inFile.close();
	return true;
}