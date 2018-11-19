#include <iostream>
#include <fstream>
#include "Record.h"
using namespace std;

ofstream openFile(string fileName) {
	ofstream myfile;
	myfile.open(fileName);
	return myfile;
}

void writeFile(int key, long long start, long long end, ofstream &myfile) {
	if (&myfile != nullptr) {
		myfile << "key " << key << "\t" << start << "\t" << end << "\n";
	}
}

void closeFile(ofstream &myfile) {
	myfile.close();
}