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

#include "point.hpp"
#include "distance.hpp"
#include "inputs.hpp"

int main() {
  bool kattis = false;
  short inputLength;
  string stringInput;

  if (!kattis) {
    inputLength = 10;
    vector<string> vec;
    get_test_input(&vec);
    for(vector<string>::iterator it = vec.begin(); it != vec.end(); ++it) {
      stringInput = *it;
      Point point(&stringInput);
      // store the point somehow here
    }
  } else {
    cin >> inputLength;
    for (short i = 0; i < inputLength; i++) {
      getline(cin, stringInput);
      Point point(&stringInput);
      // store the point somehow here
    }
  }
  return 0;
}
