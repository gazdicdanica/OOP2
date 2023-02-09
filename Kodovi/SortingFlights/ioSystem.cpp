#include "ioSystem.h"
#include <string>
#include <fstream>

ioSystem::ioSystem(InputArgs input) : inputArgs(input) {}

//bool ioSystem::loadData() {
//	string inputFile = inputArgs.inputFile;
//	//cout << "\n" + inputFile;
//	ifstream in(inputFile.c_str());
//	in.exceptions(in.exceptions() | ios_base::badbit);
//	if (!in)
//		return false;
//	Flight f;
//
//	for (int i = 0; i < 10; i++) {
//		Flight f;
//		in >> f;
//		flights.push_back(f);
//	}
//	in.close();
//	return true;
//}

vector<Flight> ioSystem::getFlights() {
	return flights;
}

InputArgs ioSystem::getInputArgs() {
	return inputArgs;
}