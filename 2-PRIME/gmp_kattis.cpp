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

void reset_globals();
bool perfect_form_test(mpz_class N, int power);
bool multiply_output_check(vector<mpz_class> vec);
void print_output(vector<mpz_class> vec);
mpz_class getRandInt(mpz_class lower, mpz_class upper);
mpz_class brent_rho(mpz_class N);
pair<int,int> factor_first_X_primes(mpz_class N, int start_index);
vector<string> get_input();
vector<string> load_test_values();

bool no_primes_found = true;
bool found_last_prime = false;
bool first_printed = false;
bool kattis = false;
bool stuck = false;
bool error = false;

mpz_class untouched_input;

int main() {
  vector<string> input_numbers = get_input();
  vector<mpz_class> output_numbers;
  mpz_class mpz_input;
  for(vector<string>::iterator it = input_numbers.begin(); it != input_numbers.end(); ++it) {
    output_numbers.clear();
    mpz_input = *it;
    ::untouched_input = *it;
    reset_globals();

    //cout << "Running num: " << mpz_input <<  endl;
    
    // ------------------------- STAGE 1 ----------------------
    
    // Is this already a prime?
    if (mpz_probab_prime_p(mpz_input.get_mpz_t(), 20)) {
      //cout << "STAGE 1 found factor: " << mpz_input <<  endl;
      output_numbers.push_back(mpz_input);
      mpz_input /= mpz_input;
    }

    // goto next loop if done factoring
    if (mpz_input == 1) {
      print_output(output_numbers);
      continue;
    }



    // ------------------------- STAGE 2 ----------------------

    // Factor using 19k prime list
    int start_index, factor;
    start_index = 0;
    pair<int,int> res_pair;
    while (start_index != prime_vector.size()) {
      if (mpz_input == 1) {break;}
      //cout << "start_index is: " << start_index << endl;
      res_pair = factor_first_X_primes(mpz_input, start_index);
      factor = res_pair.first;
      mpz_input /= factor;
      start_index = res_pair.second;
      if (factor != 1){ output_numbers.push_back(factor); }
      //cout << "STAGE 2 found factor: " << factor <<  endl;
    }

    // goto next loop if done factoring
    if (mpz_input == 1) {
      print_output(output_numbers);
      continue;
    }

    // ------------------------- STAGE 3 ----------------------

    // Check for perfect forms/powers
    mpz_class root;
    for (int power = 2; power < 7; ++power) {
      if ( perfect_form_test(mpz_input, power) ) {
        mpz_root(root.get_mpz_t(), mpz_input.get_mpz_t(), power);
        for (int i = 0; i < power; ++i) {
          mpz_input /= root;
          output_numbers.push_back(root);
          //cout << "STAGE 3 found factor: " << root <<  endl;
        }
        if (mpz_input == 1) {break;}
      }
    }

    if (mpz_input == 1) {
      print_output(output_numbers);
      continue;
    }


    // ------------------------- STAGE 4 ----------------------
    // Do qs here

    

    // ------------------------- FAIL? ----------------------

    // Just print to check if we are correct (will print fail otherwise)
     print_output(output_numbers);

  }

  return 0;
}


void reset_globals() {
  ::no_primes_found = true;
  ::found_last_prime = false;
  ::kattis = false;
  ::stuck = false;
}

// checks whenether ::factor_input is a perfect square, cube etc. As mpz is 
// integer only we do not need a floow function here. 
bool perfect_form_test(mpz_class N, int power) {
  mpz_class root, res;
  mpz_root(root.get_mpz_t(), N.get_mpz_t(), power);
  mpz_pow_ui(res.get_mpz_t(), root.get_mpz_t(), power);
  return (res == N) ? true : false;
}

bool multiply_output_check(vector<mpz_class> vec) {
  mpz_class temp;
  mpz_class num;
  temp = 1;
  for(vector<mpz_class>::iterator it = vec.begin(); it != vec.end(); ++it) {
    num = *it;
    //cout << "Num is: " << num << "\n";
    temp *= *it;
  }
    return (::untouched_input == temp) ? true : false;
}

void print_output(vector<mpz_class> vec) {
  if (::first_printed) {cout << "\n";}
  ::first_printed = true;
  if (!::error && multiply_output_check(vec)) {
    for(vector<mpz_class>::iterator it = vec.begin(); it != vec.end(); ++it) { cout << *it << "\n"; }
  } else {
    cout << "fail" << "\n";
  }
}

// returns num, lower_bound <= num <= upper_bound
mpz_class getRandInt(mpz_class lower, mpz_class upper) {
  gmp_randclass r1 (gmp_randinit_default);
  return (r1.get_z_range(upper-lower) + lower);
}

// Source: https://comeoncodeon.wordpress.com/2010/09/18/pollard-rho-brent-integer-factorization/
// Do NOT input primes here!!!!!!
// seems to be able to output non-prime numbers due to gcd
mpz_class brent_rho(mpz_class N) {
  if (N % 2 == 0) {return 2;}

  //int count = 0;      // for limiting infitate loops
  //int limit = 2000;   // for limiting infitate loops
  mpz_class y,c,m,g,q,ys, min_var, x, r, k;
  y = getRandInt(1, N-1);
  c = getRandInt(1, N-1);
  m = getRandInt(1, N-1);
  g = 1;
  r = 1;
  q = 1;
  while (g == 1) {
    x = y;
    for (int i = 0; i < r; ++i) {

      // limit checker to prevent inifinite loops
      //count += 1;
      //if (count > limit){::stuck = true; return;}
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

  //count = 0;  // limit checker to prevent inifinite loops

  if (g == N) {
    while (true) {

        // limit checker to prevent inifinite loops
        //count += 1;
        //if (count > limit){::stuck = true; return;}
        // limit checker to prevent inifinite loops

      ys = ( (ys * ys) % N + c ) % N;
      g = gcd( abs(x-ys), N);
      if (g > 1) {break;}
    }
  }

  //::factor_input /= g;
  //::output_numbers.push_back(g);
  //::no_primes_found = false;

  return g;
}

// Looks through the first X primes and divides factor_input in case it can be divided
// is said to be a good way to make huge numbers smaller
pair<int,int> factor_first_X_primes(mpz_class N, int start_index) {
  for (int i = start_index; i < prime_vector.size(); ++i) {
    if (N == 1) { return make_pair(1,i) ;}
    else if (N % prime_vector[i]  == 0) { return make_pair(prime_vector[i],i) ;}
  }
  return make_pair(1,prime_vector.size());
}

vector<string> get_input() {
  if (!::kattis) { return load_test_values(); }
  
  string temp_input;
  vector<string> vec;
  while (true) {
    getline(cin, temp_input);
    if (temp_input.empty()) {break;}
    vec.push_back(temp_input);
  }
  return vec;
}

vector<string> load_test_values() {
  vector<string> vec;
  vec.push_back("20");
  vec.push_back("175891579187581657617");
  vec.push_back("4294967291");
  vec.push_back("16");
  vec.push_back("9");
  vec.push_back("1024");
  return vec;
}