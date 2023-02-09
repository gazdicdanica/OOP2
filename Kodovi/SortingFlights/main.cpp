//============================================================================
// Name        : main.cpp
// Author      : Danica Gazdic
// Date        :
// Copyright   :
// Description :
//============================================================================

#include "Flight.h"
#include "MyWindow.h"
#include "InputArgs.h"


using namespace std;


int main(int argc, char* argv[])
{
	string inputFile = "";
	string outputFile = "";
	int crit = 0;	//kriterijum za sortiranje
	int alg = 0;	//algoritam za sortiranje
	if (argc == 5) {
		inputFile = argv[1];
		inputFile = PATH + inputFile;
		outputFile = argv[2];
		outputFile = PATH + outputFile;
		crit = stoi(argv[3]);
		alg = stoi(argv[4]);
		if (crit > 2 || crit < 1 || alg > 4 || alg < 1) {
			cout << "Invalid command line arguments";
			return -1;
		}
	}
	InputArgs ia(inputFile, outputFile, crit, alg);
	MyWindow win(Point(350, 0), WINDOW_W, WINDOW_H, "Flight sorting", ia);
	Fl::run();
	return 0;

	// C:\\Users\\danic\\Documents\\OOP2\\SV12_2020_Danica_Gazdic\\Testovi\\


}