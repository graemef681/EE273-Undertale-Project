#pragma once
#include<fstream>
#include<iostream>
#include"Destination.hpp"
#include<List>

std::list<Destination> ReadFile(std::string);
void addNewDest(std::string, std::list<Destination>*);
void deleteDest(std::list<Destination>*, std::string, std::string);
void checkNetworkTop(std::string);