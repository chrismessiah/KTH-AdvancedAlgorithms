#ifndef TWOPOINTFIVEOPT
#define TWOPOINTFIVEOPT

/*
* The only difference between the options are which where v3 is located.
* The nodes v1, v2, v4, v5 are fixed and always connected in a manner like
* this: 1-2 & 4-5. Node 3 is either located after 2 or before 4.
* HOWEVER(!!!): If a change is applied then 2 and 4 is changed thus they must
* be fetched for each insertion type. 
*/

void twopointfiveopt(vector<short> (*tour), Matrix& dMatrix) {
  long distance;
  long best_distance = get_tour_cost(tour, dMatrix);

  bool improve = true;
  short v1, v2, v3, v4, v5;
  while (improve) {
    improve = false;
    if (exit_time_reached()) {return;}
    for (short i = 0; i < inputLength; i++) {
      for (short k = i+3; k < inputLength; k++) {
        if (exit_time_reached()) {return;}

        v1 = (*tour)[i];
        v5 = (*tour)[k];

        // ************************ INSERTION 1 ************************
        // 1-2-3 & 4-5   =>   1-3 & 4-2-5  is shorter?
        v2 = (*tour)[((i+1) % inputLength)];
        v3 = (*tour)[((i+2) % inputLength)];
        v4 = (*tour)[((k-1) % inputLength)];

        // Given: E1 = (v1, v2), E2 = (v2, v3), E3 = (v4, v5)
        // Test if shorter: E1 = (v1, v3), E2 = (v4, v2), E3 = (v2, v5)
        distance = dMatrix.get(v1, v2) + dMatrix.get(v2, v3) + dMatrix.get(v4, v5);
        distance -= dMatrix.get(v1, v3) + dMatrix.get(v4, v2) + dMatrix.get(v2, v5);

        if (distance > 0) {
          improve = true;
          /*
          * remove v2 by placing v3 in its location and keep copying nodes to a location before
          * other nodes until v4 is reached, (and copied over).
          * Then place v2 in its location
          */
          for (short l = i+2; l < k; l++) { (*tour)[((l-1) % inputLength)] = (*tour)[l]; }
          (*tour)[((k-1) % inputLength)] = v2;
          best_distance -= distance;
        }

        // ************************ INSERTION 2 ************************
        // 1-2 & 3-4-5   =>   1-4-2 & 3-5  is shorter?
        v2 = (*tour)[((i+1) % inputLength)];
        v3 = (*tour)[((k-2) % inputLength)];
        v4 = (*tour)[((k-1) % inputLength)];

        // Given: E1 = (v1, v2), E2 = (v3, v4), E3 = (v4, v5)
        // Test if shorter: E1 = (v1, v4), E2 = (v4, v2), E3 = (v3, v5)
        distance = dMatrix.get(v1, v2) + dMatrix.get(v3, v4) + dMatrix.get(v4, v5);
        distance -= dMatrix.get(v1, v4) + dMatrix.get(v4, v2) + dMatrix.get(v3, v5);

        if (distance > 0) {
          improve = true;
          /*
          * remove v4 by placing v3 in its location and keep copying nodes backwards(!)
          * other nodes until v2 is reached, (and copied over). Then place v4 in its location
          */
          for (short l = k-2; i < l; l--) {
            (*tour)[((l+1) % inputLength)] = (*tour)[l];
          }
          (*tour)[((i+1) % inputLength)] = v4;
          best_distance -= distance;
        }
      }
    }
  }
}

#endif
