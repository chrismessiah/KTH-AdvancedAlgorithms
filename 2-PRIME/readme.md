# Algorithms
Here are some algorithms that are useful. A section bellow goes through the uses for each algorithm.

* [Pollard's rho algorithm](https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm)
* [Brent's rho algorithm](http://comeoncodeon.wordpress. com/2010/09/18/pollard-rho-brent-integer-factorization/.)
* [Fermat's factorization method](https://en.wikipedia.org/wiki/Fermat%27s_factorization_method)
* [Dixon's factorization method](https://en.wikipedia.org/wiki/Dixon%27s_factorization_method)
* [Quadratic sieve](https://en.wikipedia.org/wiki/Quadratic_sieve)

### Pollard's rho

blablabla

### Brent's rho

blablabla

# Installation of GMP

1. download gmp from https://gmplib.org/#DOWNLOAD and expand archive
2. Open up a terminal and cd into the gmp-folder
3. Run `./configure --enable-cxx`
4. Run `make -j 3`
5. Run `make -j 3 install`
6. cd into the project folder of lab2
7. Run `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib`
8. compile `g++ gmp_test.cpp -lgmp -lgmpxx -std=c++11`
9. Run `./a.out` and see if you get any errors, otherwise ur good to go

# Troubleshooting

If you get _error while loading shared libraries: libgmpxx.so.4: cannot open shared object file: No such file or directory_ then try running `sudo ldconfig` (works only on linux)
