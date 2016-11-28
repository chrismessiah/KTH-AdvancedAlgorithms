#include <gmp.h>
#include <gmpxx.h>
#include <mpfr.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void run_test();
mpz_class factor_input;

int main() {
  mpz_class bye, bye2;
  bye = "1267650600228229401496703205375";

  mpfr_t hej;
  mpfr_init_set_z(hej, bye.get_mpz_t(), MPFR_RNDU);
  mpfr_get_z(bye2.get_mpz_t(),hej, MPFR_RNDU);

  cout << bye << "\n";
  cout << bye2 << "\n";


	run_test();
	return 0;
}


void run_test() {
  cout << "Ran\n";
}