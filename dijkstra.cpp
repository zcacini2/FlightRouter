#include "dijkstra.h"
#include <vector>
#include "graph.h"

uing namespace std;

dijkstra::dijkstra(Graph * graph, Node * start, Node * end){
  graph_ = graph;
  start_ = start;
  end_ = end;
  vector<Edge> edges = graph.getEdges();
  size_ = edges.size();
}

int dijkstra::minDistance(int dist[], bool sptSet[]){
  
}
void dijkstra::shortestPath(Graph * graph, int src){

    vector<Edge> edges = graph.getEdges();
    int size = edges.size();
    //output array. dist[i] holds shortest distance from src to i
    int dist[size];
    // sptSet[i] will be true if vertex is included in shortest path tree or
    //shortest distance from i to source is finalized
    bool sptSet[size];
    for (int i = 0; i < size; i++) {
      dist[i] = int_MAX; sptSet[i] = false;
    }
    // initialize distance from source itself as always 0
    dist[src] = 0;

    for (int count = 0; count < size - 1; count++) {

    }

}
