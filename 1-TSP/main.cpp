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

  create_random_tour(&tour);
  // print_tour_cost(&tour, dMatrix, "Random");

  // nGreedy(tour, dMatrix, 3);
  //greedy(&tour, dMatrix);
  print_tour_cost(&tour, dMatrix, "Greedy");


  ne(tour, dMatrix);
  print_tour_cost(&tour, dMatrix, "NE");

  // twoopt(&tour, dMatrix);
  // print_tour_cost(&tour, dMatrix, "2-Opt");

  // the kattis-tour outputter.
  print_tour(&tour);

  return 0;
}

void ne(vector<short> &tour, Matrix dMatrix) {
  short numberOfGenomes = 50;
  short numberOfGenerations = 110;
  double mutationRate = 0.1;
  // Create the first generation
  vector<Genome> parents;
  Genome best = Genome(tour);
  best.updateTourLength(dMatrix);
  best.fitness -= 1;
  Genome bestChildOfGeneration = best;

  // Create the first parents
  for (int i = 0; i < numberOfGenomes; i++) {
    // vector<short> DNA(inputLength);
    // create_random_tour(&DNA);
    Genome parent = Genome(tour);
    parent.updateTourLength(dMatrix);
    parents.push_back(parent);
  }
  normalizeFitness(parents);
  // Run through the generations
  for (int i = 0; i < numberOfGenerations; i++) {
    vector<Genome> children;
    double bestFitness = 0;
    int bestFitnessIndex = 0;

    for (int j = 0; j < numberOfGenomes; j++) {

      short parent1 = selectChild(parents, -1);
      short parent2 = selectChild(parents, parent1);
      // Genome child = makeChild(bestChildOfGeneration, parents[j], mutationRate);
      Genome child = makeChild(parents[parent1], parents[parent2], mutationRate);
      child.updateTourLength(dMatrix);
      children.push_back(child);
      normalizeFitness(children);
      if (bestFitness < child.fitness) {
        bestFitness = child.fitness;
        bestFitnessIndex = j;
      }
    }
    bestChildOfGeneration = children[bestFitnessIndex];
    if (best.fitness < bestChildOfGeneration.fitness) {
      best = bestChildOfGeneration;
      //cout << "bestFitness" << best.fitness << endl;
    }
    parents = children;
    children.clear();
  }
  tour = best.DNA;
}
