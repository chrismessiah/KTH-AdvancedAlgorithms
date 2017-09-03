/*
* Lab: Factoring - https://kth.kattis.com/problems/tsp
*
* Authors
*   Christian Abdelmassih
*   Marcus Wallberg
*
* Compile with   g++ main.cpp -std=c++11
*/

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

bool kattis = false;
short inputLength;

#include "matrix.hpp"
#include "test_input.hpp"
#include "helpers.hpp"
#include "greedy.hpp"

int main() {
  if (kattis) { cin >> inputLength; }
  else { inputLength = get_test_input_length(); cout << endl << "DEBUG-MODE ACTIVE" << endl << endl;}

  Matrix dMatrix(inputLength);
  get_data(dMatrix); // convert inputs to distance matrix

  // we can print the distance matrix for debugging purposes. If kattis is true
  // this shows nothing.
  dMatrix.print();

  vector<short> tour(inputLength);
  greedy(&tour, dMatrix);

  // prints the total tour cost. To be used for debugging purposes
  print_tour_cost(&tour, dMatrix, "Greedy");

  // the kattis-tour outputter.
  print_tour(&tour);

  return 0;
}
