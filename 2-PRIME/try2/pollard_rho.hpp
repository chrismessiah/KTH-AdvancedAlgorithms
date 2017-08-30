#ifndef RHO
#define RHO

void rho(mpz_class *n, mpz_class *result);

void rho(mpz_class *n, mpz_class *result) {
  if (*n == 2) {*result = 0; return;}
  if (*n % 2 == 0) {*result = 2; return;}

  // gives memory limit exeptions on kattis. We may want to try it after removing some vars
  //if (mpz_probab_prime_p((*n).get_mpz_t(), 20) >= 1) {*result = *n; return;}

  mpz_class x, y, d, diff, two;

  two = 2;
  x = 2;
  y = 2;
  d = 1;

  mpz_mod(diff.get_mpz_t(), (*n).get_mpz_t(), two.get_mpz_t());
  if (diff == 0) {*result = 2; return;}

  // limit 400k, 300k, and 200k gives same score but takes longer time so
  // make sure to keep the number low for the sake of time.
  unsigned int count = 0, limit = 200000;
  while (d == 1) {
    if (count > limit) {*result = -1; return;} // failed to factor

    x = (x*x+1);
    mpz_mod(x.get_mpz_t(), x.get_mpz_t(), (*n).get_mpz_t());

    y = (y*y+1);
    mpz_mod(y.get_mpz_t(), y.get_mpz_t(), (*n).get_mpz_t());

    y = (y*y+1);
    mpz_mod(y.get_mpz_t(), y.get_mpz_t(), (*n).get_mpz_t());

    diff = x-y;
    mpz_abs(d.get_mpz_t(), diff.get_mpz_t());

    mpz_gcd(d.get_mpz_t(), d.get_mpz_t(), (*n).get_mpz_t());
    count = count + 1;
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
