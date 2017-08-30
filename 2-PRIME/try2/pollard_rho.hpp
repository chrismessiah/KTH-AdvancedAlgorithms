#ifndef RHO
#define RHO

void rho(mpz_class *n, mpz_class *result);

void rho(mpz_class *n, mpz_class *result) {
  if (*n == 2) {*result = 0; return;}
  if (*n % 2 == 0) {*result = 2; return;}

  mpz_class x, y, d, c;

  d = 1;

  gmp_randstate_t state;
  gmp_randinit_default(state);

  mpz_urandomm(x.get_mpz_t(), state, (*n).get_mpz_t()); // [2, N]
  y = x;
  mpz_urandomm(c.get_mpz_t(), state, (*n).get_mpz_t()); // [1, N]

  // limit 400k, 300k, and 200k gives same score but takes longer time so
  // make sure to keep the number low for the sake of time.
  unsigned int count = 0, limit = 200000;
  while (d == 1) {
    if (count > limit) {*result = -1; return;} // failed to factor

    x = (x*x+c) % (*n);
    y = (y*y+c) % (*n);
    y = (y*y+c) % (*n);

    d = x-y;
    mpz_abs(d.get_mpz_t(), d.get_mpz_t());
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
