
/*
* Compile:
*   g++ gmp_test.cpp -lgmp -lgmpxx -std=c++11
*/

#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <vector>

using namespace std;

//#include "brent_rho.hpp" // do not use. Not working
//#include "wiki_rho.hpp" // copy of wikipedia rho algorithm. Something seems missing in it.
#include "pollard_rho.hpp" // working version of pollard rho algorithm


void factor_this(mpz_class *num, vector<mpz_class> *output);
void factor_this_root(string *string_input, vector<mpz_class> *output);

int main() {
  string string_input;
  vector<mpz_class> output;

  bool kattis = false;
  if (!kattis) {
    vector<string> input;
    input.push_back("20");
    input.push_back("974069");
    input.push_back("4294967291");
    input.push_back("175891579187581657617");
    for(vector<string>::iterator it = input.begin(); it != input.end(); ++it) {
      string_input = *it;
      factor_this_root(&string_input, &output);
    }
  } else {
    while (true) {
      getline(cin, string_input);
      if (string_input.empty()) {break;}
      factor_this_root(&string_input, &output);
    }
  }

  return 0;
}

void factor_this_root(string *string_input, vector<mpz_class> *output) {
  mpz_class number;
  number = *string_input;

  // 2 = prime, 1 = likely prime, 0 = not prime
  if (mpz_probab_prime_p(number.get_mpz_t(), 20) >= 1) {cout << number << "\n\n"; return;}

  factor_this(&number, output);

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

void factor_this(mpz_class *num, vector<mpz_class> *output) {
  mpz_class a;
  rho(num, &a);
  if (a == 0) {
    (*output).push_back(*num);
  } else if (a == -1) {
    (*output).clear();
    a = 0;
    (*output).push_back(a);
  } else {
    factor_this(&a, output);
    a = (*num)/a;
    factor_this(&a, output);
  }
}
