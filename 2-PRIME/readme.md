# Installation of GMP

1. download gmp from https://gmplib.org/#DOWNLOAD and expand archive 
2. Open up a terminal and cd into the gmp-folder
3. Run `./configure --enable-cxx`
4. Run `make`
5. Run `make install`
6. cd into the project folder of lab2
7  Run `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib` 
8. compile `g++ gmp_test.cpp -lgmp -lgmpxx`
9. Run `./a.out` and see if you get any errors, otherwise ur good to go

# Troubleshooting

If you get _error while loading shared libraries: libgmpxx.so.4: cannot open shared object file: No such file or directory_ then try running `sudo ldconfig` (works only on linux)
