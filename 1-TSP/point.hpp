#ifndef POINT
#define POINT

class Point {
  public:
    double x, y;
    Point(string input);
};

Point::Point(string input) {
  std::string::size_type sz;
  x = std::stod (input, &sz);
  y = std::stod (input.substr(sz));
}

#endif
