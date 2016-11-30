#include <gmp.h>
#include <gmpxx.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

mpz_class factor_input;
mpz_class factor_input_f;

int main() {

	::factor_input = "1267650600228229401496703205375";
	double temp = ::factor_input.get_d();
	cout << ::factor_input << "\n";
	cout << temp << "\n";




	// ::factor_input_f = "1267650600228229401496703205375";
	// long double var = 1267650600228229401496703205375;
	// cout << ::factor_input << "\n";
	// cout << ::factor_input_f << "\n";
	// cout << var << "\n";

	// cout << "NOW RUNNING LOG\n";
	// mpf_class res, b;

	// b = 2;
	// long double c = 2;

	// fp_log(res.get_mpf_t(),b.get_mpf_t(),10000);
	// cout << res << "\n";
	// cout << b << "\n";
	// cout << log(c) << "\n";

	// cout << "N!!!!!!!!!!!!!!!!G\n";
	// double res2 = round_to_x(::factor_input, "10000000");
	// cout << res2 << "\n";
	// cout << log(res2) << "\n";

	return 0;
}