#ifndef TWOOPT
#define TWOOPT

void swap(vector<short> (*tour), short m, short n);
long get_2node_cost(vector<short> (*tour), Matrix& dMatrix, short m, short n);

void twoopt(vector<short> (*best_tour), Matrix& dMatrix) {
  greedy(best_tour, dMatrix);
  vector<short> tour = (*best_tour);

  long distance;
  long best_distance = get_tour_cost(best_tour, dMatrix, false);
  while (true) {
    if (exit_time_reached(1.9)) {return;}
    for (short i = 0; i < inputLength; i++) {
      for (short k = i+1; k < inputLength; k++) {
        if (exit_time_reached(1.9)) {return;}

        distance = get_2node_cost(&tour, dMatrix, i, k);
        swap(&tour, i, k);
        distance -= get_2node_cost(&tour, dMatrix, i, k);

        if (distance > 0) {
          swap(best_tour, i, k); // apply the change to our best tour
          best_distance -= distance;
        } else {
          swap(&tour, i, k);
        }
      }
    }
  }
}

void swap(vector<short> (*tour), short m, short n) {
  short tmp = (*tour)[m];
  (*tour)[m] = (*tour)[n];
  (*tour)[n] = tmp;
}

long get_2node_cost(vector<short> (*tour), Matrix& dMatrix, short m, short n) {
  long sum;
  if (m == inputLength-1) {
     sum = dMatrix.get(0, (*tour)[m]);
  } else {
     sum = dMatrix.get((*tour)[m], (*tour)[m+1]);
  }

  if (n == inputLength-1) {
     sum += dMatrix.get(0, (*tour)[n]);
  } else {
     sum += dMatrix.get((*tour)[n], (*tour)[n+1]);
  }

  if (m == 0) {
     sum += dMatrix.get(0, inputLength-1);
  } else {
     sum += dMatrix.get((*tour)[m-1], (*tour)[m]);
  }

  if (n == 0) {
     return sum + dMatrix.get(0, inputLength-1);
  } else {
     return sum + dMatrix.get((*tour)[n-1], (*tour)[n]);
  }
}

#endif
