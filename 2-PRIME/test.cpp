
#include "headers/pollard_rho.hpp"
//#include "headers/brent_rho.hpp" // not working :(

#include "headers/abs.hpp"
#include "headers/gcd.hpp"
#include "headers/min.hpp"
#include "headers/random.hpp"

#include <iostream>

void factor_this(int num);

int main() {
  int number = 974069;
  factor_this(number);
  return 0;
}

void factor_this(int num) {
  int a = rho(num);
  if (a == 0) {
    std::cout << num << "\n";
  } else {
    factor_this(num/a);
    factor_this(a);
  }
}
