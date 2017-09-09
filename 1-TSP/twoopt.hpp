#ifndef TWOOPT
#define TWOOPT

void swap(vector<short> (*tour), short m, short n);
long get_2node_cost(vector<short> (*tour), Matrix& dMatrix, short m, short n);
void reverse(vector<short> (*tour), short from, short to);
long get_path_cost(vector<short> (*tour), Matrix& dMatrix, short m, short n);

void twoopt(vector<short> (*tour), Matrix& dMatrix) {
  //greedy(tour, dMatrix);
  create_random_tour(tour);

  // vector<short> tour = (*tour);

  long distance;
  long best_distance = get_tour_cost(tour, dMatrix, false);

  if (!kattis) {
    cout << "Cost before 2-OPT: " << best_distance << endl;
  }

  bool improve = true;
  short r,c;
  while (improve) {
    improve = false;
    GOTO_WHILE:
      if (exit_time_reached()) {return;}
      for (short i = 0; i < inputLength-1; i++) {
        for (short k = i+1; k < inputLength; k++) {
          if (exit_time_reached()) {return;}

          r = (i-1) % inputLength;
          c = (k+1) % inputLength;

          // calculates the distance difference if two edges would be moved.
          distance = dMatrix.get((*tour)[r], (*tour)[i]) + dMatrix.get((*tour)[k], (*tour)[c]) - ( dMatrix.get((*tour)[r], (*tour)[k]) + dMatrix.get((*tour)[i], (*tour)[c])  );

          if (distance > 0) {
            improve = true;
            reverse(tour, i, k);
            best_distance -= distance;
            goto GOTO_WHILE;
          }
        }
      }
  }
}

void reverse(vector<short> (*tour), short from, short to) {
  int limit = ((to-from) % 2 == 0) ? (to-from)/2  : (to-from-1)/2;
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
