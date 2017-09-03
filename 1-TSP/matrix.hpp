#ifndef MATRIX
#define MATRIX

#include <iostream>
#include <sstream> // cast numbers to strings

class Matrix {
  public:
    Matrix(short length);
    void set(short r, short c, long value);
    void setSymmetrical(short r, short c, long value);
    long get(short r, short c);
    void print();
  private:
    long* array;
    short length;
};

Matrix::Matrix(short length) {
  this->length = length;
  array = new long[length*length];
  for (short i = 0; i < length; i++) {
    for (short j = 0; j < length; j++) {
      array[i*length + j] = 0;
    }
  }
}

long Matrix::get(short r, short c) {
  return array[length*r + c];
}

void Matrix::set(short r, short c, long value) {
  array[length*r + c] = value;
}

void Matrix::setSymmetrical(short r, short c, long value) {
  array[length*r + c] = value;
  array[length*c + r] = value;
}

void Matrix::print() {
  string out = "";
  string numString;
  stringstream ss;
  for (short i = 0; i < length; i++) {
    for (short j = 0; j < length; j++) {
      ss << get(i,j);
      numString = ss.str();
      ss.str("");
      out = out + numString + "	";
    }
    cout << out << "\n";
    out = "";
  }
}

#endif
