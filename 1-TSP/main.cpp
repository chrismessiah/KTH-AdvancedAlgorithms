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

#include "matrix.hpp"
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
  Matrix dMatrix(inputLength);
  for (short i = 0; i < inputLength; i++) {
    for (short j = i+1; j < inputLength; j++) {
      dMatrix.setSymmetrical(i,j, round(sqrt( ((x[i]-x[j])*(x[i]-x[j])) + ((y[i]-y[j])*(y[i]-y[j])) )));
    }
  }
  dMatrix.print();
  
  return 0;
}
