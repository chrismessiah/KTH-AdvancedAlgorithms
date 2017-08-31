#ifndef DISTANCE
#define DISTANCE

void distance(long * result, Point * p1, Point * p2);

void distance(long * result, Point * p1, Point * p2) {
  *result = round(sqrt( ((*p1).x-(*p2).x)*((*p1).x-(*p2).x) + ((*p1).y-(*p2).y)*((*p1).y-(*p2).y) ));
}

#endif
