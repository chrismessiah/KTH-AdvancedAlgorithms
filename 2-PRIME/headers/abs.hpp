#ifndef ABS
#define ABS

int absolute(int x);

int absolute(int x) {
  return (x >= 0) ? x : x*(-1);
}

#endif
