/*
* This is a test to see if we can use natural evolution
* strategies (genetic algorithm) to solve the TSP problem.
*
* https://en.wikipedia.org/wiki/Natural_evolution_strategy
*
* Authors
*   Christian Abdelmassih
*   Marcus Wallberg
*
*/

#ifndef NATURALEVOLUTION
#define NATURALEVOLUTION

#include <stdlib.h>
#include "distance.hpp"
#include "point.hpp";

// Genom (or the child)
class Genom {
  vector<Point> points;

  public:
    int dnaLength;
    vector<int> DNA;
    double fitness;
    double tourLength;
    Genom(vector<int> inputDNA, int inputLength);
};

Genom::Genom(vector<int> inputDNA, int inputLength) {
  dnaLength = inputLength;
  DNA = inputDNA;
}

void Genom::updateTourLength(vector<Point> points, ) {
  tourLength = cost(points, DNA);
}

void Genom::updateFitness() {
  fitness = 1 / tourLength;
}
// End of the genom functions

void makeChild(Genom parent1, Genom parent2, double mutationRate) {
  vector<int> newDNA(parent1.dnaLength);
  int start = rand() % parent1.dnaLength;
  int end = rand() % parent1.dnaLength;
  sort(start, end);

  for (int i = start; i < end; i++) {
    newDNA[i] = parent1.DNA[i];
    for (int j = 0; j < parent2.DNA.size(); j++) {
      if (newDNA[i] == parent2.DNA[j]) {
        parent2.DNA.erase(parent2.DNA.begin() + j);
      }
    }
  }

  for (int i = 0; i < start; i++) {
    newDNA[i] = parent2.DNA[0];
    parent2.DNA.erase(parent2.DNA.begin());
  }

  for (int i = end; i < parent1.dnaLength; i++){
    newDNA[i] = parent2.DNA[0];
    parent2.DNA.erase(parent2.DNA.begin());
  }

}

void sort(int &a, int &b)
{
    if (a > b)
    {
        int temp = a;
    }
    a = b;
    b = temp;
}


#endif
