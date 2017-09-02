#ifndef DISTANCE
#define DISTANCE
#include <math.h>

double distance(Point p1, Point p2) {
  return sqrt( pow( p1.x - p2.x, 2) + pow( p1.y - p2.y, 2) );
}

double cost(vector<Point> points, vector<int> tour) {
  int n = points.size();  // Get the size
  double tourCost = 0;

  for (int i = 1; i < n; i++) {
    double dist = distance(points[tour[i]], points[tour[i-1]]);
    tourCost += dist;
  }
  return tourCost;
}

#endif
