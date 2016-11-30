#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
using namespace std;

int rho(int N);


int main() {
  int in = 1555;
  int res;

  while (in != 1) {
    res = rho(in);
    in /= res;
    cout << res << "\n";
  }
  cout << "DONE" << "\n";
  return 0;
}

// returns num, lower_bound <= num <= upper_bound
int getRandInt(int lower_bound, int upper_bound) {
  return rand() % upper_bound + lower_bound;
}

// Not needed in actual code
int gcd(int a, int b) {
  return b == 0 ? a : gcd(b, a % b);
}

int rho(int N) {
  if (N % 2 == 0) {return 2;}
  int x,y,c,g;
  x = getRandInt(1, N-1);
  y = x;
  c = getRandInt(1, N-1);
  g = 1;
  while (g == 1) {
    x = ( (x * x) % N + c) % N;
    y = ( (y * y) % N + c) % N;
    y = ( (y * y) % N + c) % N;
    g = gcd( abs(x-y), N);
  }
  return g;
}