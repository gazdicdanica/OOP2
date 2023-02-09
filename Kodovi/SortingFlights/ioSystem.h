#pragma once
#include <vector>
#include <string>
#include "Flight.h"
#include "InputArgs.h"

class ioSystem {
	vector<Flight> flights;
	InputArgs inputArgs;

public:
	ioSystem(InputArgs inputArgs);
	//bool loadData();
	bool writeData();

	vector<Flight> getFlights();
	InputArgs getInputArgs();
};
