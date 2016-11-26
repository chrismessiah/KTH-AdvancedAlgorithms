#include <gmp.h>
#include <gmpxx.h>


// ********************* DOCUMENTATION *********************
//
// ---------------------- Compiling ------------------------
// Compile: g++ main.cpp -lgmp -lgmpxx -std=c++11
// Run: ./a.out
//
// ********************* DOCUMENTATION *********************

#include "1000_primes.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

mpz_class rho_input;
mpz_class factor_input;
void rho();
void init_globals();
void factor_first_1000_primes();

void init_globals() {
  ::rho_input = 11;
  ::factor_input = "78742807416";

}

int main() {
  init_globals();

  mpz_class x;
  x = "314159265358979323846264399999999999999";
  
  // Return 2 if n is definitely prime, return 1 if n is probably prime
  // (without being certain), or return 0 if n is definitely non-prime.
  int y = mpz_probab_prime_p(x.get_mpz_t(), 10);  
  cout << "1. " << y << "\n";
  
  // store next prime larger than lower_bound in y2
  mpz_class y2, lower_bound;
  lower_bound = 10;
  mpz_nextprime(y2.get_mpz_t(),lower_bound.get_mpz_t());
  cout << "2. " << y2 << "\n";

  //rho();
  factor_first_1000_primes();

  return 0;
}

// The algorithm bellow is a copy of the pollard rho algirithm available at
// http://www.wikiwand.com/en/Pollard's_rho_algorithm
// please note that it is very similar and may need to be re-written somewhat
// ALSO THIS RETURNS NON-PRIME FACTORIALS!!!!!!!!!!!!!!!!!!!!!!!!!!
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
    cout << "The input " << factor << " is already a prime!\n";
  } else {
    cout << "\nThe factor is " << factor << "\n";
  }
}

// Looks through the first 1000 primes and divides factor_input in case it can be divided
// is said to be a good way to make huge numbers smaller
void factor_first_1000_primes() {
  for (int i = 0; i < 1000; ++i) {
    while (true) {
     if ((::factor_input % vec.at(i)) == 0) {
        cout << vec.at(i) << "\n";
        ::factor_input = ::factor_input/vec.at(i);
     } else {
      break;
     }
    }
  }
}
