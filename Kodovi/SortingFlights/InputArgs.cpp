#include "InputArgs.h"
#include <fstream>

//konstruktor koji prima argumente koji odgovaraju atributima klase
InputArgs::InputArgs(string input, string output, int crit, int alg) : 
	inputFileName(input), outputFileName(output), criterium(crit), algorithm(alg) {}

InputArgs::InputArgs(InputArgs& ia) : 
	inputFileName(ia.inputFileName), outputFileName(ia.outputFileName), criterium(ia.criterium), algorithm(ia.algorithm){}

//destruktor
InputArgs::~InputArgs(){}

/*Funkcija koja nema ulazne parametre, sluzi za ucitavanje podataka iz ulaznog fajla
i vraca bool vrednost u skladu sa tim da li je ucitavanje uspesno izvrseno.*/
bool InputArgs::loadData() {
	ifstream in;
	in.open(inputFileName.c_str(), std::ios_base::in);
	in.exceptions(in.exceptions() | ios_base::badbit);
	if (in.fail()) {
		return false;
	}
	Flight f;

	for (int i = 0; i < 10; i++) {
		Flight f;
		in >> f;
		flights.push_back(f);
	}
	return true;
}

/*Funkcija prima vrednost tipa bool koja odredjuje da li se samo proverava ispravnost izlaznog fajla
ili se vrsi i upis i referencu na objekat klase Data. Funkcija vraca bool vrednost u odnosu na 
uspesnot otvaranja fajla/upisa u fajl*/
bool InputArgs::output(bool open, Data& d) {
	ofstream out;
	out.open(outputFileName.c_str(), std::ios_base::out);
	out.exceptions(out.exceptions() | ios_base::badbit);
	if (out.fail()) {
		return false;
	}
	if (open) {
		return true;
	}
	for (int i = 0; i < 10; i++) {
		out << flights[i] << endl;
	}
	out << "Number of comparisons: " << d.numComp << endl;
	out << "Number of rotations: " << d.numRot << endl;
	out << "Number of iterations: " << d.numIter << endl;
	return true;
	
}