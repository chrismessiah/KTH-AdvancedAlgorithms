#ifndef TWOOPT
#define TWOOPT

void swap(vector<short>& tour, int i, int k);
void copyVector(vector<short>& copy, vector<short>& base);

void twoopt(vector<short>& best_tour) {
  create_tour(best_tour);
  vector<short> tour(inputLength);

  copyVector(tour, best_tour);

  short improve = 0;
  long best_distance, distance;
  //best_distance = 20;
  while (improve < 20) {
    best_distance = get_tour_cost(best_tour);
    for (int i = 0; i < inputLength; i++) {
      for (int k = i+1; k < inputLength; k++) {
        swap(tour, i, k);
        distance = get_tour_cost(tour);
        //distance = round(best_distance/2);
        // if (best_distance < 100) {
        //   return;
        // }
        if (distance < best_distance) {
          improve = 0;
          //best_tour = tour;
          copyVector(best_tour, tour);
          best_distance = distance;
        }
      }
    }
    improve++;
  }
}

void copyVector(vector<short>& copy, vector<short>& base) {
  for (short i = 0; i < inputLength; i++) {
    copy[i] = base[i];
  }
}

void swap(vector<short>& tour, int i, int k) {
  int size = inputLength;
  vector<short> newTour(tour);

  int diff = k-i;
  for (int l = 0; l <= diff; l++) {
    tour[i+l] = newTour[k-l];
  }
}

#endif
