#include <gmp.h>
#include <gmpxx.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void perfect_test();
mpz_class factor_input;
vector<mpz_class> output_vector;

int main() {
	::factor_input = "262144";
	perfect_test();
	return 0;
}

bool check_if_prime(string mode, mpz_class num) {
  int y = mpz_probab_prime_p(num.get_mpz_t(), 20);
  if (y == 2) {return true;}
  if (y == 1 && mode == "s") {return true;}
  return false;
}

// does not neccecarily find prime factors, thus needs to run multiple times
// example 2^18 = 262144 while the root found is 512^2 = 262144
void perfect_test() {
    int res = mpz_perfect_power_p(::factor_input.get_mpz_t());
    if (res != 0) {
      mpz_class root;
      int power = 2;
      int test;
      while (true) {
      	test = mpz_root(root.get_mpz_t(),::factor_input.get_mpz_t(), power);
      	//if (test =! 0 && power != 2) {
      	cout << "Root is: " << root << "\n";
      	if (test =! 0 && check_if_prime("h", root)) {
      		cout << "Root is: " << root;
      		cout << "Power is: " << power;
      		//for (int i = 0; i < power; ++i) {
      		//	::output_vector.push_back(root);
      		//}
      		//::output_vector.push_back(::factor_input);
      		//::found_last_prime = true;
      		break;
      	}
      	power += 1;
      }
     // for(vector<mpz_class>::iterator it = ::output_vector.begin(); it != ::output_vector.end(); ++it) {
      //	cout << *it << "\n";
      //}
  	}
}