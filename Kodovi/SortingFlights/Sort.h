//============================================================================
// Name        : Sort.h
// Author      : 
// Date        :
// Copyright   : 
// Description : Sort interface class and various sorting algorithms in C++
//============================================================================
#pragma once

#include "Flight.h"
#include "Data.h"
#include <vector>


// Sort class
class Sort
{
protected:
	// number of comparisons performed in sort function
	unsigned long numCmps;
	int numRot;
	int numIter;
	int criterium;
	vector<Data> sortedData;
public:
	// main entry point
	virtual void sort(std::vector<Flight>& data) = 0;
	// returns number of comparisons
	unsigned long getNumCmps();
	// resets the number of comparisons
	void resetNumCmps();

	int getNumRot();
	void resetNumRot();

	int getNumIter();
	void resetNumIter();
	vector<Data> getSortedData();
};

// SelectionSort class
class SelectionSort : public Sort
{
public:
	SelectionSort(int crit);
	// main entry point
	void sort(std::vector<Flight>& data);
};

//QuickSort class
class QuickSort : public Sort {
public:
	QuickSort(int crit);
	void sort(std::vector<Flight>& data);
	void sort(std::vector<Flight>& data, int a, int b);
	int partitionGate(vector<Flight>& data, int a, int b);
	int partitionFlight(vector<Flight>& data, int a, int b);
	int partitionDep(vector<Flight>& data, int a, int b);
	int partitionDest(vector<Flight>& data, int a, int b);
	void swap(Flight*, Flight*);
};
