// Factoring
// https://kth.kattis.com/problems/kth.avalg.factoring

// Authors 
// Christian Abdelmassih
// Marcus Wallberg

// ********************* DOCUMENTATION *********************
//
// ---------------------- Compiling ------------------------
// Compile: g++ main.cpp -lgmp -lgmpxx
// Run: ./a.out
//
// ------------------------- GMP ----------------------------
// # References for gmp
//   Link 1 - another programming language but easier to find relevant functions
//   http://pike.lysator.liu.se/generated/manual/modref/ex/predef_3A_3A/Gmp/mpz.html
//
//   Link 2 - The official docs
//   https://gmplib.org/manual/index.html#Top
//
// # Creating variables
//   Remember to instantize an mpz_class variable before ass-ignment. For examle
//      mpz_class x;
//      x = "175891579187581657617";
//
// # Using gmp(c) fucntions with gmpxx(c++) classes
//   Remember to always get the mpz_t value when running c functions like so
//      mpz_nextprime(x.get_mpz_t(), y.get_mpz_t())
// ********************* DOCUMENTATION *********************

// Imports
#include <gmp.h>
#include <gmpxx.h>

#include <vector>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
using namespace std;

// global variables
int n;
bool kattis = false;
int base = 10;
vector<string> input;

// function declaractions
void get_input();
void load_test_values();

int main() {
	get_input();

	// loop over all values, good for later!
	cout << "printing input values" << "\n";
	for(vector<string>::iterator it = ::input.begin(); it != ::input.end(); ++it) {
    	cout << *it << "\n";
	}

	// how additions work, also good for later!
  	mpz_class a, b, c;
  	a = "314159265358979323846264399999999999999";
  	b = "314159265358979323846264338327950288400";
  	c = a+b; // in this case + is not ordinary addition but an overloaded addidtion using gmp!
	cout << "Sum is: " << c << "\n";
	

	return 0;
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
		::input.push_back(temp_input);
	}
}

void load_test_values() {
	::input.push_back("20");
	::input.push_back("175891579187581657617");
	::input.push_back("4294967291");
}


