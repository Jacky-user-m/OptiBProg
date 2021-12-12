#include <iostream>
#include <string>

#include "FootballBettingGameParser.h"
#include "MyBipartition.h"
#include "MyFootballBettingGame.h"
#include "MyMaxFlow.h"
#include "MyMaxWeightedMatching.h"
#include "check.h"
#include "randomVertex.h"
#include "readLgf.h"
#include "types.h"

/**
 *
 *
 * @param args args[0] is the number of the exercise (decides the algorithm
 * which is to be executed) args[1] is the file to parse
 */
int main(int argc, char **argv) {

  std::cout << "Which algorithm would you like to test "
               "(MaxFlow, Bipartition, BipartiteMatching, Football)?"
            << std::endl;

  std::string arg0;
  std::cin >> arg0;

  if (arg0 == "Bipartition") {
    std::cout << "Which instance would you like to solve (1,2,3,4)?"
              << std::endl;
    std::string arg1;
    std::cin >> arg1;

    std::cout << "Computing Bipartitioning of Graph " << arg1 << ":"
              << std::endl;

    Graph g{readGraphFromFile("graph" + arg1 + ".lgf")};

    // compute bipartition
    Partition_variant res{my_bipartition(g)};
    checkBiPartition(g, res);

  } else if (arg0 == "BipartiteMatching") {

    std::cout << "Which instance would you like to solve (1,2,3,4)?"
              << std::endl;
    std::string arg1;
    std::cin >> arg1;
    std::cout << "Computing Bipartite Matching of Graph " << arg1 << ":"
              << std::endl;
    Graph g{readGraphFromFile("graph" + arg1 + ".lgf")};

    // compute matching
    std::vector<Vertex> myMatching{my_max_weighted_matching(g)};
    checkMaxWeightedMatching(g, myMatching);

  } else if (arg0 == "Football") {
    std::cout << "Computing Optimal Betting:" << std::endl;

    std::string filename = "Season12.txt";
    std::vector<Matchday> season{read_football_instance(filename)};
    std::map<Team, unsigned int> myBet{my_football_betting(season)};

    checkBettingGame(myBet, season);

  } else if (arg0 == "MaxFlow") {

    std::cout << "Which instance would you like to solve (1,2,3,4)?"
              << std::endl;
    std::string arg1;
    std::cin >> arg1;
    std::cout << "Computing Maximum Flow of Graph " << arg1 << ":" << std::endl;
    DiGraph g{readDiGraphFromFile("graph" + arg1 + ".lgf")};
    // TODO DiGraph has no deep copy constructor
    DiGraph gOrg{readDiGraphFromFile("graph" + arg1 + ".lgf")};

    // generate random source and target vertex
    std::pair<DiVertex, DiVertex> stVertices{get_tuple_of_distinct_vertices(g)};

    // compute maxflow
    unsigned int flow{my_maxflow(g, stVertices.first, stVertices.second)};

    // check
    bool res{checkMaxFlow(g, gOrg, stVertices.first, stVertices.second, flow)};
    std::cout << "RESULT: " << res << std::endl;
  }
}
