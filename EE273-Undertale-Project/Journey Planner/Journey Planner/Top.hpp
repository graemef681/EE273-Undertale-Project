#pragma once
#include<fstream>
#include<iostream>
#include"Destination.hpp"
#include<List>

std::list<Destination> ReadFile(std::string);
void addNewDest(std::string fileName, std::string newName, float newX, float newY, float newSpeed, std::string * neighbours, int noNeighbours);
void addNewDest(std::string fileName, std::list<Destination>* currentTop);
void deleteDest(std::list<Destination>*, std::string, std::string);
bool checkNetworkTop(std::string);