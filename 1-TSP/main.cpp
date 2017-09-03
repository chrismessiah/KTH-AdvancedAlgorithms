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

#include "helpers.hpp"
#include "test_input.hpp"

int kattis;
short inputLength;

int main() {
  kattis = false;
  if (kattis) { cin >> inputLength; }
  else {inputLength = get_test_input_length();}

  // get inputs, store in vectors
  vector<double> x(inputLength);
  vector<double> y(inputLength);
  if (kattis) {for (short i = 0; i < inputLength; i++) { cin >> x[i] >> y[i];}}
  else {get_test_input(&x, &y);}

  // convert inputs to distance matrix
  long dMatrix[inputLength*inputLength];

  // set all values to 0, for testing purposes
  if (!kattis) {for (short i = 0; i < inputLength; i++) {for (short j = 0; j < inputLength; j++) {dMatrix[inputLength*i + j] = 0;}}}

  // insert data values
  for (short i = 0; i < inputLength; i++) {
    for (short j = i+1; j < inputLength; j++) {
      dMatrix[inputLength*i + j] = dMatrix[inputLength*j + i] = round(sqrt( ((x[i]-x[j])*(x[i]-x[j])) + ((y[i]-y[j])*(y[i]-y[j])) ));
    }
  }

  print_matrix(inputLength, dMatrix);
  return 0;
}
