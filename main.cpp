// Travelling Salesperson 2D
// https://kth.kattis.com/problems/tsp

// compile with: g++ filename.cpp
// Run with: ./a.out

// Imports
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;
// Imports

int main() {
	cout << "Hello!\n";
	return 0;
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
