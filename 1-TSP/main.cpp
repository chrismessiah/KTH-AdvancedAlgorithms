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

using namespace std;

#include "distance.hpp"
#include "inputs.hpp"

int main() {
  bool kattis = false;
  short inputLength;

  if (kattis) { cin >> inputLength; }
  else {inputLength = get_test_input_length();}

  vector<double> x(inputLength);
  vector<double> y(inputLength);

  if (kattis) {for (short i = 0; i < inputLength; i++) { cin >> x[i] >> y[i];}}
  else {get_test_input(&x, &y);}

  // change this to store the distance instead in some type of datastructure
  long dist;
  for (short i = 1; i < inputLength; i++) {
    dist = distance( &(x[i]), &(x[i-1]), &(y[i]), &(x[i-1]) );
    cout << dist << "\n";
  }
  return 0;
}
