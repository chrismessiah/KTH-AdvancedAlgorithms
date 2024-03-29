#ifndef RHO
#define RHO

void rho(mpz_class *n, mpz_class *result, gmp_randstate_t *state);

void rho(mpz_class *n, mpz_class *result, gmp_randstate_t *state) {
  if (*n == 2) {*result = 0; return;}
  if (*n % 2 == 0) {*result = 2; return;}

  mpz_class x, y, d, c;

  d = 1;

  mpz_urandomm(x.get_mpz_t(), *state, (*n).get_mpz_t()); // [2, N]
  y = x;
  mpz_urandomm(c.get_mpz_t(), *state, (*n).get_mpz_t()); // [1, N]

  unsigned int count = 0, limit = 850000;
  while (d == 1) {
    if (count > limit) {*result = -1; return;} // failed to factor

    x = (x*x+c) % (*n);
    y = (y*y+c) % (*n);
    y = (y*y+c) % (*n);

    d = abs(x-y);
    mpz_gcd(d.get_mpz_t(), d.get_mpz_t(), (*n).get_mpz_t());
    count += 1;
  }
  if (d == *n) {
    *result = 0;
    return;
  } else {
    *result = d;
    return;
  }
}

#endif
