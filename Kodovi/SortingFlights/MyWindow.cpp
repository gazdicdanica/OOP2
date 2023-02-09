#include "MyWindow.h"
#include "Data.h"

MyWindow::MyWindow(Point xy, int w, int h, const string& title, InputArgs& ia) :
	Window(xy, w, h, title),
	inputArgs(ia),
	inputFile(Point(150, 10), w - 300, 25, ""),
	outputFile(Point(150, 40), w - 300, 25, ""),
	txtInFile(Point(10, 28), "Input file: "),
	txtOutFile(Point(10, 60), "Output file: "),
	btnShow(Point(WINDOW_W - BUTTON_W - 20, 25), BUTTON_W, BUTTON_H, "Show", cb_show),
	alg(Point(10, 90 + BUTTON_H - 12), "Sorting algorithm: "),
	btnSelectionSort(Point(w / 2 - 100, 90), BUTTON_W, BUTTON_H, "Selection sort", cb_selection),
	btnQuickSort(Point(w / 2 + 100, 90), BUTTON_W, BUTTON_H, "Quick sort", cb_quick),
	sortBy(Point(10, 150), "Sort by: "),
	btnDestination(Point(x_max() / 5, 135), BUTTON_W, BUTTON_H, "Destination", cb_dest),
	btnDeparture(Point(2 * x_max() / 5, 135), BUTTON_W, BUTTON_H, "Departure", cb_dep),
	btnFlightNo(Point(3 * x_max() / 5, 135), BUTTON_W, BUTTON_H, "Flight number", cb_flight),
	btnGateNo(Point(4 * x_max() / 5, 135), BUTTON_W, BUTTON_H, "Gate number", cb_gate),
	txtDest(Point(10, 220), "Destination"),
	txtDep(Point(210, 220), "Departure"),
	txtFlight(Point(410, 220), "Flight number"),
	txtGate(Point(610, 220), "Gate number"),
	destination(Point(10, 230), OUTBOX_W, OUTBOX_H, ""),
	departure(Point(210, 230), OUTBOX_W, OUTBOX_H, ""),
	flightNo(Point(410, 230), OUTBOX_W, OUTBOX_H, ""),
	gateNo(Point(610, 230), OUTBOX_W, OUTBOX_H, ""),
	btnSort(Point(w / 2 - 150, 260 + OUTBOX_H), BUTTON_W, BUTTON_H, "Sort", cb_sort),
	btnNext(Point(w / 2 + 50, 260 + OUTBOX_H), BUTTON_W, BUTTON_H, "Next", cb_next),
	txtAlg(Point(10, 470), ""),
	txtCrit(Point(10, 500), ""),
	unsorted(Point(0, 520), OUTBOX_W, OUTBOX_H, ""),
	sorted(Point(x_max() - OUTBOX_W, 520), OUTBOX_W, OUTBOX_H, ""),
	fileError(Point(220, 600), "An error occured while trying to open files."),
	algError(Point(180, 600), "Please choose a sorting algorithm you want to use"),
	critError(Point(220,600), "Please choose criterium for sorting"),
	txtIteration(Point(100, 770), "Iteration count:"),
	outIteration(Point(250, 750), 50, 30, ""),
	txtChange(Point(440,770), "Rotations made: "),
	outChange(Point(600,750), 50, 30, ""),
	simulatePushed(false), destinationPushed(false), departurePushed(false), 
	flightPushed(false), gatePushed(false), selectionPushed(false), quickPushed(false)
{
	attach(inputFile); 
	attach(outputFile); 
	attach(txtInFile); 
	attach(txtOutFile);
	attach(btnSelectionSort); 
	attach(btnQuickSort); 
	attach(sortBy); 
	attach(alg);
	attach(btnDestination); 
	attach(btnDeparture); 
	attach(btnFlightNo); 
	attach(btnGateNo);
	attach(txtDep); 
	attach(txtDest); 
	attach(txtFlight); 
	attach(txtGate);
	attach(destination);
	attach(departure); 
	attach(flightNo); 
	attach(gateNo);
	attach(btnSort);
	attach(btnNext);
	attach(unsorted); 
	attach(sorted); 
	attach(btnShow);
	attach(txtChange); 
	attach(txtIteration); 
	attach(outIteration); 
	attach(outChange);
	attach(txtAlg);
	attach(txtCrit);
	txtAlg.set_color(FL_BLACK);
	txtCrit.set_color(FL_BLACK);
	fileError.set_color(FL_RED); 
	critError.set_color(FL_RED); 
	algError.set_color(FL_RED);
	txtIteration.set_color(FL_BLACK);
	txtChange.set_color(FL_BLACK);
	txtInFile.set_color(FL_BLACK); 
	txtOutFile.set_color(FL_BLACK); 
	alg.set_color(FL_BLACK);
	txtDep.set_color(FL_BLACK); 
	txtDest.set_color(FL_BLACK); 
	txtFlight.set_color(FL_BLACK);
	txtGate.set_color(FL_BLACK); 
	sortBy.set_color(FL_BLACK);
	lines.set_color(FL_BLACK);
	lines.set_fill_color(FL_BLACK);
	attach(lines);

}

// metode za regulisanje rada objekata klase Button
void MyWindow::cb_dep(Address, Address pw) { 
	reference_to<MyWindow>(pw).dep(); 
}
void MyWindow::cb_dest(Address, Address pw) { 
	reference_to<MyWindow>(pw).dest(); 
}
void MyWindow::cb_flight(Address, Address pw) { 
	reference_to<MyWindow>(pw).flight(); 
}
void MyWindow::cb_gate(Address, Address pw) { 
	reference_to<MyWindow>(pw).gate(); 
}
void MyWindow::cb_quick(Address, Address pw) { 
	reference_to<MyWindow>(pw).quick(); 
}
void MyWindow::cb_selection(Address, Address pw) { 
	reference_to<MyWindow>(pw).selection(); 
}
void MyWindow::cb_sort(Address, Address pw) { 
	reference_to<MyWindow>(pw).sort(); 
}

void MyWindow::cb_next(Address, Address pw) {
	reference_to<MyWindow>(pw).next();
}

void MyWindow::cb_show(Address, Address pw) {
	reference_to<MyWindow>(pw).showData();
}

/*funkcija nema ulazne parametre, a kao povratnu vrednost vraca bool vrednost
u zavisnosti od toga da li je (ne)uspesno otvoren ulazni fajl. Daje korisniku 
adekvatnu povratnu informaciju ukoliko otvaranje zadatog fajla nije moguce.
u definiciji sadrzi i poziv funkcije fillOutbox*/ 
bool MyWindow::showData() {
	string input = inputArgs.inputFileName;
	if (input == "") {
		input = inputFile.get_string();
		inputArgs.inputFileName = input;

	}
	if (inputArgs.flights.empty()) {
		bool x = inputArgs.loadData();
		if (!x) {
			(*this).attach(fileError);
			Fl::redraw();
			while (!GetKeyState(VK_LBUTTON)) {
				Fl::wait();
			}
			detach(fileError);
			Fl::redraw();
			return false;
		}

	}
	fillOutbox();
		
	return true;
}

/* funkcija nema ni ulazne parametre, ni povratnu vrednost.
Sluzi za ispis podataka o letovima u out_box-ove*/
void MyWindow::fillOutbox() {
	vector<Flight>::iterator it;
	string destList = "";
	string depList = "";
	string flighList = "";
	string gateList = "";
	for (it = inputArgs.flights.begin(); it != inputArgs.flights.end(); it++) {
		destList += (*it).getDestination() + '\n';
		depList += (*it).getDeparture() + '\n';
		flighList += (*it).getFlightNo() + '\n';
		gateList += (*it).getGateNo() + '\n';
	}

	destination.put(destList);
	departure.put(depList);
	flightNo.put(flighList);
	gateNo.put(gateList);
}


/*Metoda prima referencu na vektor letova i vraca string atributa u odnosu
na kriterijum pretrage koji je pogodan za ispis u out_box za simulaciju sortiranja.*/
string MyWindow::stringList(vector<Flight>& data) {
	vector<Flight>::iterator it;
	string val = "";
	switch (inputArgs.criterium) {
	case 1:
		for (it = data.begin(); it != data.end(); it++) {
			val += (*it).getDestination() + "\n";
		}
		break;
	case 2:
		for (it = data.begin(); it != data.end(); it++) {
			val += (*it).getDeparture() + "\n";
		}
		break;
	case 3:
		for (it = data.begin(); it != data.end(); it++) {
			val += (*it).getFlightNo() + "\n";
		}
		break;
	case 4:
		for (it = data.begin(); it != data.end(); it++) {
			val += (*it).getGateNo() + "\n";
		}
		break;
	}
	return val;
}

//metode za regulisanje rada objekata klase Button
void MyWindow::dep() {
	departurePushed = true;
	destinationPushed = false;
	flightPushed = false;
	gatePushed = false;
	inputArgs.criterium = 2;
	txtCrit.set_label("Departure");
	Fl::redraw();
}

void MyWindow::dest() {
	departurePushed = false;
	destinationPushed = true;
	flightPushed = false;
	gatePushed = false;
	inputArgs.criterium = 1;
	txtCrit.set_label("Destination");
	Fl::redraw();
}

void MyWindow::flight() {
	departurePushed = false;
	destinationPushed = false;
	flightPushed = true;
	gatePushed = false;
	inputArgs.criterium = 3;
	txtCrit.set_label("Flight No.");
	Fl::redraw();
}

void MyWindow::gate() { 
	departurePushed = false;
	destinationPushed = false;
	flightPushed = false;
	gatePushed = true; 
	inputArgs.criterium = 4;
	txtCrit.set_label("Gate No.");
	Fl::redraw();
}

/*Ova metoda je namenjena za regulisanje pritiskanja na dugme "Sort".
Proverava da li je izabran kriterijum i algoritam za sortiranje i 
daje korisniku adekvatnu povratnu informaciju ukoliko nisu.
Takodje proverava i da li su ulazni i izlazni fajlovi korektni.
Poziva se sortiranje po izabranom algoritmu, ispisuju se rezultati sortiranja
i u izlazni fajl se upisuje konacan rezultat kao i podaci prikupljeni tokom sortiranja.*/
void MyWindow::sort() {
	simulatePushed = true;
	string output = inputArgs.outputFileName;
	if (output == "") {
		output = outputFile.get_string();
		inputArgs.outputFileName = output;
	}
	if (inputArgs.algorithm == NULL) {
		(*this).attach(algError);
		Fl::redraw();
		while (!GetKeyState(VK_LBUTTON)) {
			Fl::wait();
		}
		detach(algError);
		Fl::redraw();
		return;
	}
	if (inputArgs.criterium == NULL) {
		attach(critError);
		Fl::redraw();
		while (!GetKeyState(VK_LBUTTON)) {
			Fl::wait();
		}
		detach(critError);
		Fl::redraw();
		return;
	}
	if (inputArgs.flights.empty()) {
		bool x = showData();
		if (!x) {
			return;
		}
	}
	if (!inputArgs.output(true)) {
		(*this).attach(fileError);
		Fl::redraw();
		while (!GetKeyState(VK_LBUTTON)) {
			Fl::wait();
		}
		detach(fileError);
		Fl::redraw();
		return;
	}
	
	i = 0;

	if (inputArgs.algorithm == 1) {
		unsorted.put(stringList(inputArgs.flights));
		sorted.put(stringList(inputArgs.flights));
		SelectionSort sSort(inputArgs.criterium);
		sSort.sort(inputArgs.flights);
		fillOutbox();
		Data data(sSort.getNumCmps(), sSort.getNumRot(), sSort.getNumIter(), inputArgs.flights);
		inputArgs.output(false, data);
		sortedData = sSort.getSortedData();
		Fl::redraw();
	}
	else{
		unsorted.put(stringList(inputArgs.flights));
		sorted.put(stringList(inputArgs.flights));
		QuickSort qSort(inputArgs.criterium);
		qSort.sort(inputArgs.flights);
		fillOutbox();
		Data data(qSort.getNumCmps(), qSort.getNumRot(), qSort.getNumIter(), inputArgs.flights);
		inputArgs.output(false, data);
		sortedData = qSort.getSortedData();
		Fl::redraw();
	}
	
}

void MyWindow::selection() {
	quickPushed = false;
	selectionPushed = true;
	inputArgs.algorithm = 1;
	txtAlg.set_label("Selection sort");
	Fl::redraw();
}

void MyWindow::quick() {
	quickPushed = true;
	selectionPushed = false;
	inputArgs.algorithm = 2;
	txtAlg.set_label("Quicksort");
	Fl::redraw();
}

/*Funkcija prima referencu na objekat klase Flight i na vektor iste klase.
Povratna vrednost je tipa int i predstavlja indeks prosledjenog leta u prosledjenom vektoru*/
int findNext(Flight& f, vector<Flight>& vector) {
	for (int i = 0; i < vector.size(); i++) {
		if (f == vector[i]) {
			return i;
		}
	}
}


/*metoda koja handle-uje dugme next i u odnosu na sacuvane vrednosti tokom sortiranja
iscrtava linije izmedju istih letova u svim iteracijama*/
void MyWindow::next() {
	if (i == sortedData.size()-1) {
		return;
	}
	
	Data sd1 = sortedData[i];
	Data sd2 = sortedData[i + 1];
	
	for (int k = 0; k < sd1.current.size(); k++) {
		int nexti = findNext(sd1.current[k], sd2.current);
		addLine(k, nexti);
		lines.draw_lines();
		sorted.put(stringList(sd2.current));
		Fl::redraw();
	}

	outIteration.put(sd2.numIter);
	outChange.put(sd2.numRot);
	i++;

}

void MyWindow::addLine(int m, int n) {
	Point p1(OUTBOX_W + i * LINE_LENGTH, 525 + m * SPACE);
	Point p2(OUTBOX_W + (i+1) * LINE_LENGTH, 525 + n * SPACE);
	lines.add(p1, p2);
	/*Circle c1(p1, 5);
	Circle c2(p2, 5);
	this->attach(c1);
	this->attach(c2);*/
}
