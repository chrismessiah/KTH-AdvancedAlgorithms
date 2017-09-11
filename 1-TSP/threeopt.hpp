#ifndef THREEOPT
#define THREEOPT

void reverse2(vector<short> (*tour), short from, short to);

void threeopt(vector<short> (*tour), Matrix& dMatrix) {
  long distance1, distance2, distance3, distance4, base_distance, best_distance = get_tour_cost(tour, dMatrix);
  short v1, v2, v3, v4, v5, v6;
  short i1, i2, i3, i4, i5, i6;
  bool improve = true;

  while (improve) {
    improve = false;
    if (exit_time_reached()) {return;}
    for (short i = 0; i < inputLength; i++) {
      for (short j = 0; j < inputLength; j++) {
        for (short k = 0; k < inputLength; k++) {
          if (exit_time_reached()) {return;}
          if (i == j || i == k || j == k) {continue;}

          //cout << "RAN" << endl;

          i1 = i;
          i2 = ((i+1) % inputLength);
          i3 = j;
          i4 = ((j+1) % inputLength);
          i5 = k;
          i6 = ((k+1) % inputLength);

          v1 = (*tour)[i1];
          v2 = (*tour)[i2];
          v3 = (*tour)[i3];
          v4 = (*tour)[i4];
          v5 = (*tour)[i5];
          v6 = (*tour)[i6];

          base_distance = dMatrix.get(v1, v2) + dMatrix.get(v3, v4) + dMatrix.get(v5, v6);

          // 1-2 & 3-4 & 5-6    ->   1-2 & 3-4 & 5-6    is shorter?
          distance1 = base_distance - ( dMatrix.get(v3, v1) + dMatrix.get(v6, v2) + dMatrix.get(v4, v5) );
          distance2 = base_distance - ( dMatrix.get(v2, v3) + dMatrix.get(v5, v1) + dMatrix.get(v6, v4) );
          distance3 = base_distance - ( dMatrix.get(v1, v4) + dMatrix.get(v2, v5) + dMatrix.get(v3, v6) );
          distance4 = base_distance - ( dMatrix.get(v2, v5) + dMatrix.get(v3, v1) + dMatrix.get(v6, v4) );

          if (distance1 > 0) {
            // Change AB, CD, EF to DA, FB, CE.
            //cout << "ENTERED 1" << endl;
            reverse2(tour, i6, i1);
            reverse2(tour, i4, i5);
            improve = true;
            best_distance -= distance1;
          } else if (distance2 > 0) {
            // Change AB, CD, EF to BD, EA, FC.
            //cout << "ENTERED 2" << endl;
            reverse2(tour, i6, i1);
            reverse2(tour, i2, i3);
            improve = true;
            best_distance -= distance2;
          } else if (distance3 > 0) {
            // Change AB, CD, EF to AC, BE, DF.
            //cout << "ENTERED 3" << endl;
            reverse2(tour, i2, i3);
            reverse2(tour, i4, i5);
            improve = true;
            best_distance -= distance3;
          } else if (distance4 > 0) {
            // Change AB, CD, EF to BE, DA, FC.
            //cout << "ENTERED 4" << endl;
            reverse2(tour, i1, i6);
            reverse2(tour, i2, i3);
            reverse2(tour, i4, i5);
            improve = true;
            best_distance -= distance4;
          }
        }
      }
    }
  }
}

void reverse2(vector<short> (*tour), short from, short to) {
  int limit = (((from <= to ? to - from : (to + inputLength) - from) + 1)/2);
  short i = from, j = to;
  for (short n = 0; n < limit; ++n) {
      swap(tour, i, j);
      i = (i + 1) % inputLength;
      j = ((j + inputLength) - 1) % inputLength;
  }
}

#endif
