#include "mySpanningTree.h"

struct {
    bool operator()(std::pair<Edge,unsigned int> p1, std::pair<Edge,unsigned int> p2) const{
        return p1.second < p2.second;
    }
}sort_pred;

bool is_cycle(Edge edge,std::set<Vertex> set,Graph g){
    if(set.find(boost::source(edge,g)) != set.end() && set.find(boost::target(edge,g)) != set.end()){
      return true;
    }
    return false;
}

std::vector<Edge> my_spanning_tree(const Graph &g) {
  std::vector<Edge> spanning_tree;
  std::vector<std::pair<Edge, unsigned int>> temp;
  // compute a minimal spanning tree for g
  //TODO
  EdgeIterator ei, ei_end;
  constEdgeWeightPropertyMap weight = get(boost::edge_weight, g);

  for (std::tie(ei, ei_end) = boost::edges(g); ei != ei_end; ++ei){
    //std::cout<<*ei<<boost::get(weight, *ei)<<std::endl;
    temp.push_back(std::make_pair(*ei, boost::get(weight, *ei)));
  }

  // for(auto it = temp.begin(); it != temp.end(); it++){
  //   std::cout<<it->second<<std::endl;
  // }

  std::sort(temp.begin(),temp.end(),sort_pred);

  std::set<Vertex> verties;

  for(auto it = temp.begin(); it != temp.end(); it++){
      if(!is_cycle(it->first,verties,g)){
          spanning_tree.push_back(it->first);
          verties.insert(boost::source(it->first,g));
          verties.insert(boost::target(it->first,g));
          
      }
  }

  // std::cout<<"nach sort"<<std::endl;
  // int counter=0;
  // for(auto it = spanning_tree.begin(); it != spanning_tree.end(); it++){
  //   counter++;
  //   std::cout<<*it<<std::endl;
  //   std::cout<<counter<<std::endl;
  // }


  
  
  // return spanning tree
  return spanning_tree;
}
