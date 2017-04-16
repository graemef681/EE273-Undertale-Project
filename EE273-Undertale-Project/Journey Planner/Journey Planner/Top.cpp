#include"Top.hpp"
using namespace std;

list<Destination> ReadFile(string filename)
{
start:
	//check notes on how to resize arrays to make sure this is correct
	string *ptrneighbour = NULL;
	list<Destination> Topology;
	list<string*> Nlists;
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
					if (i <= no_neighbours - 2)
					{
						getline(inFile, temp, ',');
						ptrneighbour[i] = temp;
						cout << "Neighbour " << i + 1 << " is " << temp << endl;
					}
					else if (i == no_neighbours - 1)
					{
						getline(inFile, temp);
						ptrneighbour[i] = temp;
						cout << "Last Neighbour " << i + 1 << " is " << temp << endl;
					}

				} 
				Nlists.push_back(ptrneighbour);
				Destination D({ 50, 50 }, { x, y }, name, speed_avg, no_neighbours);
				Topology.push_back(D);
			}
			inFile.close();
			list<Destination>::iterator Tbegin = Topology.begin(), Tend = Topology.end(), TIt;
			list<string*>::iterator Nbegin = Nlists.begin(), Nend = Nlists.end(), Nit;
			TIt = Tbegin;
			Nit = Nbegin;
			while (TIt != Tend)
			{
				//set neighbour list for all destinations
				(*TIt).setNeighbourList(&Topology, *Nit);
				cout << "Neighbours list has been set for: " << TIt->getName() << endl;
				TIt++; Nit++;
			}
			delete[] ptrneighbour;
			inFile.close();
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


void addNewDest(string fileName, list<Destination>* currentTop)
{
	//open the output file in append mode
	ofstream outFile(fileName + ".txt", ios::app);

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
	} while (newX < 0 || newX > 427);

	do
	{
		cout << "Please enter the y position for " << newName << ":" << endl;
		cin >> newY;
	} while (newY < 0 || newY > 488);

	do
	{
		cout << "Please enter the average speed for " << newName << ":" << endl;
		cin >> newSpeed;
	} while (newSpeed < 0);

	do
	{
		cout << "Please enter the number of neighbours that " << newName << " has:" << endl;
		cin >> noNeighbours;
	} while (noNeighbours < 0);
	outFile << "\n" << newName << ";" << newX << "," << newY << ";" << newSpeed << ";";
	outFile << noNeighbours << ";";
	for (int j = 0; j < noNeighbours; j++)
	{
		cout << "Please enter the name of neighbour number " << j + 1 << " :" << endl;
		cin >> curNeighbour;
		//If valid destination then
		outFile << curNeighbour;
		if (j != noNeighbours - 1)
			outFile << ","; //Will also need to check that neighbour is valid destiantion
	}
	outFile.close();
}

void deleteDest(list<Destination>* top, string nodeToDelete, string fileName)
{
	list<Destination>::iterator Tbegin = (*top).begin(), Tend = (*top).end(), It;
	ofstream outFile;
	outFile.open(fileName + ".txt");
	It = Tbegin;
	while (It != Tend)
	{
		//loop through neighbours array when rewriting text file, if the name found is equal to the name of the deleted node, ignore it
		//-1 from no neighbours 
		if (It->getName() != nodeToDelete)
			outFile << It->getName() << ";" << It->getPosition().x << "," << It->getPosition().y << ";" << It->getSpeed() << ";";

		list<Destination> neighbour = *((*It).getNeighbourList());
		list<Destination>::iterator Nbegin = neighbour.begin(), Nend = neighbour.end(), It2;
		It2 = Nbegin;
		while (It2 != Nend)
		{
			//Is a neighbour being deleted? if so decrement
			cout << It2->getName();
			//cout << "It1 = " << It->getName();
			if (It2->getName() == nodeToDelete)
			{
				//if the current item in the neighbour list is the destination is being removed
				//decrement noNeighbours for that destination
				It->setNoNeighbours((It->getNoNeighbours() - 1));
				//cout << "NoNeighbours Decremented = " << It->getNoNeighbours();
			}
			It2++;
		}
		//output new neighbour number to file
		if (It->getName() != nodeToDelete)
			outFile << It->getNoNeighbours() << ";";
		//output the names of the destinations to the file
		It2 = Nbegin;
		int counter = 0;
		while (It2 != Nend && It->getName() != nodeToDelete)
		{
			//cout << "IT2 -> getname = " << It2->getName();
			if (It2->getName() != It->getName() && It2->getName() != nodeToDelete)
			{
				counter++;
				if (counter < It->getNoNeighbours())
				{
					outFile << It2->getName() << ",";
				}
				else if (counter == It->getNoNeighbours())
				{
					outFile << It2->getName();
				}
			}
			
			It2++;
		}
		It++;
		if (It != Tend && It->getName() != nodeToDelete)
			outFile << endl;
		
	}
	//Search through destinations and delete from topology.
	It = Tbegin;
	while (It != Tend)
	{
		if (It->getName() == nodeToDelete)
		{
			cout << "TO ERASE" << endl;
			(*top).erase(It);
			break;
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