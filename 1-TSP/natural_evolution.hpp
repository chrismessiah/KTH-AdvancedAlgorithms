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

// Genome (or the child)
class Genome {
  public:
    int dnaLength;
    vector<short> DNA;
    double fitness;
    double tourLength;
    Genome(vector<short> inputDNA);
    Genome(short inputLength);

    // Functions
    void updateTourLength(Matrix& dMatrix);
    void updateFitness();
    void mutate(double mutationRate);
    void swap(short &a, short &b);
};

Genome::Genome(short inputLength) {
  vector<short> inputDNA(inputLength);
  dnaLength = inputDNA.size();
  DNA = inputDNA;
  create_random_tour(&DNA);
}

Genome::Genome(vector<short> inputDNA) {
  dnaLength = inputDNA.size();
  DNA = inputDNA;
}

void Genome::updateTourLength(Matrix& dMatrix) {
  tourLength = get_tour_cost(&DNA, dMatrix);
  fitness = 1 / tourLength;
}

void Genome::updateFitness() {
  fitness = 1 / tourLength;
}

// Swaps points in the DNA
void Genome::mutate(double mutationRate) {
  for (int i = 0; i < dnaLength; i++) {
    if ( (double) rand() / (RAND_MAX) < mutationRate ) {
      short switchToIndex = rand() % dnaLength;
      short temp = DNA[i];
      DNA[i] = DNA[switchToIndex];
      DNA[switchToIndex] = temp;
    }
  }
}
// End of the Genome functions

// This is what we call a crossover
Genome makeChild(Genome parent1, Genome parent2, double mutationRate) {
  short length = parent1.dnaLength;
  vector<short> newDNA(length);
  vector<short> tempDNA = parent2.DNA;
  short start = rand() % length;   // DNA start from parent1
  short end = rand() % length;     // DNA end from parent 2
  swap(start, end);

  // Adding the dna from one parent
  for (int i = start; i < end; i++) {
    newDNA[i] = parent1.DNA[i];
    for (int j = 0; j < tempDNA.size(); j++) {
      if (newDNA[i] == tempDNA[j]) {
        tempDNA.erase(tempDNA.begin() + j);
        j--;
      }
    }
  }

  for (int i = 0; i < start; i++) {
    newDNA[i] = tempDNA[0];
    tempDNA.erase(tempDNA.begin());
  }

  for (int i = end; i < newDNA.size(); i++){
    newDNA[i] = tempDNA[0];
    tempDNA.erase(tempDNA.begin());
  }

  Genome child = Genome(newDNA);
  child.mutate(mutationRate);

  return child;
}

void swap(short &a, short &b) {
  short temp;
  if (a > b) {
    temp = a;
  }
  a = b;
  b = temp;
}

#endif
