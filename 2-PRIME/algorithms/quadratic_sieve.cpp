#include <time.h>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <cmath>     /* srand, rand */
using namespace std;

mpz_class quadratic_sieve(mpz_class in);
mpz_class get_lower_base_bound(mpz_class factor_input);
vector<mpz_class> get_factor_base_vector(mpz_class N, mpz_class bound);

int main() {
  mpz_class in, res;
  in = 1555;

  while (in != 1) {
    res = quadratic_sieve(in);
    if (res == 1) {break;}  // will cause infinite loops otherwise
    in /= res;
    cout << res << "\n";
  }
  cout << "DONE" << "\n";
  return 0;
}

pair<mpz_class, mpz_class> tonelliShanks(mpz_class n, mpz_class k) {
  if (k == 2){return make_pair(n, n);}
  mpz_class q,s,z;
  q = k-1;
  s = 0;
  while (q % 2 == 0) {
    s += 1;
    q = q / 2;
  }
  z = 2;

  mpz_class c,r,t,m;
  while (mpz_legendre(z,k) != -1) {
    z += 1;
  }

  mpz_powm(c.get_mpz_t(), z.get_mpz_t(), q.get_mpz_t(), k.get_mpz_t());
  mpz_powm(r.get_mpz_t(), n.get_mpz_t(), ((q+1)/2).get_mpz_t(), k.get_mpz_t());
  mpz_powm(t.get_mpz_t(), n.get_mpz_t(), q.get_mpz_t(), k.get_mpz_t());
  m = s;

  mpz_class i, temp_e, pow_temp, b, pow_temp2;
  while (t % k != 1) {
    i = 1;
    while(true) {
      pow_temp = pow(2,i);
      mpz_powm(temp_e.get_mpz_t(), t.get_mpz_t(), pow_temp.get_mpz_t(), k.get_mpz_t());
      if (temp_e != 1) {break;}
      i += 1;
    }

    pow_temp2 = pow(2, M - i - 1);
    mpz_powm(b.get_mpz_t(), c.get_mpz_t(), pow_temp2.get_mpz_t(), k.get_mpz_t());

    r = r * b % k; 
    t = t * b * b % k;
    c = b * b % k;
    m = i;
  }

  return make_pair(r, k-r);
}

mpz_class quadratic_sieve(mpz_class N) {
  mpz_class bound, sqrtN;

  bound = get_lower_base_bound(N);
  sqrtN = sqrt(N);
  vector<mpz_class> base_vector = get_factor_base_vector(N, bound);
  
  mpz_class temp_base, N_reduced;
  int vector_size = base_vector.size();
  vector<mpz_class> index_1(vector_size);
  vector<mpz_class> index_2(vector_size);
  for (mpz_class i = 0; i < vector_size; ++i) {
    temp_base = factorBase[i];
    N_reduced = N % p;

    pair<mpz_class, mpz_class> tonelli_res = tonelliShanks(N_reduced, temp_base);

    index_1[i] = (((tonelli_res.first - sqrtN) % temp_base) + temp_base) % temp_base;
    index_2[i] = (((tonelli_res.second - sqrtN) % temp_base) + temp_base) % temp_base;
  }


  int range = 65536;
  mpz_class start, end;
  start = 0;
  end = range;

  vector<mpz_class> smooth;
  vector<vector<mpz_class> > smoothFactors;
  vector<mpf_class> l_approx(range, 0);
  mpf_class estimate;
  estimate = 0;
  mpz_class next_estimate;
  next_estimate = 1;

  while () {
    
  }
}

vector<mpz_class> get_factor_base_vector(mpz_class N, mpz_class bound) {
  mpz_class temp;
  vector<mpz_class> bases;
  vector<bool> mask(bound+1,false);
  for (int i = 2; i < bound; ++i) {
    if (mask[i]) {
      temp = i;
      if (mpz_legendre(N.get_mpz_t(), temp.get_mpz_t()) == 1) { // Checks if Legendre symbol gives N quadr residue mod temp
        bases.push_back(i);
      }

      for (mpz_class i2 = i; i2 < bound+1; i2 += i) {mask[i] = true;}

    }
  }
  return bases;
}

mpz_class get_lower_base_bound(mpz_class factor_input) {
  int c = 2;
  double logN, loglogN;
  mpf_class temp, e;
  mpz_class b;
  e = "2.71828182845904523536028747135266249775724709369995";
  temp = factor_input;
  
  logN = log(temp.get_d());                                     // logN = log(N)
  loglogN = log(logN);                                          // loglogN = log(log(N))
  temp = mpf_class(logN) * mpf_class(loglogN);                  // temp = log(N) * log(log(N))
  temp = ( sqrt(temp) )/2;                                      // temp = sqrt(temp)/2    
  mpf_pow_ui(temp.get_mpf_t(), e.get_mpf_t(), temp.get_ui());   // temp = e^temp
  temp *= c;                                                    // temp  = temp*2
  temp = round(temp.get_d());
  b = temp;
}




