#pragma once
#include "Flight.h"
#include "Data.h"
#include <string>
#include <vector>

#define PATH	"C:\\Users\\danic\\Documents\\OOP2\\SV12_2020_Danica_Gazdic\\Testovi\\"

using namespace std;

class InputArgs {
public:
	string inputFileName;
	string outputFileName;
	int criterium;	// 1 - destination, 2 - departure, 3 - flightNo, 4 - gateNo
	int algorithm;	// 1 - selectionSort, 2 - quickSort

	vector<Flight> flights;

	InputArgs(string input, string output, int crit, int alg);
	InputArgs(InputArgs& ia);
	~InputArgs();
	
	bool loadData();
	bool output(bool, Data& d = Data());
};
