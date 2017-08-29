
/*
* Compile:
*   g++ gmp_test.cpp -lgmp -lgmpxx -std=c++11
*/

#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <vector>

using namespace std;

#include "pollard_rho.hpp"


void factor_this(mpz_class *num, vector<unsigned long> *output);

int main() {
  string string_input;
  vector<string> input;
  vector<unsigned long> output;

  bool kattis = false;
  if (!kattis) {
    input.push_back("20");
    input.push_back("974069");
    input.push_back("4294967291");
    input.push_back("175891579187581657617");
  } else {
    while (true) {
      getline(cin, string_input);
      if (string_input.empty()) {break;}
      input.push_back(string_input);
    }
  }

  mpz_class number;
  for(vector<string>::iterator it = input.begin(); it != input.end(); ++it) {
		number = *it;
    factor_this(&number, &output);

    for(vector<unsigned long>::iterator it2 = output.begin(); it2 != output.end(); ++it2) {
      if (*it2 == 0) {
        cout << "fail" << "\n";
      } else {
        cout << *it2  << "\n";
      }
    }
		cout << "\n";
    output.clear();
	}

  return 0;
}

void factor_this(mpz_class *num, vector<unsigned long> *output) {
  mpz_class a;
  rho(num, &a);
  if (a == 0) {
    (*output).push_back(mpz_get_ui((*num).get_mpz_t()));
  } else if (a == -1) {
    (*output).clear();
    (*output).push_back(0);
  } else {
    factor_this(&a, output);
    a = (*num)/a;
    factor_this(&a, output);
  }
}
