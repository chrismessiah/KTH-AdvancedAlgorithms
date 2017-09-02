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
#include "greedy.cpp"
#include "distance.hpp"
#include "inputs.hpp"
#include "cost.cpp"
typedef vector<Point> pointVector;

int main() {
  bool kattis = false;
  int inputLength;
  string stringInput;

  if (!kattis) {
    inputLength = 10;
    vector<int> tour(inputLength);
    vector<Point> points;
    get_test_input(&points);

    greedy(points, &tour, inputLength);

    cout << cost(points, tour) << endl;

  } else {
    cin >> inputLength;
    for (short i = 0; i < inputLength; i++) {
      getline(cin, stringInput);
      // Point point(&stringInput);
      // store the point somehow here
    }
  }
  return 0;
}
