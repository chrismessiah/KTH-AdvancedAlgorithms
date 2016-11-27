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

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void get_input();
void factor_first_X_primes();
void load_test_values();

bool no_primes_found = true;
bool kattis = false;
mpz_class factor_input;
vector<string> input_vector;

int main() {
  int y;
  mpz_class last_prime, next_prime;
  get_input();
  for(vector<string>::iterator it = ::input_vector.begin(); it != ::input_vector.end(); ++it) {
    ::factor_input = *it;
    factor_first_X_primes();


    // really stupid block of code bellow tbh, need nore sophisticated search here
    // the thing is that we need to limit the search in case the last prime factor
    // is simply too large. We cant keep searching forever due to time limit so
    // at some point we need to give up. For example 
    //
    //      175891579187581657617 = 3*7*71*117968865987646987 
    //
    // the last prime is so large that we will never find it
    if (!::no_primes_found && ::factor_input > 1) {
      last_prime = prime_vector.at(prime_vector.size()-1);
      for (int i = 0; i < 10000; ++i) { // give up after 10k tries
        y = mpz_probab_prime_p(::factor_input.get_mpz_t(), 20); // should be 15 - 50 accord. to docs
        if (y == 2) {cout << y << "\n"; break;}
        if (::factor_input == 1) {break;}
        mpz_nextprime(next_prime.get_mpz_t(), last_prime.get_mpz_t());
        if ((::factor_input % next_prime) == 0) {
          ::factor_input = ::factor_input/next_prime;
          cout << next_prime << "\n";
        }
        last_prime = next_prime;
      }
    }


    cout << "\n";
  }

  return 0;
}

// Looks through the first X primes and divides factor_input in case it can be divided
// is said to be a good way to make huge numbers smaller
void factor_first_X_primes() {
  for (int i = 0; i < prime_vector.size(); ++i) {

    // we may want to loop multiple times for each prime since that prime can occur
    // more than once
    while (true) {
     if ((::factor_input % prime_vector.at(i)) == 0) {
        ::factor_input = ::factor_input/prime_vector.at(i);

        // if the input is already a prime we don't want to print anything since we can't
        // factor it!
        if (::no_primes_found && ::factor_input == 1){return;}
        
        cout << prime_vector.at(i) << "\n";
        ::no_primes_found = false;
     } else if(::factor_input == 1) {
      return;
     } else {
      break;
     }
    }
  }
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
    ::input_vector.push_back(temp_input);
  }
}

void load_test_values() {
  ::input_vector.push_back("20");
  ::input_vector.push_back("175891579187581657617");
  ::input_vector.push_back("4294967291");
}