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

bool kattis = false;
short inputLength;
float final_time_limit = 1.9999; // sec. Kattis has 2 sec limit
default_random_engine rng;
chrono::high_resolution_clock::time_point startTime;

#include "matrix.hpp"
#include "test_input.hpp"
#include "helpers.hpp"
#include "greedy.hpp"
#include "nGreedy.hpp"
// #include "twoopt.hpp"
#include "natural_evolution.hpp"

void ne(vector<short> &tour, Matrix dMatrix);

int main() {
  startTime = chrono::high_resolution_clock::now();
  srand(time(NULL));
  //rng = default_random_engine {};

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

  nGreedy(tour, dMatrix, 5);
  print_tour_cost(&tour, dMatrix, "Greedy");


  ne(tour, dMatrix);

  // twoopt(&tour, dMatrix);
  // print_tour_cost(&tour, dMatrix, "2-Opt");

  // the kattis-tour outputter.
  print_tour(&tour);

  return 0;
}

void ne(vector<short> &tour, Matrix dMatrix) {
  short numberOfGenomes = 10;
  short numberOfGenerations = 10;
  double mutateRate = 0.01;
  // Create the first generation
  vector<Genome> parents;
  Genome best = Genome(tour);
  best.updateTourLength(dMatrix);
  Genome bestChildOfGeneration = best;

  // Create the first parents
  for (int i = 0; i < numberOfGenomes; i++) {
    vector<short> DNA(inputLength);
    create_random_tour(&DNA);
    Genome parent = Genome(DNA);
    parent.updateTourLength(dMatrix);
    parents.push_back(parent);
  }
  // Run through the generations
  for (int i = 0; i < numberOfGenerations; i++) {
    vector<Genome> children;
    double bestFitness = 0;
    int bestFitnessIndex = 0;
    for (int j = 0; j < numberOfGenomes; j++) {
      cout << "1" << endl;
      Genome child = makeChild(bestChildOfGeneration, parents[j], mutateRate);
      cout << "2" << endl;
      child.updateTourLength(dMatrix);
      children.push_back(child);
      if (bestFitness < child.fitness) {
        bestFitness = child.fitness;
        bestFitnessIndex = j;
      }
    }
    bestChildOfGeneration = children[bestFitnessIndex];
    if (best.fitness < bestChildOfGeneration.fitness) {
      best = bestChildOfGeneration;
    }
    parents = children;
    children.clear();
  }
  tour = best.DNA;
}
