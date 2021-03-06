#include "types.h"

// Check whether the given mst is a proper minimal spanning tree for graph g
bool checkSpanningTree(const Graph &g, const std::vector<Edge> &mst);

// Check whether the given path is a shortest path in g
bool checkPath(const Graph &g, const Vertex &startVertex,
               const Vertex &endVertex, const std::vector<Vertex> &path);

// Check whether the steiner tree is valid
bool checkSteinerTree(Graph g, const std::vector<Edge> &steiner_tree,
                      const std::vector<Vertex> &terminals);
