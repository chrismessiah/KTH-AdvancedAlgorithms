#ifndef HELPERS
#define HELPERS

#include <sstream> // cast numbers to strings

void print_matrix(short inputLength, long *A);

void print_matrix(short inputLength, long *A) {
  string out = "";
  string numString;
  stringstream ss;
  for (short i = 0; i < inputLength; i++) {
    for (short j = 0; j < inputLength; j++) {
      ss << A[inputLength*i + j];
      numString = ss.str();
      ss.str("");
      out = out + numString + "	";
    }
    cout << out << "\n";
    out = "";
  }
}

#endif
