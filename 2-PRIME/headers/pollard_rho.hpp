#ifndef RHO
#define RHO

#include "abs.hpp"
#include "gcd.hpp"

int rho(int n);
int g(int x, int n);

int rho(int n) {
  if (n == 2) {return 0;}
  if (n % 2 == 0) {return 2;}
  int x = 2, y = 2, d = 1;
  while (d == 1) {
    x = g(x, n);
    y = g(y, n);
    y = g(y, n);
    d = gcd(absolute(x-y), n);
  }
  if (d == n) {
    return 0;
  } else {
    return d;
  }
}

int g(int x, int n) {
  return (x*x+1) % n;
}

#endif
