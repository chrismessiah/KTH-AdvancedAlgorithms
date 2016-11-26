#include <gmp.h>
#include <gmpxx.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main() {
  mpz_class x;
  x = "314159265358979323846264399999999999999";
  
  // Return 2 if n is definitely prime, return 1 if n is probably prime
  // (without being certain), or return 0 if n is definitely non-prime.
  int y = mpz_probab_prime_p(x.get_mpz_t(), 10);  
  cout << "1. " << y << "\n";
  
  // store next prime larger than lower_bound in y2
  mpz_class y2, lower_bound;
  lower_bound = 10;
  mpz_nextprime();
  //mpz_nextprime(y2.get_mpz_t(),lower_bound);
  cout << "2. " << y << "\n";
  
  return 0;
}
