/*
*
* This version of Greedy will chose between the n closest points and
* will chose a random point with uniform distribution probability
*
*/


#ifndef NGREEDY
#define NGREEDY

#include <stdlib.h> // rand()
#include <time.h>

void nGreedy(vector<short> &tour, Matrix dMatrix, int n) {
  vector<bool> used(inputLength);
  vector<int> nChoice;

  int selected;
  int worst;
  used[0] = 1;
  tour[0] = 0;

  for (int i = 1; i < inputLength; i++) {
    worst = -1;
    for (int j = 0; j < inputLength; j++) {
      if (!used[j] && true ) {
        if (nChoice.size() < n || dMatrix.get(tour[i-1], j) < dMatrix.get(tour[i-1], worst) ) {
          int removeThisPointValue;
          double removeThisPointIndex;

          // In case of the vector is not filled yet
          if (nChoice.size() < n) {
            nChoice.push_back(j);
          } else {
            // In case the choices are filled
            removeThisPointValue = dMatrix.get(tour[i-1], nChoice[0]);
            removeThisPointIndex = 0;
            for (int k = 1; k < nChoice.size(); k++) {
              if (removeThisPointValue > dMatrix.get(tour[i-1], nChoice[k])) {
                removeThisPointIndex = k; // check this
                removeThisPointValue = dMatrix.get(tour[i-1], nChoice[k]);
              }
            }
            nChoice[removeThisPointIndex] = j;
          }

          worst = nChoice[0];
          for (int k = 1; k < nChoice.size(); k++) {
            if (dMatrix.get(tour[i-1], nChoice[k]) > dMatrix.get(tour[i-1], worst)) {
              worst = nChoice[k];
            }
          }

        }
      }
    }
    //srand(time(NULL));
    // cout << nChoice.size() << endl;
    int selected;
    if (nChoice.size() > 0) {
      selected = floor ( rand() % nChoice.size() );
    } else {
      cout << "is 0!" << endl;
    }
    tour[i] = nChoice[selected];
    used[nChoice[selected]] = 1;
    nChoice.clear();
  }
}

#endif
