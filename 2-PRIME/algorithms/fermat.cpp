#include <time.h>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <cmath>     /* srand, rand */
using namespace std;

int fermat(int N);

int main() {
	int in = 1555;
	int res;

	while (in != 1) {
		res = fermat(in);
		if (res == 1) {break;} 	// will cause infinite loops otherwise
		in /= res;
		cout << res << "\n";
	}
	cout << "DONE" << "\n";
	return 0;
}

int fermat(int N) {
	int a, b2, b2_root, factor;
	a = ceil(sqrt(N));
	b2 = a * a - N;
	b2_root = sqrt(b2);
	while (b2_root*b2_root != b2) {
		a = a + 1;
		b2 = a * a - N;
		b2_root = sqrt(b2);
	}
	factor = a - b2_root;
	return factor; 
}


