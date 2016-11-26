// Factoring
// https://kth.kattis.com/problems/kth.avalg.factoring

// Authors 
// Christian Abdelmassih
// Marcus Wallberg

// ********************* DOCUMENTATION *********************
//
// ---------------------- Compiling ------------------------
// Compile: g++ main.cpp -lgmp -lgmpxx -std=c++11
// Run: ./a.out
//
// ------------------------- GMP ----------------------------
// # References for gmp
//   Link 1 - another programming language but easier to find relevant functions
//   http://pike.lysator.liu.se/generated/manual/modref/ex/predef_3A_3A/Gmp/mpz.html
//
//   Link 2 - The official docs
//   https://gmplib.org/manual/index.html#Top
//
// # Creating variables
//   Remember to instantize an mpz_class variable before ass-ignment. For examle
//      mpz_class x;
//      x = "175891579187581657617";
//
// # Using gmp(c) fucntions with gmpxx(c++) classes
//   Remember to always get the mpz_t value when running c functions like so
//      mpz_nextprime(x.get_mpz_t(), y.get_mpz_t())
// ********************* DOCUMENTATION *********************

// Imports
#include <gmp.h>
#include <gmpxx.h>

#include <vector>
#include <stack>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
using namespace std;

// global variables
int n;
bool kattis = false;
int base = 10;
vector<string> input;
mpz_class rho_input, rho_output;
stack<mpz_class> staq;

// function declaractions
void get_input();
void load_test_values();
void rho();
void factor_this();

void factor_this() {
	while (true) {
		cout << "Input is: " << ::rho_input << "\n";
		rho();
		cout << "Output is: " << ::rho_output << "\n";
		if (mpz_cmp_si(::rho_output.get_mpz_t(), -1) == 0) {
    		// could not factor the number, might already be a prime?
			::rho_output = ::rho_input;

			int res = mpz_probab_prime_p(::rho_output.get_mpz_t(), 2);
			if (res == 2) {
    			// is a prime
				cout << ::rho_output << "\n";
			} else if (res == 0) {
    			// not a prime
				cout << "fail" << "\n";
			} else {
    			// mpz fuction does not know
				cout <<  "Could be prime" << ::rho_output << "\n";
			}
			return;
		} else {
    		// found factor but we dont know if its a prime!
			int res = mpz_probab_prime_p(::rho_output.get_mpz_t(), 2);
			if (res == 2) {
    			// is a prime, go ahead and print it!
				cout << ::rho_output << "\n";
			} else if (res == 0) {
    			// not a prime so we need to factor this as well, dont print it yet!
    			mpz_class temp;
    			temp = ::rho_input;
    			::rho_input = ::rho_output;
				factor_this();
				::rho_input = temp;
			} else {
    			/// we no not know!
				cout << "What the heck is " << ::rho_output << "???\n";
			}
			::rho_input = ::rho_input/::rho_output;
		}
	}
}

int main() {
	get_input();
	int i = 0;
	for(vector<string>::iterator it = ::input.begin(); it != ::input.end(); ++it) {
		::rho_input = *it;
		factor_this();
		cout << "\n";
	}

	return 0;
}

void get_input() {
	if (!::kattis) {
		load_test_values();
		return;
	}
	string temp_input;
	while (true) {
		getline(cin, temp_input);
		if (temp_input.empty()) {break;}
		::input.push_back(temp_input);
	}
}

void load_test_values() {
	::input.push_back("20");
	::input.push_back("175891579187581657617");
	::input.push_back("4294967291");
}


// The algorithm bellow is a copy of the pollard rho algirithm available at
// http://www.wikiwand.com/en/Pollard's_rho_algorithm
// please note that it is very similar and may need to be re-written somewhat
void rho() {
	mpz_class number, x_fixed, cycle_size, x, factor, x_temp;
	x_fixed = 2;
	cycle_size = 2;
	x = 2;
	factor = 1;

	while (factor == 1) {
		for (int count=1;count <= cycle_size && factor <= 1;count++) {
			x = (x*x+1) % ::rho_input;
			x_temp = x-x_fixed;
			mpz_gcd(factor.get_mpz_t(),x_temp.get_mpz_t(), ::rho_input.get_mpz_t());
		}
		cycle_size *= 2;
		x_fixed = x;
	}
	if (factor == ::rho_input) {
  	::rho_output = "-1"; // failed to factor, is already a prime?
  } else {
    ::rho_output = factor; // found prime factor!
}
}
