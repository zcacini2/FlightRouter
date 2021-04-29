#pragma once

#include <iterator>
#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <stack>
#include <queue>
#include <unordered_map>
using std::unordered_map;
using namespace std;

class dijkstra {
  public:

    dijkstra();
    dijkstra(Graph * graph, Node * start, Node * end);
      /* dijkstra constructor. The constructor takes graph and two nodes:
      first node is starting point(source) and second node is ending point (destination)
      */
    vector<Node> shortestPath(Graph * graph, Node *start, Node * end);
      /* dijkstra function. this function takes graph and two Nodes
      and return shortest distance from starting point to the end.
      */

  private:
      Graph * graph_;
      Node * start_;
      Node * end_;
      //size = total number of vertices
      int size_;
};
