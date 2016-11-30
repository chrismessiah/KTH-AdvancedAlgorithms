#include <gmp.h>
#include <gmpxx.h>


// ********************* DOCUMENTATION *********************
//
// ---------------------- Compiling ------------------------
// Compile: g++ main.cpp -lgmp -lgmpxx -std=c++11
// Run: ./a.out
//
// ------------------ Online Factorizer --------------------
// Great site for prime factorization
// http://www.numberempire.com/numberfactorizer.php
//
// ********************* DOCUMENTATION *********************




// change this to 1k, 10k, or 100k depending on how many primes
// you want the factor_first_X_primes() to seek through
#include "100k_primes.h"


#include <time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

clock_t start;
mpz_class rho_input;
mpz_class factor_input, factor_input2;
void init_globals();
void factor_first_X_primes();

// time fuctions
void resetTimer();
void printRunTime();
double getRunTime();

void init_globals() {
  ::rho_input = 11;

  // ridiculously large but can actually be factorized to 
  // 23*127*1231*2791*2299907*95880419*141958116336983 
  // however, its more than 100 bit so it should only
  // be used for testing purposes 
  ::factor_input2 = "314159265358979323846264399999999999999";

  // The largest (unsigned) 100 bit number that exists
  // we will not be handling numbrs above this.
  ::factor_input = "1267650600228229401496703205375"

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

  resetTimer();
  factor_first_X_primes();
  printRunTime();

  return 0;
}

// Looks through the first X primes and divides factor_input in case it can be divided
// is said to be a good way to make huge numbers smaller
void factor_first_X_primes() {
  bool no_primes_found = true;
  for (int i = 0; i < prime_vector.size(); ++i) {

    // we may want to loop multiple times for each prime since that prime can occur
    // more than once
    while (true) {
     if ((::factor_input % prime_vector.at(i)) == 0) {
        ::factor_input = ::factor_input/prime_vector.at(i);

        // if the input is already a prime we don't want to print anything since we can't
        // factor it!
        if (no_primes_found && ::factor_input == 1){return;}
        
        cout << prime_vector.at(i) << "\n";
        no_primes_found = false;
     } else if(::factor_input == 1) {
      return;
     } else {
      break;
     }
    }
  }
}


void resetTimer() {
  ::start = clock();
}

void printRunTime() {
  cout << "Current runtime: " << getRunTime() << " s\n";
}

// returns time in seconds
double getRunTime() {
  return(( clock() - ::start ) / (double) CLOCKS_PER_SEC);
}