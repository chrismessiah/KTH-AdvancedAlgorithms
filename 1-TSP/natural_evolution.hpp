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
    // Genome(short inputLength);

    // Functions
    void updateTourLength(Matrix& dMatrix);
    void updateFitness();
    void mutate(double mutationRate);
    void swap(short &a, short &b);
};

// Genome::Genome(short inputLength) {
//   vector<short> inputDNA(inputLength);
//   dnaLength = inputDNA.size();
//   DNA = inputDNA;
//   create_random_tour(&DNA);
// }

Genome::Genome(vector<short> inputDNA) {
  dnaLength = inputDNA.size();
  DNA = inputDNA;
}

void Genome::updateTourLength(Matrix& dMatrix) {
  tourLength = get_tour_cost(&DNA, dMatrix);
  updateFitness();
}

void Genome::updateFitness() {
  fitness = 1 / tourLength + 1;
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

// Genome makeChild(Genome parent1, Genome parent2, double mutationRate) {
//   vector<short> childDNA;
//   childDNA.insert(childDNA.begin(), parent1.DNA.begin(), parent1.DNA.end());
//   Genome child = Genome(childDNA);
//   child.mutate(mutationRate);
//
//   return child;
// }

Genome makeChild(Genome parent1, Genome parent2, double mutationRate) {
  short length = parent1.dnaLength;
  vector<short> parent1PartDNA;
  vector<short> parent2PartDNA;
  vector<short> newDNA;
  short start = rand() % length;   // DNA start from parent1
  short end = rand() % length;     // DNA end from parent 2
  if (start > end)
    std::swap(start, end);

  vector<short> childDNA(length);
  vector<short> parent1sub(end - start);
  vector<short> parent2sub(length - (end - start));

  // Getting all the DNA from parent1
  for (int i = 0; i < parent1sub.size(); i++) {
    parent1sub[i] = parent1.DNA[start + i];
  }

  // Getting the DNA from parent2 that is not in parent1
  int p2idx = 0;
  for (int i = 0; i < length; i++) {
    bool exists = false;
    for (int j = 0; j < parent1sub.size(); j++) {
      if (parent2.DNA[i] == parent1sub[j]) {
        exists = true;
      }
    }
    if (!exists) {
      parent2sub[p2idx] = parent2.DNA[i];
      p2idx++;
    }
  }

  p2idx = 0;
  int p1idx = 0;
  for (int i = 0; i < length; i++) {
    if (i < start || i >= end) {
      childDNA[i] = parent2sub[p2idx];
      p2idx++;
    } else {
      childDNA[i] = parent1sub[p1idx];
      p1idx++;
    }
  }

  Genome child = Genome(childDNA);
  child.mutate(mutationRate);

  return child;
}
// End of the Genome functions

double totalFitness(vector<Genome> genomes) {
  double sum = 0;
  for (int i = 0; i < genomes.size(); i++) {
    sum += genomes[i].fitness;
  }
  return sum;
}

void normalizeFitness(vector<Genome> &genomes) {
  double totFitness = totalFitness(genomes);
  for (int i = 0; i < genomes.size(); i++) {
    genomes[i].fitness /= totFitness;
  }
}

short selectChild(vector<Genome> genomes, short selected) {
  double r = ((double) rand() / (RAND_MAX));
  double probSum = 0;
  for (int i = 0; i < genomes.size(); i++) {
    probSum += genomes[i].fitness;
    if (probSum < r) {
      // if (selected != i) {
      return i;
      // }
    }
  }
  return genomes.size() - 1;
}

#endif
