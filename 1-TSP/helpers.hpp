#ifndef HELPERS
#define HELPERS

void get_data(Matrix& dMatrix);

// gets input data and converts it to distance, stores it in matrix
void get_data(Matrix& dMatrix) {
  vector<double> x(inputLength);
  vector<double> y(inputLength);
  if (kattis) {for (short i = 0; i < inputLength; i++) { cin >> x[i] >> y[i];}}
  else {get_test_input(&x, &y);}

  for (short i = 0; i < inputLength; i++) {
    for (short j = i+1; j < inputLength; j++) {
      dMatrix.setSymmetrical(i,j, round(sqrt( ((x[i]-x[j])*(x[i]-x[j])) + ((y[i]-y[j])*(y[i]-y[j])) )));
    }
  }
}

void print_tour(vector<short> (*tour)) {
  for (short i = 0; i < inputLength; i++) {
    cout << (*tour)[i] << endl;
  }
}

void print_tour_cost(vector<short> (*tour), Matrix& dMatrix, string label) {
  if (kattis) {return;}
  short r, c;
  long sum = 0;
  for (short i = 0; i <= inputLength; i++) {
    r = (*tour)[i];
    c = (i+1 == inputLength) ? (*tour)[0] : (*tour)[i+1];
    sum += dMatrix.get(r, c);
  }
  cout << "Tour: " << label << "	Cost: " << sum << endl;
}

#endif
