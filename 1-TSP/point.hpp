#ifndef POINT
#define POINT

class Point {
  public:
    double x;
    double y;
    Point(string * input);
};

Point::Point(string * input) {
  string::size_type sz;
  x = stod(*input, &sz);
  y = stod( (*input).substr(sz) );
}

#endif
