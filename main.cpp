// Travelling Salesperson 2D
// https://kth.kattis.com/problems/tsp

// Authors 
// Christian Abdelmassih
// Marcus Wallberg

// compile with: g++ filename.cpp
// Run with: ./a.out

// Imports
#include <math.h>
#include <vector>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cstdlib>
#include <ctime>
using namespace std;

// global variables
int n;
bool kattis = false;
vector<vector<float> > coordinates;

// function declaractions
void getInput();
float dist(int a, int b);
vector<int> greedyTour();
//vector<int> algorithm1();
void printTour(vector<int> output);
float calculateTourCost(vector<int> tour);
vector<int> getRandomTour();
void loadTestValues();
vector<int> nodeSwap(int m, int n, vector<int> tour);





int main() {
	getInput();

	vector<int> tour = greedyTour();
	cout << "before: \n";
	printTour(tour);
	cout << "\nafter: \n";
	tour = nodeSwap(1,2,tour);
	printTour(tour);

	//vector<int> randomTour = getRandomTour();
	//vector<int> tour = algorithm1();

	if (!::kattis) {
		cout << "\nCost for tour is: " << calculateTourCost(tour) << "\nTour path is: \n";
	}

	// printTour(tour);
	// cout << "\n";
	// printTour(randomTour);
	return 0;
}

void printTour(vector<int> output) {
	for (int i = 0; i < ::n; ++i) {
		cout << output[i] << "\n";
	}
}

void getInput() {
	if (!::kattis) {
		loadTestValues();
		return;
	}

	cin >> ::n;
	
	// set size of vector
	::coordinates.resize(::n);
	for (int i = 0; i < ::n; ++i) {
		::coordinates[i].resize(2);
	}

	// get rest of input
	for (int i = 0	; i < ::n; ++i) {
		cin >> ::coordinates[i][0];
		cin >> ::coordinates[i][1];
	}
}



// Swaps nodes at index m and n in tour vector
vector<int> nodeSwap(int m, int n, vector<int> tour) {
	int temp = tour[m];
	tour[m] = tour[n];
	tour[n] = temp;
	return tour;
}

void loadTestValues() {
	::n = 10;

	::coordinates.resize(::n);
	for (int i = 0; i < ::n; ++i) {
		::coordinates[i].resize(2);
	}

	::coordinates[0][0] = 95.0129;
	::coordinates[0][1] = 61.5432;

	::coordinates[1][0] = 23.1139;
	::coordinates[1][1] = 79.1937;

	::coordinates[2][0] = 60.6843;
	::coordinates[2][1] = 92.1813;

	::coordinates[3][0] = 48.5982;
 	::coordinates[3][1] = 73.8207;

	::coordinates[4][0] = 89.1299;
 	::coordinates[4][1] = 17.6266;

	::coordinates[5][0] = 76.2097;
 	::coordinates[5][1] = 40.5706;

	::coordinates[6][0] = 45.6468;
 	::coordinates[6][1] = 93.5470;

	::coordinates[7][0] = 1.8504;
 	::coordinates[7][1] = 91.6904;

	::coordinates[8][0] = 82.1407;
 	::coordinates[8][1] = 41.0270;

	::coordinates[9][0] = 44.4703;
 	::coordinates[9][1] = 89.3650;
}

// REMEMBER 
// SHUFFLE uses tour as SEED unless explicitly defined !!!!!!!!!!!
vector<int> getRandomTour() {
	vector<int> tour(::n);
	for (int i = 0; i < ::n; ++i) {
		tour[i] = i;
	}

	srand(time(NULL)); // make random more random by having seed time-dependent
	// random_shuffle(&tour[0], &tour[::n-1]); // does not support custom seeds unless overloaded, skip for now.

	// manual shuffle
	for (int i=0; i< ::n; i++) {
        int r = rand() % ::n;
        int temp = tour[i];
        tour[i] = tour[r];
        tour[r] = temp;
    }

	return tour;
}

float calculateTourCost(vector<int> tour) {
	float cost = 0.0;
	for (int i = 1; i < ::n; ++i) {
		cost += dist(tour[i-1], tour[i]);
	}
	cost += dist(tour[::n-1], tour[0]);
	return cost;
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
    return sqrt(pow(x,2) + pow(y,2));
}
