#ifndef RHO
#define RHO

/*
*
* This function is not working as it should!!!!!
*
*/


void rho(mpz_class *n, mpz_class *result);

void rho(mpz_class *n, mpz_class *result) {
	if (*n == 2) {*result = 0; return;}
	if (*n % 2 == 0) {*result = 2; return;}

	mpz_class y,c,m,g,q,ys, min_var, x, r, k, temp;

  // gmp_randstate_t state;
  // gmp_randinit_default(state);

  // mpz_urandomm(y.get_mpz_t(), state, (*n).get_mpz_t());
  // mpz_urandomm(c.get_mpz_t(), state, (*n).get_mpz_t());
  // mpz_urandomm(m.get_mpz_t(), state, (*n).get_mpz_t());

	y = 2;
	m = 2;
	c = 1; // constant in added in modulus

	g = 1;
	r = 1;
	q = 1;

	unsigned long count = 0;
	unsigned long limit = 100000;

	while (g == 1) {
		x = y;
		for (int i = 0; i < r; ++i) {
			if (count > limit) {*result = -1; return;} // failed to factor

			temp = y*y;
			mpz_mod(temp.get_mpz_t(), temp.get_mpz_t(), (*n).get_mpz_t());
			temp = temp + c;
			mpz_mod(y.get_mpz_t(), temp.get_mpz_t(), (*n).get_mpz_t());

			count += 1;
		}
		k = 0;
		while (k < r && g == 1) {
			ys = y;

			temp = r-k;
			min_var = (m <= temp) ? m : temp;

			for (int i = 0; i < min_var; ++i) {
				temp = y*y;
				mpz_mod(temp.get_mpz_t(), temp.get_mpz_t(), (*n).get_mpz_t());
				temp = temp + c;
				mpz_mod(y.get_mpz_t(), temp.get_mpz_t(), (*n).get_mpz_t());

				temp = x-y;
				mpz_abs(temp.get_mpz_t(), temp.get_mpz_t());
				temp = q*temp;
				mpz_mod(q.get_mpz_t(), temp.get_mpz_t(), (*n).get_mpz_t());
			}
			mpz_gcd(g.get_mpz_t(), q.get_mpz_t(), (*n).get_mpz_t());
			k = k + m;
		}
		r = r * 2;
	}

  count = 0;
	if (g == *n) {
		while (true) {
			if (count > limit) {*result = -1; return;} // failed to factor
			temp = ys*ys;
			mpz_mod(temp.get_mpz_t(), temp.get_mpz_t(), (*n).get_mpz_t());
			temp = temp + c;
			mpz_mod(ys.get_mpz_t(), temp.get_mpz_t(), (*n).get_mpz_t());

			temp = x-ys;
			mpz_abs(temp.get_mpz_t(), temp.get_mpz_t());

			mpz_gcd(g.get_mpz_t(), temp.get_mpz_t(), (*n).get_mpz_t());

			if (g > 1) {break;}
			count += 1;
		}
	}

	*result = g;
}


#endif
