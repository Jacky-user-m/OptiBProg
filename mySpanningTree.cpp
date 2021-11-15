#include "mySpanningTree.h"

struct {
    bool operator()(std::pair<Edge,unsigned int> p1, std::pair<Edge,unsigned int> p2) const{
        return p1.second < p2.second;
    }
}sort_pred;
std::vector<Edge> my_spanning_tree(const Graph &g) {
  std::vector<Edge> spanning_tree;
  std::vector<std::pair<Edge, unsigned int>> temp;
  int num_vertices = boost::num_vertices(g);
  int co_list[num_vertices];
  for(int i=0;i<num_vertices;i++){
    co_list[i]=i;
  }
  EdgeIterator ei, ei_end;
  constEdgeWeightPropertyMap weight = get(boost::edge_weight, g);

  for (std::tie(ei, ei_end) = boost::edges(g); ei != ei_end; ++ei){
    temp.push_back(std::make_pair(*ei, boost::get(weight, *ei)));
  }
  std::sort(temp.begin(),temp.end(),sort_pred);
  for(auto it = temp.begin(); it != temp.end(); it++){
    if(co_list[boost::source(it->first,g)] != co_list[boost::target(it->first,g)]){
      int bigger,smaller = -1;
      if(co_list[boost::source(it->first,g)]>co_list[boost::target(it->first,g)]){
        bigger = co_list[boost::source(it->first,g)];
        smaller = co_list[boost::target(it->first,g)];
      }
      else{
        bigger = co_list[boost::target(it->first,g)];
        smaller = co_list[boost::source(it->first,g)];
      }
      for (auto i = 0; i < num_vertices; i++){
        if(co_list[i]==bigger){
          co_list[i] = smaller;     
        }
      }
      spanning_tree.push_back(it->first);
    }
  }
  return spanning_tree;
}
