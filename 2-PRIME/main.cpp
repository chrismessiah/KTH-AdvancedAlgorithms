
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

void factorize(mpz_class *num, vector<mpz_class> *output);
void start_factoring(string *string_input, vector<mpz_class> *output);

int main() {
  string string_input;
  vector<mpz_class> output;

  bool kattis = true;
  if (!kattis) {
    vector<string> input;
    input.push_back("20");
    input.push_back("974069");
    input.push_back("4294967291");
    input.push_back("175891579187581657617");
    for(vector<string>::iterator it = input.begin(); it != input.end(); ++it) {
      string_input = *it;
      start_factoring(&string_input, &output);
    }
  } else {
    while (true) {
      getline(cin, string_input);
      if (string_input.empty()) {break;}
      start_factoring(&string_input, &output);
    }
  }
  return 0;
}

void start_factoring(string *string_input, vector<mpz_class> *output) {
  mpz_class number;
  number = *string_input;

  // 2 = prime, 1 = likely prime, 0 = not prime
  if (mpz_probab_prime_p(number.get_mpz_t(), 20) >= 1) {cout << number << "\n\n"; return;}

  factorize(&number, output);

  // check for errors, failed to factor etc
  for(vector<mpz_class>::iterator it2 = (*output).begin(); it2 != (*output).end(); ++it2) {
    // 2 = prime, 1 = likely prime, 0 = not prime
    if ( *it2 == 0 || mpz_probab_prime_p((*it2).get_mpz_t(), 20) == 0) {cout << "fail" << "\n\n"; return;}
  }

  // print output
  for(vector<mpz_class>::iterator it2 = (*output).begin(); it2 != (*output).end(); ++it2) {cout << *it2  << "\n";}
  cout << "\n";
  (*output).clear();
}

void factorize(mpz_class *num, vector<mpz_class> *output) {
  mpz_class a;
  rho(num, &a);
  if (a == 0) {
    (*output).push_back(*num);
  } else if (a == -1) {
    (*output).clear();
    a = 0;
    (*output).push_back(a);
  } else {

    if (mpz_probab_prime_p(a.get_mpz_t(), 20) >= 1) {(*output).push_back(a);}
    else {factorize(&a, output);}

    a = (*num)/a;

    if (mpz_probab_prime_p(a.get_mpz_t(), 20) >= 1) {(*output).push_back(a);}
    else {factorize(&a, output);}
  }
}
