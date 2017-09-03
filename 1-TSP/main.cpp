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
#include "natural_evolution.hpp"
typedef vector<Point> pointVector;  // Vi kan använda pointVector istället för vector<Point> för snabbare typing

// Function declaractions
void getInput(vector<Point> *points, int inputLength);
void getTerminalInput(vector<Point> *points, int inputLength);
void printResult(vector<int> tour, int inputLength);

int main() {
  bool kattis = true;
  int inputLength;
  string stringInput;
  vector<Point> points;

  if (!kattis) {

    inputLength = 10;
    vector<int> tour(inputLength);
    get_test_input(&points);  // Stores the all the points in a vector
    greedy(points, &tour, inputLength); //
    cout << "Length of the tour: " << cost(points, tour) << endl;
    printResult(tour, inputLength);

  } else {
    // Vet inte hur du fick det att funka med kattis förut
    // Compilar inte med kattis än

    inputLength = 0;

    cin >> stringInput;
    inputLength = stoi(stringInput);
    vector<int> tour(inputLength);

    getTerminalInput(&points, inputLength);
    greedy(points, &tour, inputLength);
    printResult(tour, inputLength);

  }
  return 0;
}

// Some help functions

// Har int fått getline att funka
void getInput(vector<Point> *points, int inputLength) {
  int i = 0;
  string s;
  while(true) {
    getline(cin, s);
    if (s.empty()) {break;}
    (*points).push_back(Point(s));
    i++;
  }
}

// Den här inputen funkar
void getTerminalInput(vector<Point> *points, int inputLength) {
  string Xinput;
  string Yinput;
  for (int i = 0; i < inputLength; i++) {
    cin >> Xinput;
    cin >> Yinput;
    (*points).push_back(Point(Xinput + "  " + Yinput));
  }
}

// Printing the ouput to kattis
void printResult(vector<int> tour, int inputLength) {
  for (int i = 0; i < inputLength; i++) {
    cout << tour[i] << endl;
  }
}
// End of help functions
