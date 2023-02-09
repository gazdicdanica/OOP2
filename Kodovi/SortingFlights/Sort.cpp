//============================================================================
// Name        : Sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of the sort classes
//============================================================================

#include "Sort.h"

using namespace std;

//funkcije koje resetuju brojace (inicijalizuju na 0)
void Sort::resetNumCmps() {
	(*this).numCmps = 0;
}

void Sort::resetNumRot() {
	(*this).numRot = 0;
}

void Sort::resetNumIter() {
	(*this).numIter = 0;
}

// geteri atributa
unsigned long Sort::getNumCmps() {
	return this->numCmps;
}

int Sort::getNumRot() {
	return this->numRot;
}

int Sort::getNumIter() {
	return this->numIter;
}

vector<Data> Sort::getSortedData() {
	return this->sortedData;
}

// funkcija menja mesta dva elementa vektora. Prima pokazivace na dva leta, a nema povratnu vrednost
void QuickSort::swap(Flight* a, Flight* b) {
	if ( ! (*a == *b)) {
		this->numRot++;
	}
	Flight f = *a;
	*a = *b;
	*b = f;
}

/*Partition funkcije se razlikuju samo po kriterijumu po kom uporedjuju elemente.
Funkcije primaju referencu na vektor objekata tipa Flight, i vrednosti granica intervala.
Za pivot se uzima poslednji element. Svi manji elementi od pivota postavljaju se sa njegove 
leve strane, a svi veci sa desne. Funkcija vraca indeks narednog pivota*/
int QuickSort::partitionDest(std::vector<Flight>& data, int a, int b) {
	Flight f = data[b];
	int i = a - 1;
	this->numIter++;
	for (int j = a; j <= b - 1; j++) {
		this->numCmps++;
		if (data[j].getDestination() <= f.getDestination()) {
			i++;
			swap(&data[i], &data[j]);
		}
	}
	
	swap(&data[i + 1], &data[b]);
	sortedData.push_back(Data(numCmps, numRot, numIter, data));
	return(i + 1);
}

int QuickSort::partitionDep(std::vector<Flight>& data, int a, int b) {
	Flight f = data[b];
	int i = a - 1;

	this->numIter++;
	for (int j = a; j <= b - 1; j++) {
		this->numCmps++;
		string a = data[j].getDeparture();
		string b = f.getDeparture();
		if (a.size() == 4) {
			a = "0" + a;
		}
		if (b.size() == 4) {
			b = "0" + b;
		}
		if (a <= b) {
			i++;
			swap(&data[i], &data[j]);
		}
	}
	
	swap(&data[i + 1], &data[b]);
	sortedData.push_back(Data(numCmps, numRot, numIter, data));
	return(i + 1);
}

int QuickSort::partitionFlight(std::vector<Flight>& data, int a, int b) {
	Flight f = data[b];
	int i = a - 1;
	this->numIter++;
	for (int j = a; j <= b - 1; j++) {
		this->numCmps++;
		if (data[j].getFlightNo() <= f.getFlightNo()) {
			i++;
			swap(&data[i], &data[j]);
		}
	}
	
	swap(&data[i + 1], &data[b]);
	sortedData.push_back(Data(numCmps, numRot, numIter, data));
	return(i + 1);
}

int QuickSort::partitionGate(std::vector<Flight>& data, int a, int b) {
	Flight f = data[b];
	int i = a - 1;
	this->numIter++;
	for (int j = a; j <= b - 1; j++) {
		this->numCmps++;
		if (data[j].getGateNo() <= f.getGateNo()) {
			i++;
			swap(&data[i], &data[j]);
		}
	}
	
	swap(&data[i + 1], &data[b]);
	sortedData.push_back(Data(numCmps, numRot, numIter, data));
	return(i + 1);
}

// konstruktor klase QuickSort. Parametar funkcije je vrednost tipa int koja predstavlja
// kriterijum po kojem je potrebno vrsiti sortiranje
QuickSort::QuickSort(int crit) { criterium = crit; }

/*preklopljena metoda sort bazne klase Sort. U njoj se vrsi inicijalizovanje brojaca
na nulu i inicijalni poziv glavne metode za sortiranje algoritma quicksort.*/
void QuickSort::sort(std::vector<Flight>& data) {
	resetNumCmps();
	resetNumIter();
	resetNumRot();
	int a = 0;
	int b = data.size() - 1;
	sortedData.clear();
	sortedData.push_back(Data(0, 0, 0, data));
	sort(data, a, b);
	
}

/*glavna funkcija quicksort algoritma. Rekurzivna je i kao ulazne parametre prima referencu na 
vektor objekata klase Flight koji je potrebno sortirati, i granice intervala koga treba sortirati.
U odnosu na kriterijum sortiranja poziva se funkcija partitionCriterium.*/
void QuickSort::sort(std::vector<Flight>& data, int a, int b) {
	
	int p;

	if (a < b) {
		switch (criterium) {
		case 1:
			p = this->partitionDest(data, a, b);
			break;
		case 2:
			p = this->partitionDep(data, a, b);
			break;
		case 3:
			p = this->partitionFlight(data, a, b);
			break;
		case 4:
			p = this->partitionGate(data, a, b);
			break;
		}
		(*this).sort(data, a, p - 1);
		(*this).sort(data, p + 1, b);
	}

}


//konstruktor klase SelectionSort, ulazni parametar predstavlja kriterijum po kom se sortira.
SelectionSort::SelectionSort(int crit) { criterium = crit; }

/*glavna funkcija selection algortima za sortiranje. kao ulazni parametar prima referencu na vektor
objekata klase Flight koji je potrebno sortirati. Sortiranje se vrsi u odnosu na izabrani kriterijum i to je 
razgrniceno switch-em. Algoritam pretrazuje ceo vektor i trazi najmanji element. Kada ga pronadje fiksira
se na prvo mesto i zatim se pretrazuje ostatak vektora kako bi se pronasao sledeci najmanji element i fiksirao na prvo
sledece mesto i tako dok se ne sortira ceo vektor.*/
void SelectionSort::sort(std::vector<Flight>& data) {
	int min;
	resetNumCmps();
	resetNumRot();
	resetNumIter();
	sortedData.clear();
	sortedData.push_back(Data(0,0,0,data));
		switch (criterium) {
		case 1:
		{
			int i;
			for (i = 0; i < data.size() - 1; i++) {
				min = i;
				for (int j = i + 1; j < data.size(); j++) {
					(*this).numCmps++;
					if (data[j].getDestination() < data[min].getDestination()) {
						min = j;
					}
				}
				if (min != i) {
					this->numRot++;
				}
				std::iter_swap(data.begin() + min, data.begin() + i);
				sortedData.push_back(Data(numCmps, numRot, i+1, data));

			}
			this->numIter = i;
			break;
		}
		case 2:
		{
			int i;
			for (i = 0; i < data.size() - 1; i++) {
				min = i;
				for (int j = i + 1; j < data.size(); j++) {
					(*this).numCmps++;
					string a = data[j].getDeparture();
					string b = data[min].getDeparture();
					if (a.size() == 4) {
						a = "0" + a;
					}
					if (b.size() == 4) {
						b = "0" + b;
					}
					if (a < b) {
						min = j;
					}
				}
				if (min != i) {
					this->numRot++;
				}
				std::iter_swap(data.begin() + min, data.begin() + i);
				sortedData.push_back(Data(numCmps, numRot, i+1, data));
			}
			this->numIter = i;
			break;
		}
			
		case 3: 
		{
			int i;
			for (i = 0; i < data.size() - 1; i++) {
				min = i;
				for (int j = i + 1; j < data.size(); j++) {
					(*this).numCmps++;
					if (data[j].getFlightNo() < data[min].getFlightNo()) {
						min = j;
					}
				}
				if (min != i) {
					this->numRot++;
				}
				std::iter_swap(data.begin() + min, data.begin() + i);
				sortedData.push_back(Data(numCmps, numRot, i+1, data));
			}
			this->numIter = i;
			break;
		}
			
		case 4:
		{
			int i;
			for (i = 0; i < data.size() - 1; i++) {
				min = i;
				for (int j = i + 1; j < data.size(); j++) {
					(*this).numCmps++;
					if (data[j].getGateNo() < data[min].getGateNo()) {
						min = j;
					}
				}
				if (min != i) {
					this->numRot++;
				}
				std::iter_swap(data.begin() + min, data.begin() + i);
				sortedData.push_back(Data(numCmps, numRot, i+1, data));
			}
			this->numIter = i;
			break;
		}
			
			}
}
