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
// ------------------ 100-bit highest number  --------------------
// Assumin unsigned: 0 - 1267650600228229401496703205375
// ********************* DOCUMENTATION *********************




// change this to 1k or 10k depending on how many primes you want the
// factor_first_X_primes() to seek through Note: Kattis will not search
// the 100k due to file size limitations
#include "19k_primes.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void get_input();
void factor_first_X_primes();
void load_test_values();
void reset_globals();
void print_output();
void perfect_form_test(int power);
bool check_if_prime(string mode, mpz_class num);
bool check_if_prime(string mode);
int getRandInt(int lower_bound, int upper_bound);
void brent_rho();
void check_2();

bool no_primes_found = true;
bool found_last_prime = false;
bool first_printed = false;
bool kattis = true;
bool stuck = false;
mpz_class factor_input, rand_result, rand_upper, rand_lower, untouched_input;
vector<string> input_vector;
vector<mpz_class> output_vector;

void reset_globals() {
  ::no_primes_found = true;
  ::found_last_prime = false;
  ::kattis = false;
  ::stuck = false;
  ::output_vector.clear();
}

// checks whenether ::factor_input is a perfect square, cube etc. As mpz is 
// integer only we do not need a floow function here. 
void perfect_form_test(int power) {
  mpz_class root, input_test;
  mpz_root(root.get_mpz_t(), ::factor_input.get_mpz_t(), power);
  mpz_pow_ui(input_test.get_mpz_t(), root.get_mpz_t(), power);
  if (input_test == ::factor_input && check_if_prime("s", root)) {
    ::factor_input = root;
    for (int i = 0; i < power; ++i) {
      ::output_vector.push_back(root);
    }
  }
}

// If mode=s (s for soft) this function will also return true if its unsure 
bool check_if_prime(string mode) {
  int y = mpz_probab_prime_p(::factor_input.get_mpz_t(), 20);
  if (y == 2) {return true;}
  if (y == 1 && mode == "s") {return true;}
  return false;
}

bool check_if_prime(string mode, mpz_class num) {
  int y = mpz_probab_prime_p(num.get_mpz_t(), 20);
  if (y == 2) {return true;}
  if (y == 1 && mode == "s") {return true;}
  return false;
}

bool multiply_check() {
  mpz_class temp;
  temp = 1;
  for(vector<mpz_class>::iterator it = ::output_vector.begin(); it != ::output_vector.end(); ++it) {
    temp *= *it;
  }
  if (::untouched_input == temp) {return true;}
  return false;
}

void print_output() {
  if (first_printed) {cout << "\n";}
  ::first_printed = true;
  if (::found_last_prime && multiply_check() ) {
    for(vector<mpz_class>::iterator it = ::output_vector.begin(); it != ::output_vector.end(); ++it) {
      cout << *it << "\n";
    }
  } else {
    cout << "fail" << "\n";
  }
}

// returns num, lower_bound <= num <= upper_bound
void getRandInt() {
  gmp_randclass r1 (gmp_randinit_default);
  ::rand_result = r1.get_z_range(::rand_upper-::rand_lower) + ::rand_lower;
}

void check_2() {
  while (::factor_input % 2 == 0) {
    ::factor_input /= 2;
    ::output_vector.push_back(2);
    ::no_primes_found = false;
  }
}

// Source: https://comeoncodeon.wordpress.com/2010/09/18/pollard-rho-brent-integer-factorization/
// Do NOT input primes here!!!!!!
// seems to be able to output non-prime numbers due to gcd
void brent_rho() {
  check_2();

  int count = 0;      // for limiting infitate loops
    int limit = 2000;   // for limiting infitate loops
    mpz_class y,c,m,g,q,ys, min_var, x, N, r, k;
    N = ::factor_input;
    ::rand_lower = 1;
    ::rand_upper = N-1;
    getRandInt(); y = ::rand_result;
    getRandInt(); c = ::rand_result;
    getRandInt(); m = ::rand_result;
    g = 1;
    r = 1;
    q = 1;
    while (g == 1) {
      x = y;
      for (int i = 0; i < r; ++i) {
          
          // limit checker to prevent inifinite loops
        count += 1;
        if (count > limit){::stuck = true; return;}
          // limit checker to prevent inifinite loops
        y = ( (y*y) % N +c ) % N;
      }
      k = 0;
      while (k < r && g == 1) {
        ys = y;
      min_var = (m <= r-k) ? m : r-k; // min function
      for (int i = 0; i < min_var; ++i) {
        y = ( (y*y) % N + c ) % N;
        q = q * ( abs(x-y) ) % N;
      }
      g = gcd(q,N);
      k = k + m;
    }
    r *= 2;
  }

    count = 0;  // limit checker to prevent inifinite loops

    if (g == N) {
      while (true) {

        // limit checker to prevent inifinite loops
      count += 1;
      if (count > limit){::stuck = true; return;}
        // limit checker to prevent inifinite loops

      ys = ( (ys * ys) % N + c ) % N;
      g = gcd( abs(x-ys), N);
      if (g > 1) {break;}
    }
  }

  ::factor_input /= g;
  ::output_vector.push_back(g);
  ::no_primes_found = false;

  return;
}

int main() {
  get_input();
  for(vector<string>::iterator it = ::input_vector.begin(); it != ::input_vector.end(); ++it) {
    ::factor_input = *it;
    ::untouched_input = *it;
    reset_globals();
    factor_first_X_primes();
    //if (check_if_prime("s")) {
    if (false) {
      ::output_vector.push_back(::factor_input);
      ::found_last_prime = true;
    } else {
      //while(::factor_input != 1) {
      for (int i = 0; i < 8; ++i){ // max amount of loops needed
        if (::factor_input == 1) {
          ::found_last_prime = true;
          break;
        }
        
        brent_rho();
        if (::stuck){break;}
        
        if (check_if_prime("h")) {  
          ::output_vector.push_back(::factor_input);
          ::found_last_prime = true;
          break;
        }
      }
    }

    print_output();
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
      if (::factor_input == 1) {
        ::found_last_prime = true;
        return;
      }
      if ((::factor_input % prime_vector.at(i)) == 0) {
        ::factor_input = ::factor_input/prime_vector.at(i);
        ::output_vector.push_back(prime_vector.at(i));
        ::no_primes_found = false;

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