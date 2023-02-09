#pragma once
#include "GUI.h"
#include "Window.h"
#include "Graph.h"
#include "InputArgs.h"
#include "Sort.h"

#define WINDOW_W			800
#define WINDOW_H			800
#define WINDOW_POSITION_X	350
#define BUTTON_W			100
#define BUTTON_H			30
#define RBUTTON_H			20
#define OUTBOX_W			150
#define OUTBOX_H			200
#define LINE_LENGTH			50
#define SPACE				16.5


using namespace Graph_lib;

struct MyWindow : public Window {
private:

	InputArgs inputArgs;
	vector<Data> sortedData;
	int i;

	In_box inputFile;
	In_box outputFile;
	Text txtInFile;
	Text txtOutFile;
	Button btnShow;

	Text alg;
	Button btnSelectionSort;
	Button btnQuickSort;

	Text sortBy;
	Button btnDestination;
	Button btnDeparture;
	Button btnFlightNo;
	Button btnGateNo;

	Out_box destination;
	Out_box departure;
	Out_box flightNo;
	Out_box gateNo;
	Text txtDest;
	Text txtDep;
	Text txtFlight;
	Text txtGate;

	Out_box unsorted;
	Out_box sorted;

	Text fileError;
	Text algError;
	Text critError;

	Text txtIteration;
	Out_box outIteration;
	Text txtChange;
	Out_box outChange;

	Text txtCrit;
	Text txtAlg;

	Lines lines;

	Button btnSort;
	Button btnNext;

	bool simulatePushed;
	bool selectionPushed;
	bool quickPushed;
	bool destinationPushed;
	bool departurePushed;
	bool flightPushed;
	bool gatePushed;

	static void cb_show(Address, Address);
	static void cb_next(Address, Address);
	static void cb_sort(Address, Address);
	static void cb_selection(Address, Address);
	static void cb_quick(Address, Address);
	static void cb_dest(Address, Address);
	static void cb_dep(Address, Address);
	static void cb_flight(Address, Address);
	static void cb_gate(Address, Address);

	void sort();
	void next();
	void selection();
	void quick();
	void dest();
	void dep();
	void flight();
	void gate();

public:
	MyWindow(Point xy, int w, int h, const string& title, InputArgs& ia);
	bool showData();
	void fillOutbox();
	string stringList(vector<Flight>&);
	void addLine(int, int);
};