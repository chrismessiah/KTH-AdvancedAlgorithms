// Travelling Salesperson 2D
// https://kth.kattis.com/problems/tsp

// Authors 
// Christian Abdelmassih
// Marcus Wallberg

// compile with: g++ *.cpp
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
clock_t start;

// function declaractions
void getInput();
float dist(int a, int b);
vector<int> greedyTour();
vector<int> twoOptTour();
void printTour(vector<int> output);
float calculateTotalTourCost(vector<int> tour);
vector<int> getRandomTour();
void loadTestValues();
vector<int> nodeSwap(int m, int n, vector<int> tour);
float calculateMultipleNodeCost(int m, int n, vector<int> tour);
float calculateNodeRelativeCost(int m, vector<int> tour);
double getRunTime();
void printRunTime();
void resetTimer();

int main() {
	resetTimer();
	getInput();

	if (!::kattis) {
		vector<int> tour = greedyTour();
		printRunTime();
		vector<int> tour2 = twoOptTour();
		printRunTime();

		cout << "\nCost for tour 1 is: " << calculateTotalTourCost(tour) << "\n";
		cout << "\nCost for tour 2 is: " << calculateTotalTourCost(tour2) << "\n";

		cout << "\nTour 1: \n";
		printTour(tour);
		cout << "\nTour 2: \n";
		printTour(tour2);
	} else {
		vector<int> tour = twoOptTour();
		//vector<int> tour = greedyTour();
		printTour(tour);
	}
	return 0;
}

void resetTimer() {
	::start = clock();
}

void printRunTime() {
	cout << "Current runtime: " << getRunTime() << "\n";
}

double getRunTime() {
	return(( clock() - ::start ) / (double) CLOCKS_PER_SEC);
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



vector<int> twoOptTour() {
	// The theshhold of how much the algorithm will search,
	// we may want to use time as upper bound instead
	int thresh = 10;

	vector<int> tour = getRandomTour();
	vector<int> tempTour;
 	double bestDistance = calculateTotalTourCost(tour);
 	double swapResultCost;
    
    int count = 0;
    while (count < thresh) {

        for (int i = 0; i < ::n-1; i++) { // loop through all nodes except last 
            for (int j = i+1; j < ::n; j++) { // loop through all nodes after node tour[i]
            	tempTour = nodeSwap(i, j, tour);
                swapResultCost = calculateMultipleNodeCost(i,j,tour);
                swapResultCost -= calculateMultipleNodeCost(i,j,tempTour);
 
                if (swapResultCost > 0) { // found a shorter path!
                    count = 0;
                    tour = tempTour;
                    bestDistance -= swapResultCost;
                }
            }
        }
        count++;
    }
    return tour;
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

// calculates the cost by going through the entire tour
float calculateTotalTourCost(vector<int> tour) {
	float cost = 0.0;
	for (int i = 1; i < ::n; ++i) {
		cost += dist(tour[i-1], tour[i]);
	}
	cost += dist(tour[::n-1], tour[0]);
	return cost;
}

// runs calculateNodeRelativeCost for two nodes
float calculateMultipleNodeCost(int m, int n, vector<int> tour) {
	float cost = 0.0;
	cost += calculateNodeRelativeCost(m, tour);
	cost += calculateNodeRelativeCost(n, tour);
	return cost;
}

// calculates cost for edges going into and out of node tour[m]
float calculateNodeRelativeCost(int m, vector<int> tour) {
	float cost = 0.0;
	int before = m-1;
	int after = m+1;

	if (m == 0) {
		before = ::n-1;
	} else if (m == ::n-1) {
		after = 0;
	}

	cost += dist(tour[before], tour[m]);
	cost += dist(tour[m], tour[after]);
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
