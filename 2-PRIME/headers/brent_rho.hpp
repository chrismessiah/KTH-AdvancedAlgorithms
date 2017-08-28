#ifndef RHO
#define RHO

#include <iostream>

#include "abs.hpp"
#include "gcd.hpp"
#include "min.hpp"
#include "random.hpp"

// THIS VERSION IS NOT WORKING AND SHOULD NOT BE USED

int rho(int n);
int g_fun(int x, int c, int n);

int rho(int n) {
  if (n == 2) {return 0;}
  if (n % 2 == 0) {return 2;}

  int g = 1, r = 1, q = 1;
  int y = randInt(1, n), c = randInt(1, n), m = randInt(1, n);
  int k, ys, x;
  while (g == 1) {
    x = y;
    for (size_t i = 0; i < r; i++) {
      y = g_fun(y, c, n);
    }
    k = 0;
    while (k < r && g == 1) {
      ys = y;
      for (size_t i2 = 0; i2 < minimum(m, r-k); i2++) {
        y = g_fun(y, c, n);
        q = q * absolute(x-y) % n;
      }
      g = gcd(q, n);
      k = k + m;
    }
    r = r * 2;
  }
  if (g == n) {
    while (true) {
      ys = g_fun(ys, c, n);
      g = gcd(absolute(x-ys), n);
      if (g > 1) {
        break;
      }
    }
  }
  return g;
}

int g_fun(int x, int c, int n) {
  return ((x*x) % n + c) % n;
}

#endif
