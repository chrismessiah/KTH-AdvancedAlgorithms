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
vector<int> greedyTour();
void printForKattis(vector<int> output);

int main() {
	getFirstLine();
	resizeCoordinateVector();
	getInput();
	vector<int> output = greedyTour();
	printForKattis(output);
	return 0;
}

void printForKattis(vector<int> output) {
	for (int i = 0; i < ::n; ++i) {
		cout << output[i] << "\n";
	}
}

void getFirstLine() {
	cin >> ::n;
}

void resizeCoordinateVector() {
	::coordinates.resize(::n);
	for (int i = 0; i < ::n; ++i) {
		::coordinates[i].resize(2);
	}
} 

void getInput() {
	for (int i = 0	; i < ::n; ++i) {
		cin >> ::coordinates[i][0];
		cin >> ::coordinates[i][1];
	}
}

vector<int> greedyTour() {
	// initalize some variables
	vector<int> tour(::n);
	vector<bool> used(::n);
	used[0] = true;
	int best = -1;

	// run the actual algorithm
	for (int i = 1; i < ::n; ++i) {
		best = -1;
		for (int j = 0; j < ::n; ++j) {
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
