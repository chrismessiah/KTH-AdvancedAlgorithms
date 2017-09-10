#ifndef INPUTS
#define INPUTS

short get_test_input_length() { return 10; }
void get_test_input(vector<double> * x, vector<double> * y) {
  (*x)[0] = 95.0129;
  (*y)[0] = 61.5432;

  (*x)[1] = 23.1139;
  (*y)[1] = 79.1937;

  (*x)[2] = 60.6843;
  (*y)[2] = 92.1813;

  (*x)[3] = 48.5982;
  (*y)[3] = 73.8207;

  (*x)[4] = 89.1299;
  (*y)[4] = 17.6266;

  (*x)[5] = 76.2097;
  (*y)[5] = 40.5706;

  (*x)[6] = 45.6468;
  (*y)[6] = 93.5470;

  (*x)[7] = 1.8504;
  (*y)[7] = 91.6904;

  (*x)[8] = 82.1407;
  (*y)[8] = 41.0270;

  (*x)[9] = 44.4703;
  (*y)[9] = 89.3650;
}

// used to verify minimal spanning tree
short get_test_input_length_2() { return 5; }
void get_test_input_2(vector<double> * x, vector<double> * y) {
  (*x)[0] = 0;
  (*y)[0] = 0;

  (*x)[1] = 2;
  (*y)[1] = 0;

  (*x)[2] = 5;
  (*y)[2] = 0;

  (*x)[3] = 0;
  (*y)[3] = 6;

  (*x)[4] = 5;
  (*y)[4] = 9;
}

#endif
