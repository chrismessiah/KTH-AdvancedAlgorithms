void quadratic_sieve() {

  // check if we even need qs
  if (::factor_input == 1) {
    ::found_last_prime = true;
    return;
  }

  // inital perfect square, cube, ... test. No need to check more than to power
  // of 6 since we already have checked the first 19k primes and the highest is
  // a 100 bit nuber
  for (int power = 2; power <= 6; ++power) {
    perfect_form_test(power);
  }

  //mpz_class foo = sqrt(::factor_input);
  //foo += 1;
}

void get_factor_base_limit() {
  double log_N, log_log_N;
  mpf_class f_N, e;
  e = "2.71828182845904523536028747135266249775724709369995";
  f_N = ::factor_input;
  
  log_N = log(f_N.get_d());                                   //log_N = log(N)
  log_log_N = log(log_N);                                     //log_log_N = log(log(N))
  f_N = mpf_class(log_N) * mpf_class(log_log_N);              //f_N = log(N) * log(log(N))
  f_N = ( sqrt(f_N) )/2;                                      //f_N = sqrt(f_N)/2    
  mpf_pow_ui(f_N.get_mpf_t(), e.get_mpf_t(), f_N.get_ui());   //f_N = e^f_N

  mpz_class base_mpz;
  base_mpz = round(f_N.get_d());
  cout << "factor base: " << base_mpz << "\n";
}