#include "dijkstra.h"
#include "graph.h"
#include <vector>
#include <stack>
#include <queue>
using std::unordered_map;
using namespace std;
typedef pair<double, int> distanceToNode;

struct NodeDistance{
}

dijkstra::dijkstra(Graph * graph, Node * start, Node * end){
  graph_ = graph;
  start_ = start;
  end_ = end;
}

vector<Node> dijkstra::shortestPath(Graph * graph, Node * start, Node * end){
    //struct for comparison function of priority queue
    struct CompareDistance{
      bool operator()(std::pair<Node, double> const & a, std::pair<Node, double> const & b){
        //return true if a is bigger than b
        // ensures lower distances are prioritized in a queue
        return a.second> b.second;
      }
    };

    //retrieve all the nodes and edges from graphs
    vector<Node> nodes = graph.getNodes();
    vector<Edge> edges = graph.getEdges();

    //size = number of all nodes(vertices) in graph
    int size = nodes.size();

    std::unordered_map<Node, double> distances; // retrieve distance values for each node
    std::unordered_map<Node, Node> routes_;    // initialize a route that records node->its previous node

    //initialize a priority queue of node-distance pair
    typedef std::priority_queue<std::pair<Node, int>, vector<std::pair<Node, int>>,
    priority_queue<distanceToNode, vector<distanceToNode>, greater<distanceToNode>> pq;
    pq q;
    std::set<Node> visited; //initialize set 'visited' to chech whether this nodes are visited

    //check if there's adjacent nodes from starting node
    list<Node> adjacent = Node.neighbors();
    if(adjacent.empty()){
      return vector<Node>(); //return empty vector if there's no adjacent node
    }

    //initialize edges in distance map to be large enough
    for(auto v: nodes) {
      distance[v] = 9999999;
    }

    //set distances of starting point to be zero
    distances[start] = 0;
    q.push(std::pair<Node,double>(start, 0));

    //loop until we reach destination
    while (q.top().first != end && !q.empty()){
      std::pair<Node, double> curr = q.top(); //get the next pair from priority_queue
      Node curr_node = curr.first;
      q.pop();

      //mark current node as visited
      routes_.insert(curr_node);

<<<<<<< HEAD
      list<Node> neighbors = curr_node.neighbors(); // get all adjacent nodes

      for (Node neighbor : neighbors){
        if (visited.find(neighbor) == visited.end()){ // if there's no node neighbor in visited
          double dist = distances[curr_node] + curr_node.getDistance(neighbor)
=======
      vector<Node> neighbors = curr_node.neighbors(); // get all adjacent nodes

      for (Node neighbor : neighbors){
        if (visited.find(neighbor) == visited.end()){ // if there's no node neighbor in visited
          double dist = distances[curr_node] + Something_we_have_to_solve//stuck: how can I get distance of specific edge from two vertex?
>>>>>>> 30d0912ea20226fba177a31a3b931cbb83693ca6
          if (dist <= distances[neighbor]) {
            distances[neighbor] = dist;
            routes_[neighbor] = curr_vertex;
            q.push(std::pair<Node, double>(neighbor, dist));
          }
        }
      }
    }

    if(routes_.find(destination) == routes_.end()){ // if no path exists
      return vector<Node>();                          //return empty vector
    }

    //backtracing the path from routes_
    vector<Node> path;
    Node cur = destination;
    while (cur != start) {
      path.push_back(cur);
      curr = routes_[curr];
    }
    path.push_back(source);
    std::reverse(path.begin(), path.end());
    return path;
}
