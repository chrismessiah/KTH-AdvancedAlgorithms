#ifndef TWOOPT
#define TWOOPT

// This 2opt is not working due to segmentation errors!

void swap(vector<short> (*tour), int * i, int * k);

void twoopt(vector<short> (*best_tour), Matrix& dMatrix) {
  create_random_tour(best_tour);
  vector<short> tour = (*best_tour);

  short improve = 0;
  long best_distance, distance;
  while (improve < 20) {
    best_distance = get_tour_cost(best_tour, dMatrix);
    for (int i = 0; i < inputLength; i++) {
      for (int k = i+1; k < inputLength; k++) {
        swap(&tour, &i, &k);
        distance = get_tour_cost(&tour, dMatrix);
        if (distance < best_distance) { // debug
          improve = 0;
          (*best_tour) = tour;
          best_distance = distance;
        }
      }
    }
    improve++;
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
