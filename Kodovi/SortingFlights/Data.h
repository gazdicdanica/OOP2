#pragma once
#include "Flight.h"
#include <vector>

class Data {
public:
	unsigned long numComp;
	int numRot;
	int numIter;
	vector<Flight> current;

	Data();
	Data(unsigned long, int, int, vector<Flight>&);
	~Data();

};