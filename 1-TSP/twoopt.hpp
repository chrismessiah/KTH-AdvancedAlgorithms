#ifndef TWOOPT
#define TWOOPT

void swap(vector<short> (*tour), int * i, int * k);

void twoopt(vector<short> (*tour), Matrix& dMatrix) {
  //create_random_tour(tour);
  // greedy(tour, dMatrix);

  long best_distance, distance;
  while (true) {
    best_distance = get_tour_cost(best_tour, dMatrix);
    for (int i = 0; i < inputLength; i++) {
      for (int k = i+1; k < inputLength; k++) {
        if (exit_time_reached(1.9)) {return;}

        swap(&tour, &i, &k);
        distance = get_tour_cost(&tour, dMatrix);
        if (distance < best_distance) {
          (*best_tour) = tour;
          best_distance = distance;
        }
      }
    }
  }
}

void swap(vector<short> (*tour), int * i, int * k) {
  int size = inputLength;
  vector<short> newTour = (*tour);

  int diff = (*k) - (*i);
  for (int l = 0; l <= diff; l++) {
    newTour[(*i)+l] = (*tour)[(*k)-l];
  }
  (*tour) = newTour;
}

#endif
