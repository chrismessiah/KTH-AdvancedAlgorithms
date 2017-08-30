
/*
* Lab: Factoring - https://kth.kattis.com/problems/kth.avalg.factoring
*
* Authors
*   Christian Abdelmassih
*   Marcus Wallberg
*
* ********************* DOCUMENTATION *********************
* Compile
*   $ g++ main.cpp -lgmp -lgmpxx -std=c++11
* Run
*   $ ./a.out
* ------------------------- GMP ----------------------------
* The official GMP docs
*   https://gmplib.org/manual/index.html#Top
*
* Creating variables
*   Remember to instantize an mpz_class variable before assignment.
*   For examle
*      mpz_class x;
*      x = "175891579187581657617";
*
* Using gmp(c) fucntions with gmpxx(c++) classes
*   Remember to always get the mpz_t value when running c functions
*   For example
*      mpz_abs(x.get_mpz_t(), y.get_mpz_t());
* ********************* DOCUMENTATION *********************
*/

#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <vector>

using namespace std;

#include "pollard_rho.hpp"

void start_factoring(mpz_class *number, vector<mpz_class> *output, gmp_randstate_t *state);
void factorize(mpz_class *num, vector<mpz_class> *output, gmp_randstate_t *state);

int main() {
  mpz_class number;
  vector<mpz_class> output;

  gmp_randstate_t state;
  gmp_randinit_default(state);

  bool kattis = true;
  if (!kattis) {
    vector<string> input;
    input.push_back("20");
    input.push_back("974069");
    input.push_back("4294967291");
    input.push_back("175891579187581657617");
    for(vector<string>::iterator it = input.begin(); it != input.end(); ++it) {
      number = *it;
      start_factoring(&number, &output, &state);
    }
  } else {
    string string_input;
    while (true) {
      getline(cin, string_input);
      if (string_input.empty()) {break;}
      number = string_input;
      start_factoring(&number, &output, &state);
    }
  }
  return 0;
}

void start_factoring(mpz_class *number, vector<mpz_class> *output, gmp_randstate_t *state) {

  // 2 = prime, 1 = likely prime, 0 = not prime
  if (mpz_probab_prime_p((*number).get_mpz_t(), 10) >= 1) {cout << *number << "\n\n"; return;}

  factorize(number, output, state);

  // check for errors, failed to factor etc
  for(vector<mpz_class>::iterator it2 = (*output).begin(); it2 != (*output).end(); ++it2) {
    // 2 = prime, 1 = likely prime, 0 = not prime
    if ( *it2 == 0 || mpz_probab_prime_p((*it2).get_mpz_t(), 10) == 0) {cout << "fail" << "\n\n"; return;}
  }

  // print output
  for(vector<mpz_class>::iterator it2 = (*output).begin(); it2 != (*output).end(); ++it2) {cout << *it2  << "\n";}
  cout << "\n";
  (*output).clear();
}

void factorize(mpz_class *num, vector<mpz_class> *output, gmp_randstate_t *state) {
  mpz_class a;
  rho(num, &a, state);
  if (a == 0) {
    (*output).push_back(*num);
  } else if (a == -1) {
    (*output).clear();
    a = 0;
    (*output).push_back(a);
  } else {

    if (mpz_probab_prime_p(a.get_mpz_t(), 10) >= 1) {(*output).push_back(a);}
    else {factorize(&a, output, state);}

    a = (*num)/a;

    if (mpz_probab_prime_p(a.get_mpz_t(), 10) >= 1) {(*output).push_back(a);}
    else {factorize(&a, output, state);}
  }
}
