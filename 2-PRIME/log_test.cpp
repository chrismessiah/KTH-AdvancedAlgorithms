#include <gmp.h>
#include <gmpxx.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

mpz_class factor_input;
mpz_class factor_input_f;
void fp_log (mpf_t lg, const mpf_t z, unsigned int prec);
void fp_log2(mpf_t l2, unsigned int prec);
void fp_log_m1(mpf_t lg, const mpf_t z, unsigned int prec);
void fp_epsilon(mpf_t eps, int prec);
double round_to_x(mpf_class large_num, string round_to);

// NEED FOR log2
static pthread_spinlock_t mp_const_lock;
// NEED FOR log2

int main() {
	// NEED FOR log2!!
	pthread_spin_init(&mp_const_lock, 0);
	// NEED FOR log2!!

	::factor_input = "1267650600228229401496703205375";
	::factor_input_f = "1267650600228229401496703205375";
	long double var = 1267650600228229401496703205375;
	cout << ::factor_input << "\n";
	cout << ::factor_input_f << "\n";
	cout << var << "\n";

	cout << "NOW RUNNING LOG\n";
	mpf_class res, b;

	b = 2;
	long double c = 2;

	fp_log(res.get_mpf_t(),b.get_mpf_t(),10000);
	cout << res << "\n";
	cout << b << "\n";
	cout << log(c) << "\n";

	cout << "N!!!!!!!!!!!!!!!!G\n";
	double res2 = round_to_x(::factor_input, "10000000");
	cout << res2 << "\n";
	cout << log(res2) << "\n";

	return 0;
}

// round to 10, 100, 1000, 10000
double round_to_x(mpf_class large_num, string round_to) {
	mpf_class temp;
	temp = round_to;
    large_num /= temp;
    large_num = floor(large_num + 0.5) * temp;  
    return large_num.get_d();
}


void fp_log (mpf_t lg, const mpf_t z, unsigned int prec) {
	mp_bitcnt_t bits = ((double) prec) * 3.322 + 50;
	mpf_t zee;
	mpf_init2 (zee, bits);
	mpf_set (zee, z);
	int nexp = 0;

	/* Assume branch cut in the usual location, viz
	 * along negative z axis */
	if (mpf_cmp_ui(zee, 0) <= 0) {
		fprintf(stderr, "Error: bad domain for fp_log: log(%g)\n", mpf_get_d(zee));
		mpf_clear (zee);
		exit (1);
	}

	/* Find power of two by means of bit-shifts */
	while (mpf_cmp_ui(zee, 2) > 0) {
		nexp ++;
		mpf_div_ui (zee, zee, 2);
	}

	while (mpf_cmp_ui(zee, 1) < 0) {
		nexp --;
		mpf_mul_ui (zee, zee, 2);
	}

#if 1
	/* Apply simple-minded series summation
	 * This appears to be faster than the Feynman algorithm
	 * for the types of numbers and precisions I'm encountering. */
	if (mpf_cmp_d(zee, 1.618) > 0) {
		mpf_ui_div (zee, 1, zee);
		mpf_ui_sub (zee, 1, zee);
		fp_log_m1 (lg, zee, prec);
	} else {
		mpf_ui_sub (zee, 1, zee);
		fp_log_m1 (lg, zee, prec);
		mpf_neg (lg, lg);
	}
#else
	fp_log_shiftadd (lg, zee, prec);
#endif

	/* Add log (2^n) = n log (2) to result. */
	if (0 != nexp) {
		fp_log2 (zee, prec);
		if (0 > nexp) {
			mpf_mul_ui (zee, zee, -nexp);
			mpf_neg (zee, zee);
		} else {
			mpf_mul_ui (zee, zee, nexp);
		}
		mpf_add (lg,lg, zee);
	}

	mpf_clear (zee);
}


void fp_log_m1 (mpf_t lg, const mpf_t z, unsigned int prec) {
	mp_bitcnt_t bits = ((double) prec) * 3.322 + 50;
	mpf_t zee, z_n, term;

	mpf_init2 (zee, bits);
	mpf_init2 (z_n, bits);
	mpf_init2 (term, bits);

	/* Make copy of argument now! */
	mpf_set (zee, z);
	mpf_mul (z_n, zee, zee);
	mpf_set (lg, zee);

	/* Use 10^{-prec} for smallest term in sum */
	mpf_t maxterm;
	mpf_init2 (maxterm, bits);
	fp_epsilon (maxterm, prec);

	unsigned int n=2;
	while(1) {
		mpf_div_ui (term, z_n, n);
		mpf_add (lg, lg, term);

		/* don't go no farther than this */
		mpf_abs (term, term);
		if (mpf_cmp (term, maxterm) < 0) break;

		n ++;
		mpf_mul (z_n, z_n, zee);
	}

	mpf_clear (zee);
	mpf_clear (z_n);
	mpf_clear (term);

	mpf_clear (maxterm);
}

void fp_log2 (mpf_t l2, unsigned int prec) {
	static unsigned int precision=0;
	static mpf_t cached_log2;

	pthread_spin_lock(&mp_const_lock);
	if (precision >= prec) {
		mpf_set (l2, cached_log2);
		pthread_spin_unlock(&mp_const_lock);
		return;
	}

	if (0 == precision) {
		mpf_init (cached_log2);
	}
	mp_bitcnt_t bits = ((double) prec) * 3.322 + 50;
	mpf_set_prec (cached_log2, bits);

	mpf_t two;
	mpf_init2 (two, bits);
	mpf_set_ui (two, 2);
	fp_log (cached_log2, two, prec);
	mpf_set (l2, cached_log2);

	mpf_clear (two);
	precision = prec;
	pthread_spin_unlock(&mp_const_lock);
}

void fp_epsilon(mpf_t eps, int prec) {
	static int cache_prec = -1;
	static mpf_t cache_eps;

	if (-1 == cache_prec) {
		mpf_init (cache_eps);
	}

	if (prec == cache_prec) {
		mpf_set (eps, cache_eps);
		return;
	}
	if (cache_prec < prec) {
		mpf_set_prec (cache_eps, 3.322*prec+50);
	}

	/* double mex = ((double) prec) * log (10.0) / log(2.0); */
	double mex = ((double) prec) * 3.321928095;
	unsigned int imax = (unsigned int) (mex +1.0);
	mpf_t one;
	mpf_init (one);
	mpf_set_ui (one, 1);
	mpf_div_2exp (cache_eps, one, imax);

	mpf_set (eps, cache_eps);
	cache_prec = prec;
	mpf_clear (one);
}