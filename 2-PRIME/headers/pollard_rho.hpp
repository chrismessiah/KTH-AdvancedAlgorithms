#ifndef RHO
#define RHO

#include "gcd.hpp"

int rho(int n);

int rho(int n) {
  if (n == 2) {return 0;}
  if (n % 2 == 0) {return 2;}
  int x = 2, y = 2, d = 1;
  int diff;
  while (d == 1) {
    x = (x*x+1) % n;

    y = (y*y+1) % n;
    y = (y*y+1) % n;

    diff = x-y;
    d = (diff >= 0) ? diff : diff * (-1); // absolute

    d = gcd(d, n); // use the gmp mpz_gcd function here
  }
  if (d == n) {
    return 0;
  } else {
    return d;
  }
}

#endif
