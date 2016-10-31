// Travelling Salesperson 2D
// https://kth.kattis.com/problems/tsp

// compile with: g++ filename.cpp
// Run with: ./a.out

// Imports
#include <math.h>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

// global variables
int n;
vector<vector<float> > coordinates;

// function declaractions
void getInput();
void getFirstLine();
void resizeCoordinateVector();
float dist(int a, int b);

int main() {
	getFirstLine();
	resizeCoordinateVector();
	getInput();

	// testing for globality
	for (int i = 0; i < ::n; ++i) {
		cout << ::coordinates[i][0];
		cout << ::coordinates[i][1];
	}
	cout << ::n;

	return 0;
}

void getFirstLine() {
	string input = 	"";
	
	getline(cin, input);
	stringstream myStream(input);
	myStream >> ::n;
}

void resizeCoordinateVector() {
	::coordinates.resize(::n);
	for (int i = 0; i < ::n; ++i) {
		::coordinates[i].resize(2);
	}
} 

void getInput() {
	string input = 	"";

	for (int i = 0	; i < ::n; ++i) {
		getline(cin, input);
    	istringstream buf(input);
    	istream_iterator<string> beg(buf), end;
    	vector<string> tokens(beg, end);

		::coordinates[i][0] = atof(tokens[0].c_str());
		::coordinates[i][1] = atof(tokens[1].c_str());
	}
}

vector<int> GreedyTour(int n) {
	// initalize some variables
	vector<int> tour(n);
	vector<bool> used(n);
	used[0] = true;
	int best = -1;

	// run the actual algorithm
	for (int i = 1; i < n; ++i) {
		best = -1;
		for (int j = 0; j < n; ++j) {
			if (!used[j] && (best == -1 || dist(tour[i-1],j) < dist(tour[i-1],best) ) ) {
				best = j;
			}
		}
		tour[i] = best;
		used[best] = true;
	}
	return tour;
}

float dist(int a, int b) {
    float x = ::coordinates[a][0] - ::coordinates[b][0];
    float y = ::coordinates[a][1] - ::coordinates[b][1];

    return  sqrt(pow(x,2) + pow(y,2));
}
