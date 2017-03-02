#include"Top.hpp"
using namespace std;

list<Destination> ReadFile(string filename)
{
start:
	string *neighbour;
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
				float speed_avg;
				getline(inFile, temp, ';');
				speed_avg = stof(temp);
				int no_neighbours;
				getline(inFile, temp, ';');
				no_neighbours = stoi(temp);
				neighbour = new string[no_neighbours];
				for (int i = 0; i < no_neighbours; i++)
				{
					getline(inFile, temp, ',');
					neighbour[i] = temp;
				}

				Destination D({ 25, 25 }, { x, y }, name, speed_avg);
				Topology.push_back(D);
				D.getNeighbours(&neighbour);
			}
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


void addNewDest(string fileName,list<Destination>* currentTop)
{
	//open the output file in append mode
	ofstream outFile(fileName +".txt", ios::app);

	string newName;
	float newX, newY;
	float newSpeed;

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


	outFile <<"\n"<< newName << ";" << newX << "," << newY << ";" << newSpeed << endl;
	outFile.close();
	//add this to the list
	Destination newDest({ 25, 25 }, { newX, newY }, newName, newSpeed);
	(*currentTop).push_back(newDest);
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
	outFile.open(fileName+".txt");
	It = begin;
	while (It != end)
	{
		//loop through neighbours array when rewriting text file, if the name found is equal to the name of the deleted node, ignore it
		//-1 from no neighbours 
		outFile << It->getName() << ";" << It->getPosition().x << "," << It->getPosition().y << ";" << It->getSpeed() << endl;
		It++;
	}
}

bool checkNetworkTop(string filename)
{
	string checkName, checkX, checkY, checkSpeed;
	ifstream inFile;
	filename = filename + ".txt";
	inFile.open("test.txt");
	//check to see there is a name
	getline(inFile, checkName, ';');
	getline(inFile, checkX, ',');
	getline(inFile, checkY, ';');
	getline(inFile, checkSpeed);
	if(checkName.empty() || checkX.empty() || checkY.empty() || checkSpeed.empty())
	{
		std::cout << "The topology given is invalid. Please provide another topology." << endl;
		return false;
	}
	else
	{
		try
		{
			stof(checkX);
			stof(checkY);
			stof(checkSpeed);
		}
		catch(invalid_argument)
		{
		std::cout << "The topology given is invalid. Please provide another topology." << endl;
		return false;
		}
	}
	inFile.close();
	return true;
}