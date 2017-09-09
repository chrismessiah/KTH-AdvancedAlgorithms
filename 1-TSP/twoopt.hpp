#ifndef TWOOPT
#define TWOOPT

void swap(vector<short> (*tour), short m, short n);
long get_2node_cost(vector<short> (*tour), Matrix& dMatrix, short m, short n);
void reverse(vector<short> (*tour), short from, short to);

void twoopt(vector<short> (*best_tour), Matrix& dMatrix) {
  //greedy(best_tour, dMatrix);
  create_random_tour(best_tour);

  vector<short> tour = (*best_tour);

  long distance;
  long best_distance = get_tour_cost(best_tour, dMatrix, false);

  if (!kattis) {
    cout << "Cost before 2-OPT: " << best_distance << endl;
  }

  bool improve = true;
  while (improve) {
    improve = false;
    GOTO_WHILE:
      if (exit_time_reached(1.9)) {return;}
      for (short i = 0; i < inputLength; i++) {
        for (short k = i+1; k < inputLength; k++) {
          if (exit_time_reached(1.9)) {return;}

          distance = get_2node_cost(&tour, dMatrix, i, k);
          reverse(&tour, i, k);
          distance -= get_2node_cost(&tour, dMatrix, i, k);

          if (distance > 0) {
            improve = true;
            reverse(best_tour, i, k); // apply the change to our best tour
            best_distance -= distance;
            goto GOTO_WHILE;
          } else {
            reverse(&tour, i, k);
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

long get_2node_cost(vector<short> (*tour), Matrix& dMatrix, short m, short n) {
  long sum;

  if (m == inputLength-1) {
     sum = dMatrix.get((*tour)[m], 0);
  } else {
     sum = dMatrix.get((*tour)[m], (*tour)[m+1]);
  }

  if (n == inputLength-1) {
     sum += dMatrix.get((*tour)[n], 0);
  } else {
     sum += dMatrix.get((*tour)[n], (*tour)[n+1]);
  }

  if (m == 0) {
     sum += dMatrix.get((*tour)[m], (*tour)[inputLength-1]);
  } else {
     sum += dMatrix.get((*tour)[m], (*tour)[m-1]);
  }

  if (n == 0) {
     sum += dMatrix.get((*tour)[n], (*tour)[inputLength-1]);
  } else {
     sum += dMatrix.get((*tour)[n], (*tour)[n-1]);
  }
  return sum;
}

#endif
