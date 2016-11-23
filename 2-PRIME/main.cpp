// Travelling Salesperson 2D
// https://kth.kattis.com/problems/tsp

// Authors 
// Christian Abdelmassih
// Marcus Wallberg


// DOCUMENTATION
// Possible algorithms to use
//      1. Nearest neighbour/Greedy
//      2. Clarke-Wright heuristic
//      3. K-opt (2 in our case)

// compile with: g++ *.cpp
// Run with: ./a.out

// Imports
#include <gmp.h>
#include <vector>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
using namespace std;

// global variables
int n;
bool kattis = false;
int base = 10;

// function declaractions
void get_input();
void load_test_values();

int main() {
	get_input();


	// if (!::kattis) {

	// } else {

	// }
	
	return 0;
}

void get_input() {
	if (!::kattis) {
		load_test_values();
		return;
	}

  	MP_INT integ;
  	string integ_str;
  	mpz_init (&integ);
  	mpz_set_str (&integ, "314159265358979323846264399999999999999", ::base);
	mpz_get_str (&integ_str, ::base, &integ);
	cout << integ_str << "\n";

  	MP_INT integ2;
  	string integ2_str;
  	mpz_init_set_str (&integ2, "3141592653589793238462643383279502884", ::base);
  	mpz_get_str (&integ_str2, ::base, &integ2);
  	cout << integ_str2 << "\n";

  	mpz_clear (&integ);
  	mpz_clear (&integ2);

	//mpz_add(c, a, b);
	//cin >> ::n;
}


