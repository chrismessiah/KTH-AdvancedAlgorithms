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

int main() {
  if (kattis) { cin >> inputLength; }
  else { inputLength = get_test_input_length(); }

  Matrix dMatrix(inputLength);
  get_data(dMatrix); // convert inputs to distance matrix
  dMatrix.print();

  return 0;
}
