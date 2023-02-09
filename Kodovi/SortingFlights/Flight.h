//============================================================================
// Name        : Flight.h
// Author      : Danica Gazdic
// Date        : 05.01.2022.
// Copyright   :
// Description :
//============================================================================
#pragma once
#include <string>
#include <iostream>

using namespace std;

class Flight
{
	// your definition goes here
	string flightNo;
	string destination;
	string departure;
	string gateNo;

public:
	
	Flight();
	Flight(string, string, string, string);
	Flight(const Flight&);
	~Flight();
	string getFlightNo() const;
	string getDestination() const;
	string getDeparture() const;
	string getGateNo() const;

	bool operator==(const Flight& other);

	friend istream& operator>>(istream& in, Flight& flight);
	friend ostream& operator<<(ostream& out, const Flight& flight);
};
