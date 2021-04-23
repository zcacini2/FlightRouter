#include "dijkstra.h"
#include <vector>
#include "graph.h"

using namespace std;
typedef pair<double, int> distanceToNode;

struct NodeDistance{
}
dijkstra::dijkstra(Graph * graph, Node * start, Node * end){
  graph_ = graph;
  start_ = start;
  end_ = end;
}

int dijkstra::minDistance(int dist[], bool sptSet[], int numNodes){
  // Initialize min value
  int min = INT_MAX, min_index;

  for (int i = 0; i < numNodes; i++)
    if (sptSet[i] == false && dist[i] <= min)
        min = dist[i], min_index = i;

  return min_index;
}

void dijkstra::shortestPath(Graph * graph, Node * start, Node * end){
    //struct for comparison function of priority queue
    struct CompareDistance{
      bool operator()(std::pair<Node, double> const & a, std::pair<Node, double> const & b){
        //return true if a is bigger than b
        //this ensures lower distances are prioritized in a queue
        return a.second> b.second;
      }
    };

    //retrieve all the nodes and edges from graphs
    vector<Node> nodes = graph.getNodes();
    vector<Edge> edges = graph.getEdges();

    //size = number of all nodes(vertices) in graph
    int size = nodes.size();

    std::unordered_map<Node, double> distances; // retrieve distance values for each node
    std::unordered_map<Node, Node> traces;    // initialize a map that records node->its previous node

    //initialize a priority queue of node-distance pair
    typedef std::priority_queue<std::pair<Node, int>, vector<std::pair<Node, int>>,
    priority_queue<distanceToNode, vector<distanceToNode>, greater<distanceToNode>> pq;
    pq q;
    std::set<Node> visited; //initialize set 'visited' to chech whether this nodes are visited

    //check if there's adjacent nodes from starting node
    list<Node> adjacent = Node.neighbors();
    if(adjacent.empty()){
      return vector<Node>();
    }

    //initialize vertices in distance map to be large enough
    for(auto v: nodes) {
      distance[v] = 999999;
    }

    //set distances of starting point to be zero
    distances[start] = 0;
    q.push(std::pair<Node,double>(start, 0));
    while (q.top().first != end && !q.empty()){
      std::pair<Node, double> curr = q.top(); //get the next pair from priority_queue
      Node curr_node = curr.first;
      q.pop();

      //mark current node as visited
      traces.insert(curr_node);
      ///////////////////////////////needs to work from here//////////////////////////////////
    }

    }
}
