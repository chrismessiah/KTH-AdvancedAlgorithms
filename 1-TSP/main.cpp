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
#include "greedy.hpp"
#include "inputs.hpp"
typedef vector<Point> pointVector;

// Function declaractions
void getInput(vector<Point> *points, int inputLength);
void printResult(vector<int> tour, int inputLength);

int main() {
  bool kattis = false;
  int inputLength;
  string stringInput;
  vector<Point> points;

  if (!kattis) {

    inputLength = 10;
    vector<int> tour(inputLength);

    get_test_input(&points);
    greedy(points, &tour, inputLength);
    cout << "Length of the tour: " << cost(points, tour) << endl;

    printResult(tour, inputLength);

  } else {

    // Vet inte hur du fick det att funka med kattis förut
    // Men du gjorde något liknande på factorization

    cin >> stringInput;
    inputLength = stoi(stringInput);
    vector<int> tour(inputLength);

    getInput(&points, inputLength);

    greedy(points, &tour, inputLength);
    //cout << cost(points, tour) << endl;
    printResult(tour, inputLength);

  }
  return 0;
}

void getInput(vector<Point> *points, int inputLength) {
  string stringInput;
  while(true) {
    getline(cin, stringInput);
    if (stringInput.empty()) {break;}
    (*points).push_back(Point(stringInput));
  }
}

void printResult(vector<int> tour, int inputLength) {
  for (int i = 0; i < inputLength; i++) {
    cout << tour[i] << endl;
  }
}
