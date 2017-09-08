#ifndef HELPERS
#define HELPERS

void get_data();
long get_tour_cost(vector<short> (*tour));
void create_random_tour(vector<short> (*tour));
void create_tour(vector<short> (*tour));

// gets input data and converts it to distance, stores it in matrix
void get_data() {
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

void print_tour_cost(vector<short> (*tour), string label) {
  if (kattis) {return;}
  long cost = get_tour_cost(tour);
  cout << "Tour: " << label << "	Cost: " << cost << endl;
}

long get_tour_cost(vector<short> (*tour)) {
  long sum = 0;
  for (short i = 0; i < inputLength-1; i++) {
    sum += dMatrix.get((*tour)[i], (*tour)[i+1]);
  }
  sum += dMatrix.get((*tour)[inputLength-1], (*tour)[0]);
  return sum;
}

void create_tour(vector<short> (*tour)) {
  iota((*tour).begin(), (*tour).end(), 0);
}

void create_random_tour(vector<short> (*tour)) {
  create_tour(tour);
  shuffle(begin((*tour)), end((*tour)), rng);
}

bool exit_time_reached(double time_limit) {
  chrono::high_resolution_clock::time_point nowTime = chrono::high_resolution_clock::now();
  chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(nowTime - startTime);
  return (time_span.count() >= time_limit) ? true : false;
}

#endif
