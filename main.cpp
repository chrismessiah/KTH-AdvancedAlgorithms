// Travelling Salesperson 2D
// https://kth.kattis.com/problems/tsp

// Authors 
// Christian Abdelmassih
// Marcus Wallberg


// DOCUMENTATION
// Possible algorithms to use
//      1. Nearest neighbour/Greedy
//      2. Clarke-Wright heuristic
//      3. K-opt (2 in our case)

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
vector<vector<double> > coordinates;
clock_t start;
vector<int> tour;

// function declaractions
void getInput();
bool wiredCoinFlip(double temp, double a, double b);
double dist(int a, int b);
void greedyTour();
void twoOptTour();
void printTour();
double calculateTotalTourCost();
void getRandomTour();
int getRandInt(int upperBound);
void loadTestValues();
void nodeSwap(int m, int n);
double calculateMultipleNodeCost(int m, int n);
double calculateNodeRelativeCost(int m);
double getRunTime();
void printRunTime();
void resetTimer();
void twoOptTourTimer();
void simulatedAnnealing();

int main() {
	srand(time(NULL));
	resetTimer();
	getInput();

	if (!::kattis) {
		
		cout << "\nTour 1: \n";
		greedyTour();
		printRunTime();
		cout << "\nCost for tour 1 is: " << calculateTotalTourCost() << "\n";
		//printTour();

		cout << "\nTour 2: \n";
		twoOptTour();
		printRunTime();
		cout << "\nCost for tour 2 is: " << calculateTotalTourCost() << "\n";
		//printTour();

		cout << "\nTour 3: \n";
		simulatedAnnealing();
		printRunTime();
		cout << "\nCost for tour 3 is: " << calculateTotalTourCost() << "\n";
		//printTour();

	} else {
		twoOptTour();
		//twoOptTourTimer();
		//greedyTour();
		printTour();
	}
	return 0;
}

void resetTimer() {
	::start = clock();
}

void printRunTime() {
	cout << "Current runtime: " << getRunTime() << "\n";
}

// returns time in seconds
double getRunTime() {
	return(( clock() - ::start ) / (double) CLOCKS_PER_SEC);
}

void printTour() {
	for (int i = 0; i < ::n; ++i) {
		cout << ::tour[i] << "\n";
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
	for (int i = 0  ; i < ::n; ++i) {
		cin >> ::coordinates[i][0];
		cin >> ::coordinates[i][1];
	}
}

bool wiredCoinFlip(double temp, double a, double b) {
	double ex = exp( - ( b-a )/temp );
	if (getRandInt(2) < ex){
		return true;
	 }
	 return false;
}

void simulatedAnnealing() {
	greedyTour();
	//getRandomTour();
	vector<int> bestTour;
	double currentCost = calculateTotalTourCost();
	double lowestCost = currentCost;
	double swapResultCost;
	double temp = 40;
	double tempReduction = 0.5;
	int thresh = 20;
	if (thresh > ::n) {thresh = ::n;}
	int randomIndex;

	for (int i = 0; i < thresh; ++i) {
		randomIndex = getRandInt(::n-1);
		swapResultCost = calculateMultipleNodeCost(i,randomIndex);
		nodeSwap(i, randomIndex);
		swapResultCost -= calculateMultipleNodeCost(i,randomIndex);
		nodeSwap(i, randomIndex);
		
		if (swapResultCost > 0) { // found a shorter path!
			nodeSwap(i, randomIndex);
			currentCost -= swapResultCost;
			if (currentCost < lowestCost) {
				lowestCost = currentCost;
				bestTour = ::tour;
			}
		} else if(wiredCoinFlip(temp, currentCost, currentCost-swapResultCost) ) {
			nodeSwap(i, randomIndex);
			currentCost -= swapResultCost;
		} 
		temp *= tempReduction;
	}
	::tour = bestTour;
}

// experimetal with time
void twoOptTourTimer() {
	//getRandomTour();
	greedyTour();
	double bestDistance = calculateTotalTourCost();
	double swapResultCost;
	
	while (true) {
		for (int i = 0; i < ::n-1; i++) { // loop through all nodes except last 
			for (int j = i+1; j < ::n; j++) { // loop through all nodes after node tour[i]
				swapResultCost = calculateMultipleNodeCost(i,j);
				nodeSwap(i, j);
				swapResultCost -= calculateMultipleNodeCost(i,j);
				nodeSwap(i, j);

				if (swapResultCost > 0) { // found a shorter path!
					nodeSwap(i, j);
					bestDistance -= swapResultCost;
				}
				if (getRunTime() > 0.037) {return;} // 2/51=0.0392156863
			}
		}
	}
}


// performs all possible swaps!
void twoOptTour() {
	int thresh = 20;

	//getRandomTour();
	greedyTour();
	double bestDistance = calculateTotalTourCost();
	double swapResultCost;
	
	int count = 0;
	while (count < thresh) {

		for (int i = 0; i < ::n-1; i++) { // loop through all nodes except last 
			for (int j = i+1; j < ::n; j++) { // loop through all nodes after node tour[i]
				swapResultCost = calculateMultipleNodeCost(i,j);
				nodeSwap(i, j);
				swapResultCost -= calculateMultipleNodeCost(i,j);
				nodeSwap(i, j);

				if (swapResultCost > 0) { // found a shorter path!
					count = 0;
					nodeSwap(i, j);
					bestDistance -= swapResultCost;
					//break; // some 2-Opt algorithms use break here!
				}
			}
		}
		count++;
	}
}

// Swaps nodes at index m and n in tour vector
void nodeSwap(int m, int n) {
	int temp = ::tour[m];
	::tour[m] = ::tour[n];
	::tour[n] = temp;
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
void getRandomTour() {
	::tour.resize(::n);
	for (int i = 0; i < ::n; ++i) {
		::tour[i] = i;
	}

	srand(time(NULL)); // make random more random by having seed time-dependent
	// random_shuffle(&tour[0], &tour[::n-1]); // does not support custom seeds unless overloaded, skip for now.

	// manual shuffle
	for (int i=0; i< ::n; i++) {
		int r = getRandInt(::n);
		int temp = ::tour[i];
		::tour[i] = ::tour[r];
		::tour[r] = temp;
	}
}

int getRandInt(int upperBound) {
	return rand() % upperBound;
}

// calculates the cost by going through the entire tour
double calculateTotalTourCost() {
	double cost = 0.0;
	for (int i = 1; i < ::n; ++i) {
		cost += dist(::tour[i-1], ::tour[i]);
	}
	cost += dist(::tour[::n-1], ::tour[0]);
	return cost;
}

// runs calculateNodeRelativeCost for two nodes
double calculateMultipleNodeCost(int m, int n) {
	double cost = 0.0;
	cost += calculateNodeRelativeCost(m);
	cost += calculateNodeRelativeCost(n);
	return cost;
}

// calculates cost for edges going into and out of node tour[m]
double calculateNodeRelativeCost(int m) {
	double cost = 0.0;
	int before = m-1;
	int after = m+1;

	if (m == 0) {
		before = ::n-1;
	} else if (m == ::n-1) {
		after = 0;
	}

	cost += dist(::tour[before], ::tour[m]);
	cost += dist(::tour[m], ::tour[after]);
	return cost;
}

void greedyTour() {
	// initalize some variables
	::tour.resize(::n);
	vector<bool> used(::n);
	used[0] = true;
	int best = -1;

	// run the actual algorithm
	for (int i = 1; i < ::n; ++i) {
		best = -1;
		for (int j = 0; j < ::n; ++j) {
			if (!used[j] && (best == -1 || dist(::tour[i-1],j) < dist(::tour[i-1],best) ) ) {
				best = j;
			}
		}
		::tour[i] = best;
		used[best] = true;
	}
}

double dist(int a, int b) {
	float x = ::coordinates[a][0] - ::coordinates[b][0];
	float y = ::coordinates[a][1] - ::coordinates[b][1];
	return sqrt(pow(x,2) + pow(y,2));
}