#ifndef TWOOPT
#define TWOOPT

void swap(vector<short> (*tour), short m, short n);
long get_2node_cost(vector<short> (*tour), Matrix& dMatrix, short m, short n);
void reverse(vector<short> (*tour), short from, short to);
long get_path_cost(vector<short> (*tour), Matrix& dMatrix, short m, short n);

void twoopt(vector<short> (*tour), Matrix& dMatrix) {
  //create_random_tour(tour);
  greedy(tour, dMatrix);

  long distance;
  long best_distance = get_tour_cost(tour, dMatrix);

  if (!kattis) {
    cout << "Cost before 2-OPT: " << best_distance << endl;
  }

  bool improve = true;
  short vX_pre, vX, vY, vY_post;
  while (improve) {
    improve = false;
    if (exit_time_reached()) {return;}
    for (short i = 0; i < inputLength; i++) {
      for (short k = i+1; k < inputLength; k++) {
        if (exit_time_reached()) {return;}

        // the vertices relevant for the following comparison
        vX_pre = (*tour)[((i-1) % inputLength)];
        vX = (*tour)[i];
        vY = (*tour)[k];
        vY_post = (*tour)[((k+1) % inputLength)];

        // calculates the distance difference if two edges would be moved.
        distance = dMatrix.get(vX_pre, vX) + dMatrix.get(vY, vY_post) - ( dMatrix.get(vX_pre, vY) + dMatrix.get(vX, vY_post)  );

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
