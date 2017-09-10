#ifndef CHRISTOFIDES
#define CHRISTOFIDES

#include <vector>
#include "matrix.hpp"

void find_minimum_spanning_tree(vector< vector<short> > (*adj_list), Matrix& graph);
short minimum_key_vertex(vector<long> (*keys), vector<bool> (*vertex_is_used));
void prefect_matching(vector<short> (*tour), Matrix& graph);
void find_odd_degrees(vector<short> (*odd_vertices), vector<short> (*tour), Matrix& graph);

void christofides(vector<short> (*tour), Matrix& dMatrix) {
  vector<  vector<short> > adjecency_list(inputLength, vector<short>(0));

  find_minimum_spanning_tree(&adjecency_list, dMatrix);
  prefect_matching(tour, dMatrix, &adjecency_list);
  // create an euler cycle which is the tour. After that the algorithm is complete
}

void prefect_matching(vector<short> (*tour), Matrix& graph, vector< vector<short> > (*adj_list)) {
  vector<short> odd_vertices;
  find_odd_degrees(&odd_vertices, adj_list);

  // create minimum-weight matching or perfect matching here on the set of nodes having an odd degree
}

void find_odd_degrees(vector<short> (*odd_vertices), vector< vector<short> > (*adj_list)) {
  for (short i = 0; i < inputLength; i++) {
    if ((*adj_list)[i].size() % 2 == 0) {continue;}
    odd_vertices.push_back(i);
  }
}

// the goal here is to generate an adjacency list
void find_minimum_spanning_tree(vector< vector<short> > (*adj_list), Matrix& graph) {
  vector<long> parent(inputLength);
  vector<long> keys(inputLength);
  vector<bool> vertex_is_used(inputLength);
  for (short i = 0; i < inputLength; i++) { keys[i] = 9999999; }

  keys[0] = 0;
  parent[0] = -1;

  short index;
  for (short i = 0; i < inputLength-1; i++) {
    index = minimum_key_vertex(&keys, &vertex_is_used);
    vertex_is_used[index] = true;
    for (short j = 0; j < inputLength; j++) {
      if (graph.get(index, j) && !vertex_is_used[j] && graph.get(index, j) < keys[j]) {
        parent[j] = index; // store MST vertices in tour
        keys[j] = graph.get(index, j);
      }
    }
  }
  for (short i = 0; i < inputLength; i++) {
    if (parent[i] == -1) {continue;}
    (*adj_list)[i].push_back(parent[i]);
    (*adj_list)[parent[i]].push_back(i);
  }
}

// pick the minimum key vertex from the not included vertices
short minimum_key_vertex(vector<long> (*keys), vector<bool> (*vertex_is_used)) {
  long minimum = 9999999;
  short index;
  for (short i = 0; i < inputLength; i++) {
    if (!((*vertex_is_used)[i]) && (*keys)[i] < minimum) {
      minimum = (*keys)[i];
      index = i;
    }
  }
  return index;
}

#endif
