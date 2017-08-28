#ifndef GCD
#define GCD

int gcd(int u, int v);

int gcd(int u, int v) {
  int r;
  while (v != 0) {
    r = u % v;
    u = v;
    v = r;
  }
  return u;
}

#endif
