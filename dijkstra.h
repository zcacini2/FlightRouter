#pragma once

#include <iterator>
#include <queue>
#include "Graph.h"
#include "Node.h"
#include "Edge.h"

using namespace std;

class dijkstra {
  public:

    dijkstra();
    dijkstra(Graph * graph, Node * start, Node * end);
      /* dijkstra constructor. The constructor takes graph and two nodes:
      first node is starting point(source) and second node is ending point (destination)
      */


    void shortestPath(Graph * graph, int src);
    int minDistance(int dist[], bool sptSet[]);

  private:
      Graph * graph_;
      Node * start_;
      Node * end_;
      //size = total number of vertices
      int size_;
}
