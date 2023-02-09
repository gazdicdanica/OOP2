//============================================================================
// Name        : Flight.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of the Flight class
//============================================================================

#include "Flight.h"

using namespace std;

//prazan konstruktor
Flight::Flight() {};

//Konstruktor koji kao argumente prima vrednosti svih atributa klase Flight
Flight::Flight(string flNo, string dest, string dep, string gate) : flightNo(flNo), destination(dest), departure(dep), gateNo(gate) {}

//Konstruktor kopije koji kao argument prima referencu na objekat klase Flight
Flight::Flight(const Flight& other) : flightNo(other.flightNo), destination(other.destination), departure(other.departure), gateNo(other.gateNo) {}

//Destruktor
Flight::~Flight() {};

//geteri
string Flight::getFlightNo() const {
	return flightNo;
}

string Flight::getDestination() const {
	return destination;
}

string Flight::getDeparture() const {
	return departure;
}

string Flight::getGateNo() const {
	return gateNo;
}

//preklopljen operator == koji poredi 2 objekta klase Flight
//i vraca true ukoliko su im brojevi leta jednaki
bool Flight::operator==(const Flight& other) {
	if (other.flightNo == flightNo) {
		return true;
	}
	else {
		return false;
	}
}

/*preklopljen operator>> -za ucitavanje objekata klase Flight; prima referencu na ulazni stream i referencu
	na objekat klase Flight; povratna vrednost je referenca na stream*/
istream& operator>>(istream& in, Flight& flight) {
	string flightNo;
	string dep;
	string dest;
	string gate;
	string h;
	getline(in, h);		//zaglavlje
	h = "";
	in >> h;
	dest = h;
	while (dest.find(";") == string::npos) {
		in >> h;
		dest = dest + " " + h;
	}dest.replace(dest.length() - 1, 1, "");
	flight.destination = dest;
	in >> dep;
	dep.replace(dep.length() - 1, 1, "");
	in >> flightNo;
	flightNo.replace(flightNo.length() - 1, 1, "");
	in >> gate;
	gate.replace(gate.length() - 1, 1, "");
	flight.flightNo = flightNo;
	flight.departure = dep;
	flight.gateNo = gate;
	return in;
}


/*preklopljen operator<< -za ispis objekata klase Flight; prima referencu na izlazni stream i referencu
	na objekat klase Flight koji je potrebno ispisati; povratna vrednost je referenca na stream*/
ostream& operator<<(ostream& out, const Flight& flight) {
	out << flight.destination << "; " << flight.departure << "; " << flight.flightNo << "; " << flight.gateNo;
	return out;
}
