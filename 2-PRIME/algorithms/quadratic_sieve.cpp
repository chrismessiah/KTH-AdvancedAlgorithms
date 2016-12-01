#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

#include <stdint.h>
#include <gmp.h>
#include <gmpxx.h>

#include "matrix.h"

using namespace std;

mpz_class quadratic_sieve(mpz_class in);
mpz_class get_lower_base_bound(mpz_class factor_input);
vector<mpz_class> get_factor_base_vector(mpz_class N, mpz_class bound);
mpz_class power_fn(int base, mpz_class power);
mpz_class power_fn(int base, int power);

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
  while (mpz_legendre(z.get_mpz_t(),k.get_mpz_t()) != -1) {
    z += 1;
  }

  mpz_powm(c.get_mpz_t(), z.get_mpz_t(), q.get_mpz_t(), k.get_mpz_t());
  mpz_powm(r.get_mpz_t(), n.get_mpz_t(), mpz_class((q+1)/2).get_mpz_t(), k.get_mpz_t());
  mpz_powm(t.get_mpz_t(), n.get_mpz_t(), q.get_mpz_t(), k.get_mpz_t());
  m = s;

  int i;
  mpz_class temp_e, pow_temp, b, pow_temp2;
  while (t % k != 1) {
    i = 1;
    while(true) {
      pow_temp = power_fn(2,i);
      mpz_powm(temp_e.get_mpz_t(), t.get_mpz_t(), pow_temp.get_mpz_t(), k.get_mpz_t());
      if (temp_e != 1) {break;}
      i += 1;
    }

    pow_temp2 = power_fn(2, mpz_class(m - i - 1));
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
  for (int i = 0; i < vector_size; ++i) {
    temp_base = base_vector[i];
    N_reduced = N % temp_base;

    pair<mpz_class, mpz_class> tonelli_res = tonelliShanks(N_reduced, temp_base);

    index_1[i] = (((tonelli_res.first - sqrtN) % temp_base) + temp_base) % temp_base;
    index_2[i] = (((tonelli_res.second - sqrtN) % temp_base) + temp_base) % temp_base;
  }







  int range = 65536;
  int start, end;
  start = 0;
  end = range;

  vector<mpz_class> smooth;
  vector<int> l_approx(range, 0);
  mpf_class estimate;
  estimate = 0;
  mpz_class next_estimate;
  next_estimate = 1;
  mpz_class a;
  
  vector<vector<mpz_class> > smoothFactors;

  mpz_class temp_q;
  while (smooth.size() < vector_size + 15) {
    a = start;
    for (int i = 1, a = start + 1; i < end; ++i) {
      if (next_estimate < a+1) {
        temp_q = (a + sqrtN) * (a + sqrtN) - N;
        estimate = mpz_sizeinbase(temp_q.get_mpz_t(), 2);    // ~log_2(Q)
        next_estimate *= 1.8;
        next_estimate += 1;
      }
      l_approx[i] = estimate.get_si();
      a += 1;
    }

    mpz_class p_temp;
    for (int i = 0; i < vector_size; ++i) {
      p_temp = base_vector[i];
      double p_temp_d = p_temp.get_d();
      double p_temp_d_log = log(p_temp_d)/log(2);

      while (index_1[i] < end) {
        l_approx[mpz_class(index_1[i] - start).get_ui()] = l_approx[mpz_class(index_1[i] - start).get_ui()] - p_temp_d_log;
        index_1[i] = index_1[i] + p_temp;
      }
      if (p_temp == 2){ continue; }
      while (index_2[i] < end) {
        l_approx[mpz_class(index_2[i] - start).get_ui()] = l_approx[mpz_class(index_2[i] - start).get_ui()] - p_temp_d_log;
        index_2[i] = index_2[i] + p_temp;
      }
    }

    mpz_class temp_logger;
    temp_logger = base_vector[base_vector.size()-1];
    double thresh = log( temp_logger.get_d() )/log(2);
    mpz_class a2, q_temp2;
    a2 = start;
    vector<mpz_class> temp_factors_2_list;
    for (int i = 0; i < range; ++i) {
      if (fabs(l_approx[i]) < thresh) {
        q_temp2 = (a2 + sqrtN) * (a2 + sqrtN) - N;
        for (int j = 0; j < vector_size; ++j) {
          mpz_class p;
          p = base_vector[j];
          while (q_temp2 % p == 0) {
            q_temp2 /= p;
            temp_factors_2_list.push_back(j);
          }
        }
        if (q_temp2 == 1) {
          smoothFactors.push_back(temp_factors_2_list);
          smooth.push_back(a);
        }
        if (base_vector.size() + 25 <= smooth.size()) {break;}
      }
      a2 += 1;
    }
    start += range;
    end += range;
  }

  vector<mpz_class> factorBase = base_vector;

  Matrix M(factorBase.size(), smoothFactors.size() + 1);
  for (int i = 0; i < smoothFactors.size(); ++i) {
    for (int j = 0; j < smoothFactors[i].size(); ++j) {
      int temp_123 = smoothFactors[i][j].get_ui();
      M(temp_123, i).flip();
    }
  }

    /*
     * Step 3.2
     *
     * Reduce the matrix to row echelon form and solve it repeatedly until a factor
     * is found.
     */
  M.reduce();
  mpz_class a3;
  mpz_class b3;

  do {
    std::vector<uint32_t> x = M.solve();

    a3 = 1;
    b3 = 1;

        /*
         * Calculate b = product(smooth[i] + sqrt(N)).
         *
         * Also calculate the the power of each prime in a's decomposition on the
         * factor base.
         */
    std::vector<uint32_t> decomp(factorBase.size(), 0);
    for (uint32_t i = 0; i < smoothFactors.size(); ++i) {
      if (x[i] == 1) {
        for(uint32_t p = 0; p < smoothFactors[i].size(); ++p)
          ++decomp[smoothFactors[i][p].get_ui()];
        b3 *= (smooth[i] + sqrtN);
      }
    }

        /*
         * Calculate a = sqrt(product(factorBase[p])).
         */
    for(uint32_t p = 0; p < factorBase.size(); ++p) {
      for(uint32_t i = 0; i < (decomp[p] / 2); ++i)
        a3 *= factorBase[p];
    }

        // a = +/- b (mod N) means we have a trivial factor :(
  } while (a3 % N == b3 % N || a3 % N == (- b3) % N + N);


    /************************************
     *                                  *
     * STAGE 4: Success!                *
     *                                  *
     ***********************************/

  mpz_class factor;
  mpz_gcd(factor.get_mpz_t(), mpz_class(b3 - a3).get_mpz_t(), N.get_mpz_t());

  return factor;




}

vector<mpz_class> get_factor_base_vector(mpz_class N, mpz_class bound) {
  mpz_class temp;
  vector<mpz_class> bases;
  vector<bool> mask(bound.get_ui()+1,false);
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

mpz_class power_fn(int base, int power) {
  mpz_class temp;
  temp = 0;
  for (int i = 0; i < power; ++i) {
    temp += base * power;
  }
  return temp;
}

mpz_class power_fn(int base, mpz_class power) {
  mpz_class temp;
  temp = 0;
  for (int i = 0; i < power; ++i) {
    temp += base * power;
  }
  return temp;
}


