#include "MyMaxFlow.h"


#include <boost/property_map/property_map.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

unsigned int my_maxflow(DiGraph &g, const DiVertex &s, const DiVertex &t) {

  unsigned int flow = 0;
  //bool flag = true;
  
  // EdgeCapacityMap capacity{get(boost::edge_capacity, g)};
  // EdgeResidualCapacityMap res_capacity{get(boost::edge_residual_capacity, g)};
  // EdgeReverseMap rev{get(boost::edge_reverse, g)};
  // EdgeWeightMap weight{get(boost::edge_weight, g)};
  
  
  
    
  while (true){
    std::vector<DiVertex> p(num_vertices(g));
    std::vector<unsigned int> d(num_vertices(g));
    //find shortest path in residualgraph
    boost::dijkstra_shortest_paths(g, s,
    predecessor_map(boost::make_iterator_property_map(p.begin(), 
                    get(boost::vertex_index, g))).distance_map(boost::make_iterator_property_map(d.begin(), 
                    get(boost::vertex_index, g))));
    //if there is no path from s to t in res-graph
    if((p[t] ==t) || (d[t]==0)){
      break;
    }
    //agumenting this path
    //1.Storage path
    std::vector<DiVertex> path;
    DiVertex curr = t;
    while (curr != s)
    {
      path.insert(path.begin(),curr);
      curr = p[curr];
    }
    //2.find the minimal capacity in this path
    std::vector<unsigned int> path_capacity;
    for(int i =0;i != sizeof(path)/sizeof(DiVertex) ;i++){
      path_capacity.push_back(d[i]);
    }
    int min_path = std::numeric_limits<int>::max();
    for(auto it = path_capacity.begin();it != path_capacity.end();it++){
      if((int)*it< min_path ){
        min_path=*it;
      }
    }
    //3.agumenting by min_path
    for(int i = 0;i<(int)sizeof(path)/(int)sizeof(DiVertex)-1;i++){
      boost::put(boost::edge_weight,g,boost::edge(path[i],path[i+1],g).first,path_capacity[i]-min_path);
      //boost::put((unsigned int)min_path,g,path[i+1],path[i]);
      if(boost::edge(path[i],path[i+1],g).second){
        boost::put(boost::edge_weight,g,boost::edge(path[i+1],path[i],g).first,
        (boost::get(boost::edge_weight,g,boost::edge(path[i+1],path[i],g).first)+min_path));
      }
      else{
        boost::add_edge(path[i+1],path[i],g);
        boost::put(boost::edge_weight,g,boost::edge(path[i+1],path[i],g).first,min_path);
      }
    }
    flow += min_path;
  } 
  return flow;
}
