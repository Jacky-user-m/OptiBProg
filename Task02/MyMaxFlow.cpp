#include "MyMaxFlow.h"


#include <boost/property_map/property_map.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

unsigned int my_maxflow(DiGraph &g, const DiVertex &s, const DiVertex &t) {

  unsigned int flow = 0;

  
  EdgeCapacityMap capacity{get(boost::edge_capacity, g)};
  EdgeResidualCapacityMap res_capacity{get(boost::edge_residual_capacity, g)};
  EdgeReverseMap rev{get(boost::edge_reverse, g)};

  EdgeWeightMap weight{get(boost::edge_weight, g)};
  std::vector<DiVertex> p(num_vertices(g));
  std::vector<unsigned int> d(num_vertices(g));

  boost::dijkstra_shortest_paths(g, s,
  predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, g)))
            .distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, g))));
  
  while(true){
  }
  return flow;
}
