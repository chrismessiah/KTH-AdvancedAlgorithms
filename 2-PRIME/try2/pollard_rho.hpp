#ifndef RHO
#define RHO

void rho(mpz_class *n, mpz_class *result);

void rho(mpz_class *n, mpz_class *result) {
  if (*n == 2) {*result = 0; return;}
  if (*n % 2 == 0) {*result = 2; return;}

  mpz_class x, y, d;

  x = 2;
  y = 2;
  d = 1;

  // limit 400k, 300k, and 200k gives same score but takes longer time so
  // make sure to keep the number low for the sake of time.
  unsigned int count = 0, limit = 200000;
  while (d == 1) {
    if (count > limit) {*result = -1; return;} // failed to factor

    x = (x*x+1) % (*n);
    y = (y*y+1) % (*n);
    y = (y*y+1) % (*n);

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
