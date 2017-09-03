#ifndef GREEDY
#define GREEDY

void greedy(vector<short> (*tour), Matrix& input) {
  vector<bool> used(inputLength);

  short best;
  used[0] = 1;
  (*tour)[0] = 0;

  for (int i = 1; i < inputLength; i++) {
    best = -1;
    for (int j = 0; j < inputLength; j++) {
      if (!used[j] && ( best == -1 || input.get((*tour)[i-1], j) < input.get((*tour)[i-1], best)) ) {
        best = j;
      }
    }
    (*tour)[i] = best;
    used[best] = 1;
  }
}

#endif
