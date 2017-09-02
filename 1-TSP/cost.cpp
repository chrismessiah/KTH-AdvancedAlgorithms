#include "distance.hpp"

// We don't need any pointers here, let's just return the total
// distance aka cost.
double cost(vector<Point> points, vector<int> tour) {
  int n = points.size();  // Get the size
  double tourCost = 0;

  for (int i = 1; i < n; i++) {
    double dist = distance(points[tour[i]], points[tour[i-1]]);
    tourCost += dist;
  }
  return tourCost;
}
