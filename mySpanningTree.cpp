#include "mySpanningTree.h"

std::vector<Edge> my_spanning_tree(const Graph &g) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<Edge> spanning_tree;

    //Kruskal's algorithm
    struct {
    bool operator()(std::pair<Edge,unsigned int> p1, std::pair<Edge,unsigned int> p2) const{
        return p1.second < p2.second;
    }
    }sort_pred;
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
    if((int)spanning_tree.size() == num_vertices-1){break;} 

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

    // //Prim's algorithm
    // int num_vertices = boost::num_vertices(g);
    // std::vector<Vertex> temp;
    // VertexIterator vi,vi_end;
    // for(std::tie(vi,vi_end) = boost::vertices(g); vi != vi_end; ++vi){
    //     temp.push_back(*vi);
    // }

    // int v_distance[num_vertices];
    // std::vector<Vertex> v_back;
    // for(int i =0;i< num_vertices ;i++){
    //     v_distance[i]=std::numeric_limits<int>::max();
    //     v_back.push_back(0);
    // }

    // v_distance[0] = 0;

    // Vertex curr_vertex = temp.front();

    // for(int i = 0;i<num_vertices -1 ;i++){
    //     auto neighbours = boost::adjacent_vertices(curr_vertex,g);
    //     for(auto next_vertex : make_iterator_range(neighbours)){
    //         if(v_distance[next_vertex] > (int) boost::get(boost::edge_weight,g,boost::edge(curr_vertex,next_vertex,g).first)){
    //             v_distance[next_vertex] = boost::get(boost::edge_weight,g,boost::edge(curr_vertex,next_vertex,g).first);
    //             v_back[next_vertex] = curr_vertex;
    //         }
    //     }
    //     int curr_min_index = 0;
    //     int curr_min_distance = std::numeric_limits<int>::max();

    //     for(int k=0; k<num_vertices; k++){
    //         if(v_distance[k] != 0 && v_distance[k]<curr_min_distance){
    //             curr_min_distance = v_distance[k];
    //             curr_min_index = k;
    //         }
    //     }
    //     auto edge = boost::edge(v_back[temp[curr_min_index]],temp[curr_min_index],g).first;
    //     spanning_tree.push_back(edge);

    //     v_distance[curr_min_index] = 0;
    //     curr_vertex = temp[curr_min_index];
    // }


    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: "
            << duration.count() << " microseconds" << std::endl;
    return spanning_tree;
}
