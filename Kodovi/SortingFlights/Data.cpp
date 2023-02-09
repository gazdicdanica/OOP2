#include "Data.h"

//prazan konstruktor koji inicijalizuje atribute na nulu
Data::Data() : numComp(0), numRot(0), numIter(0){}

//konstruktor koji kao ulazne parametre prima argumente koji odgovaraju atributima klase
Data::Data(unsigned long cmp, int rot, int it, vector<Flight>& data) : 
	numComp(cmp), numRot(rot), numIter(it), current(data) {}

//destruktor
Data::~Data() {}