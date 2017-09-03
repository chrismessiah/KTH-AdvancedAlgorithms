/*
* Lab: Factoring - https://kth.kattis.com/problems/tsp
*
* Authors
*   Christian Abdelmassih
*   Marcus Wallberg
*
* Implementation of the Greedy Tour from Kattis @ https://kth.kattis.com/problems/tsp
*
*/

#ifndef GREEDY
#define GREEDY

#include "distance.hpp"
#include "point.hpp"
using namespace std;

void greedy(vector<Point> input, vector<int> (*tour), int n) {
  vector<bool> used(n);

  short best;
  used[0] = 1;
  (*tour)[0] = 0;

  for (int i = 1; i < n; i++) {
    best = -1;
    for (int j = 0; j < n; j++) {
      if (!used[j] && ( best == -1 || distance(input[ (*tour)[i-1] ], input[j]) < distance(input[ (*tour)[i-1] ], input[best])) ) {
        best = j;
      }
    }
    (*tour)[i] = best;
    used[best] = 1;
  }
}

#endif
