#ifndef DISTANCE
#define DISTANCE
#include <math.h>

long distance(double * x1, double * x2, double * y1, double * y2);

long distance(double * x1, double * x2, double * y1, double * y2) {
  return round(sqrt( ( ((*x1) - (*x2)) * ((*x1) - (*x2)) ) + ( ((*y1) - (*y2)) * ((*y1) - (*y2)) ) ));
}

#endif
