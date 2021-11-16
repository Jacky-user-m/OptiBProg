#include "myShortestPath.h"
typedef std::pair<Vertex,int> V_and_distance;
struct CmpByValueGreat{
  bool operator()(const V_and_distance &lhs,const V_and_distance &rhs){
    return lhs.second < rhs.second ;
  }
};


std::vector<Vertex> my_shortest_path(const Graph &g, const Vertex &startVertex,
                                     const Vertex &endVertex) {
  std::vector<Vertex> path;
  // compute a shortest path between startVertex and endVertex and save it in
  // the vector >>path<<
  
  //Dijstra
  int num_vertices = boost::num_vertices(g);

  std::priority_queue<V_and_distance,std::vector<V_and_distance>,CmpByValueGreat> Dijstra;

  std::vector<Vertex> pred_vertex(num_vertices);

  
  int distance[num_vertices];
  for(int i = 0;i<num_vertices;i++){
    distance[i] = std::numeric_limits<int>::max();
  }

  std::vector<Vertex> V_all;
  VertexIterator vi,vi_end;
  for(std::tie(vi,vi_end) = boost::vertices(g); vi != vi_end; ++vi){
      V_all.push_back(*vi);
  }

  //Inizialisirung
  distance[(int)startVertex] = 0;


  Dijstra.push(std::make_pair(startVertex,0));
  pred_vertex[(int)startVertex] = startVertex;

  std::cout<<"hier!!!!!!!!!!!!!"<<std::endl;
  while (!Dijstra.empty()){
    auto curr = Dijstra.top();
    Dijstra.pop();
    if(curr.first == endVertex){break;}
    auto out_edges = boost::out_edges(Dijstra.top().first,g);
    for(auto adj_edges : make_iterator_range(out_edges)){
      if(curr.second
      + (int) boost::get(boost::edge_weight,g,adj_edges)
      < distance[boost::target(adj_edges,g)]){
        
        distance[boost::target(adj_edges,g)] = curr.second
        + (int) boost::get(boost::edge_weight,g,adj_edges);
        pred_vertex[boost::target(adj_edges,g)] = Dijstra.top().first;
        Dijstra.push(std::make_pair(boost::target(adj_edges,g),distance[boost::target(adj_edges,g)]));
      }    
    }
    //not_scanned_V.erase(not_scanned_V.begin()+(int)Dijstra.top().first);
  }
  
  std::cout<<"[";
  for(int i=0;i<(int)sizeof(pred_vertex);i++){
    std::cout<<pred_vertex[i]<<",";
  }
  std::cout<<"]"<<std::endl;


  // std::vector<Vertex> all_V;
  // VertexIterator v,v_end;
  // for(std::tie(vi,vi_end) = boost::vertices(g); vi != vi_end; ++vi){
  //     all_V.push_back(*vi);
  // }
  int look_for = (int)endVertex;
  while (look_for != (int)startVertex)
  {
    path.push_back(V_all[pred_vertex[look_for]]);
    look_for = pred_vertex[look_for];
  }

  // return path
  return path;
}
