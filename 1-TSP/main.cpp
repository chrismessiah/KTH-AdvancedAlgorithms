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
#include <random>
#include <algorithm>
#include <ctime>
#include <math.h>
#include <chrono>

using namespace std;

bool kattis = true;
short inputLength;
default_random_engine rng;
chrono::high_resolution_clock::time_point startTime;

#include "matrix.hpp"
#include "test_input.hpp"
#include "helpers.hpp"
#include "greedy.hpp"
#include "twoopt.hpp"

int main() {
  startTime = chrono::high_resolution_clock::now();
  srand(time(NULL));
  rng = default_random_engine {};

  if (kattis) { cin >> inputLength; }
  else { inputLength = get_test_input_length(); cout << endl << "DEBUG-MODE ACTIVE" << endl << endl;}

  Matrix dMatrix(inputLength);
  get_data(dMatrix); // convert inputs to distance matrix

  // we can print the distance matrix for debugging purposes. If kattis is true
  // this shows nothing.
  // dMatrix.print();

  vector<short> tour(inputLength);

  // create_random_tour(&tour);
  // print_tour_cost(&tour, dMatrix, "Random");
  //
  // greedy(&tour, dMatrix);
  // print_tour_cost(&tour, dMatrix, "Greedy");

  twoopt(&tour, dMatrix);
  //print_tour_cost(&tour, dMatrix, "2-Opt");

  // the kattis-tour outputter.
  print_tour(&tour);

  return 0;
}
