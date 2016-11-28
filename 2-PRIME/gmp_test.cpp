#include <gmp.h>
#include <gmpxx.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

mpz_class factor_input;

int main() {
	::factor_input = "1267650600228229401496703205375";
  long double var = 1267650600228229401496703205375;
  cout << ::factor_input << "\n";
  cout << var << "\n";
	return 0;
}