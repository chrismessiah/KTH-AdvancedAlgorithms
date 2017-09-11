#ifndef TWOOPT
#define TWOOPT

void swap(vector<short> (*tour), short m, short n);
long get_2node_cost(vector<short> (*tour), Matrix& dMatrix, short m, short n);
void reverse(vector<short> (*tour), short from, short to);
long get_path_cost(vector<short> (*tour), Matrix& dMatrix, short m, short n);

void twoopt(vector<short> (*tour), Matrix& dMatrix) {
  long distance, best_distance = get_tour_cost(tour, dMatrix);
  short v1, v2, v3, v4;
  bool improve = true;
  
  while (improve) {
    improve = false;
    if (exit_time_reached()) {return;}
    for (short i = 0; i < inputLength; i++) {
      for (short k = i+1; k < inputLength; k++) {
        if (exit_time_reached()) {return;}

        // the vertices relevant for the following comparison
        v1 = (*tour)[((i-1) % inputLength)];
        v2 = (*tour)[i];
        v3 = (*tour)[k];
        v4 = (*tour)[((k+1) % inputLength)];

        // calculates the distance difference if two edges would be moved.
        // 1-2 & 3-4    ->    1-3 & 2-4   is shorter?
        distance = dMatrix.get(v1, v2) + dMatrix.get(v3, v4) - ( dMatrix.get(v1, v3) + dMatrix.get(v2, v4)  );

        if (distance > 0) {
          improve = true;
          reverse(tour, i, k);
          best_distance -= distance;
        }
      }
    }
  }
}

void reverse(vector<short> (*tour), short from, short to) {
  int limit = ((to-from) % 2 == 0) ? (to-from)/2 : (to-from-1)/2;
  for (int l = 0; l <= limit; l++) {
    swap(tour, from+l, to-l);
  }
}

void swap(vector<short> (*tour), short m, short n) {
  short tmp = (*tour)[m];
  (*tour)[m] = (*tour)[n];
  (*tour)[n] = tmp;
}

#endif
