#ifndef RHO
#define RHO

/*
* this rho function is a modified copy of the C-version available on wikipedia
* since it is different from the origial algorithm I though one should test both
* and compare the results regarding speed and precision.
*/

void rho(mpz_class *n, mpz_class *result);

void rho(mpz_class *n, mpz_class *result) {
    if (*n == 2) {*result = 0; return;}
    if (*n % 2 == 0) {*result = 2; return;}

    mpz_class number, x_fixed, cycle_size, x, factor, x_temp;
  	x_fixed = 2;
  	cycle_size = 2;
  	x = 2;
  	factor = 1;

    unsigned int count = 0, limit = 100000;

  	while (factor == 1) {
  		for (unsigned long count=1;count <= cycle_size && factor <= 1;count++) {
        if (count > limit) {*result = -1; return;}
        x_temp = x*x+1;
        mpz_mod(x.get_mpz_t(), x_temp.get_mpz_t(), (*n).get_mpz_t());
  			x_temp = x-x_fixed;
  			mpz_gcd(factor.get_mpz_t(), x_temp.get_mpz_t(), (*n).get_mpz_t());
        count += 1;
  		}
  		cycle_size *= 2;
  		x_fixed = x;
  	}

  	if (factor == *n) {
    	*result = 0; // failed to factor, is already a prime?
    } else {
      *result = factor; // found prime factor!
    }
}

#endif
