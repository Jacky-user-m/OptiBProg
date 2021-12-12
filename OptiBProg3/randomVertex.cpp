#include "randomVertex.h"

#include <random>

#include <boost/graph/random.hpp>

std::pair<DiVertex, DiVertex> get_tuple_of_distinct_vertices(const DiGraph &g) {
  // generate random start and end vertex
  time_t seed = time(0);
  std::mt19937 RandomNumGen(seed++);
  DiVertex startVertex = random_vertex(g, RandomNumGen);
  DiVertex endVertex;
  do {
    endVertex = random_vertex(g, RandomNumGen);
  } while (startVertex == endVertex);
  return std::make_pair(startVertex, endVertex);
}
