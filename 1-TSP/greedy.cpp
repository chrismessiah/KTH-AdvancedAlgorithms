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

#include "distance.hpp"
using namespace std;

void greedy(vector<Point> input, vector<int> (*tour), int n);

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
//
// GreedyTour
//    tour[0] = 0
//    used[0] = true
//    for i = 1 to n-1
//       best = -1
//       for j = 0 to n-1
//          if not used[j] and (best = -1 or dist(tour[i-1],j) < dist(tour[i-1],best))
//             best = j
//       tour[i] = best
//       used[best] = true
//    return tour
