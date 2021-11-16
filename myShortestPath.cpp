#include "myShortestPath.h"

typedef std::pair<Vertex,int> V_and_distance;

std::vector<Vertex> my_shortest_path(const Graph &g, const Vertex &startVertex,
                                     const Vertex &endVertex) {
  std::vector<Vertex> path;
  // compute a shortest path between startVertex and endVertex and save it in
  // the vector >>path<<

  struct {
    bool operator()(std::pair<Vertex, int> p1, std::pair<Vertex, int> p2) const{
        return p1.second < p2.second;
    }
  }sort_pred;
  
  //Dijstra
  int num_vertices = boost::num_vertices(g);
  std::vector<V_and_distance> Dijstra;
  std::vector<int> pred_vertex(num_vertices);
  int distance[num_vertices];

  for(int i = 0;i<num_vertices;i++){
    distance[i] = std::numeric_limits<int>::max();
    pred_vertex[i] = -1;
  }

  std::vector<Vertex> V_all;
  VertexIterator vi,vi_end;
  for(std::tie(vi,vi_end) = boost::vertices(g); vi != vi_end; ++vi){
      V_all.push_back(*vi);
  }

  //Inizialisirung
  distance[(int)startVertex] = 0;

  Dijstra.push_back(std::make_pair(startVertex,0));
  pred_vertex[(int)startVertex] = startVertex;

  while (!Dijstra.empty()){
    auto curr = Dijstra[0];
    Dijstra.erase(Dijstra.begin());
    if(curr.first == endVertex){break;}
    auto out_edges = boost::out_edges(curr.first,g);
    for(auto adj_edges : make_iterator_range(out_edges)){
      if(curr.second + (int) boost::get(boost::edge_weight,g,adj_edges) < distance[boost::target(adj_edges,g)]){
        distance[boost::target(adj_edges,g)] = curr.second + (int) boost::get(boost::edge_weight,g,adj_edges);
        pred_vertex[boost::target(adj_edges,g)] = (int)curr.first;
        Dijstra.push_back(std::make_pair(boost::target(adj_edges,g),distance[boost::target(adj_edges,g)]));
      }    
    }
    std::sort(Dijstra.begin(),Dijstra.end(),sort_pred);
    
  }

  int look_for = (int)endVertex;
  path.push_back(V_all[endVertex]);
  while (look_for != (int)startVertex)
  {
    path.insert(path.begin(), V_all[pred_vertex[look_for]]);
    look_for = pred_vertex[look_for];
  }

  // return path
  return path;
}
