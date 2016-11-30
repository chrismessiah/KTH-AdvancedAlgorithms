#include <time.h>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
using namespace std;

int brent_rho(int N);
int getRandInt(int lower_bound, int upper_bound);
int gcd(int a, int b);

int main() {
	srand(time(NULL));
	
	int in = 1555;
	int res;

	while (in != 1) {
		res = brent_rho(in);
		in /= res;
		cout << res << "\n";
	}
	cout << "DONE" << "\n";
	return 0;
}

// Source: https://comeoncodeon.wordpress.com/2010/09/18/pollard-rho-brent-integer-factorization/
// Do NOT input primes here!!!!!!
int brent_rho(int N) {
	if (N % 2 == 0) {return 2;}
	int y,c,m,g,r,q,ys, min_var, x, k;
	y = getRandInt(1,N-1);
	c = getRandInt(1,N-1);
	m = getRandInt(1,N-1);
	g = 1;
	r = 1;
	q = 1;
	while (g == 1) {
		x = y;
		for (int i = 0; i < r; ++i) {
			y = ( (y*y) % N +c ) % N;
		}
		k = 0;
		while (k < r && g == 1) {
			ys = y;
			min_var = min(m, r-k);
			for (int i = 0; i < min_var; ++i) {
				y = ( (y*y) % N + c ) % N;
				q = q * ( abs(x-y) ) % N;
			}
			g = gcd(q,N);
			k = k + m;
		}
		r *= 2;
	}
	if (g == N) {
		while (true) {
			ys = ( (ys * ys) % N + c ) % N;
			g = gcd( abs(x-ys), N);
			if (g > 1) {break;}
		}
	}
	return g;

}

// returns num, lower_bound <= num <= upper_bound
int getRandInt(int lower_bound, int upper_bound) {
	return rand() % upper_bound + lower_bound;
}

// Not needed in actual code
int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}