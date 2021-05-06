#include "Graph.h"
#include <vector>
#include <memory>
#include "Edge.h"
#include "readFromFile.hpp"
#include "Airports.h"
#include <queue>
#include <set>
#include <unordered_map>

using namespace std;

typedef pair<double, int> distanceToNode;

Graph::Graph() { }

Graph::~Graph() {

}

/**
 * Graph constructor. The constructor will take in the routes file. The routes file is a CSV containing the
 * following elements in order: Airline, Airline ID, Source airport, Source Airport (OpenFlights ID), Destination
 * Airport, Destination Airport (OpenFlights ID), CodeShare, Stops, and Equipment. The only values that are of
 * importance to us are the Source Airport (OpenFlights ID) and the Destination Airport (OpenFlights ID). Stops are
 * all 0 (direct flight) for the entire file.
 *
 * The goal of the constructor is to convert the CSV into a vector. Then, using this vector, we want to find the
 * two values of interest. With the two values of interest, we must build their nodes if they dont exist. Data
 * required for nodes are airport code, latitude, and longitude. These two values will be matched using the Airports
 * coder/decoder. The OpenFlights ID ends up  being simply the index of the vector for which it's information is
 * stored.
 *
 * So, if the nodes and edge exist, we do nothing for that line. If the nodes exist but not the edge, we must add
 * an edge. If neither the node or the edge exist, we must create the proper nodes (reference the Airport
 * coder/decoder) and add the edge to the adjacency list.
 *
 * @param filename name of the file to create the graph from
 */

Graph::Graph(const std::string & routesFile, const std::string & airportsFile) {

  std::string str = file_to_string(routesFile);

  Airports airports(airportsFile);

  nodes_.resize(airports.size());
  for (unsigned i = 0; i < airports.size(); i++) {
    nodes_[i] = new Node();
  }

  vector<string> line;  //create line vector
  stringstream s_stream(str); //create string stream from the string
  int sourceID, destID;
  bool areBothValid;

  while(s_stream.good()) {
    string row, substr;
    getline(s_stream, row, '\n'); //get first string delimited by new line
    stringstream row_stream(row);
    areBothValid = true;

    while (row_stream.good()) {
      getline(row_stream, substr, ',');
      substr.erase(std::remove( substr.begin(), substr.end(), '\"' ), substr.end()); //cleans quotations
      line.push_back(substr);
    }

    sourceID = stoi(line[3]); //OpenFlights ID of the source airport
    destID = stoi(line[5]); //OpenFlights ID of the destination airport

    Node* source;
    Node* dest;

    //std::cout << sourceID << " " << airports.latitude(sourceID) << std::endl;
    //std::cout << destID << " " << airports.latitude(destID) << std::endl;

    // Check if airport with sourceID is null in airports.
    if (airports.latitude(sourceID) == -1000) {
      areBothValid = false;
    }

    // Check if airport with destID is null in airports.
    if (airports.latitude(destID) == -1000) {
      areBothValid = false;
    }

    // If source node doesnt exist create, else set source equal to already built node
    if (areBothValid == true && nodes_[sourceID]->airportCode() == -1) {

      double sourceLat, sourceLng;

      sourceLat = airports.latitude(sourceID);
      sourceLng = airports.longitude(sourceID);

      Node* _source = new Node(sourceID, sourceLat, sourceLng);
      source = _source;

      nodes_[sourceID] = source;

    } else if (areBothValid == true) {
      source = nodes_[sourceID];
    }

    //If dest node doesnt exist create, else set dest equal to already built node
    if (areBothValid == true && nodes_[destID]->airportCode() == -1) {

      double destLat, destLng = 0.0;

      destLat = airports.latitude(destID);
      destLng = airports.longitude(destID);

      Node* _dest = new Node(destID, destLat, destLng);
      dest = _dest;

      nodes_[destID] = dest;

    } else if (areBothValid == true) {
      dest = nodes_[destID];
    }

    //Add edge if not there

    if (areBothValid == true && !source->areNeighbors(dest)) {
      Edge route(source, dest);
      edges_.push_back(route);

      source->addNeighbor(dest);
      dest->addNeighbor(source);
    }

    line.clear();

  }

  /*
  Functionality to add:
    - Handling null (\N) values (Delete from file?)
    - Parsing for invalid values
    - Check airport for valid airport
  */

}

/**
 * Method returning all nodes of a graph.
 */
vector<Node*> Graph::getNodes() {
  return nodes_;
}

/**
 * Method returning all edges of a graph
 */
vector<Edge> Graph::getEdges() {
  return edges_;
}

Node* Graph::getFirstNode() {
  return (nodes_.at(1));
}

double Graph::getDistance(int start, int end) {
  Node * start_node = nodes_[start];
  Node * end_node = nodes_[end];

  if (start_node->areNeighbors(end_node)) {
    return start_node->distance(end_node);
  }

  return 9999999;
}

/*
Graph::shortestPath is implementation of Dijkstra algorithm. Receives airportCode of starting airport and destination airport,
and returns vector of Node* which stores the shortest route between two airports.
*/
vector<Node*> Graph::shortestPath(int start, int end){

    //struct for comparison function of priority queue
    struct CompareDistance {
      bool operator()(std::pair<int, double> const & a, std::pair<int, double> const & b){
        //return true if a is bigger than b
        // ensures lower distances are prioritized in a queue
        return a.second > b.second;
      }
    };

    //size = number of all nodes(vertices) in graph
    int size = nodes_.size();

    std::unordered_map<int, double> distances_; // initialize distances_ which retrieve distance values from source for each node
    std::unordered_map<int, int> routes_;    // initialize a route that records node->its previous node (curr airport code, parent airport code)

    //initialize a priority queue of node-distance pair
    typedef std::priority_queue<std::pair<int, double>, vector<std::pair<int, double>>, CompareDistance> pq;
    pq q;
    std::set<int, greater<int>> visited; //initialize set 'visited' to chech whether this nodes are visited

    //getting nodes from airportcode, refactored from below
    Node* startNode = nodes_[start];
    Node* endNode = nodes_[end];

    //check if there's adjacent nodes from starting node
    list<Node*> adjacent = startNode->neighbors();
    if (adjacent.empty()) {
      return vector<Node*>(); //return empty vector if there's no adjacent node
    }

    //initialize edges in distance map to be large enough
    for (int i = 0; i < (int) nodes_.size(); i++) {
      distances_[i] = 9999999;
    }

    //set distances of starting point to be zero
    distances_[start] = 0;
    q.push(pair<int,double>(start, 0));  // Pushing a pair of airport code and distance to priority queue from source

    //loop until we reach destination
    while (q.top().first != end && !q.empty()){
      std::pair<int, double> curr = q.top(); //get the next pair from priority_queue
      int curr_node = curr.first;  // Airport code of current node
      q.pop();

      //mark current node as visited
      visited.insert(curr_node);

      list<int> neighbors = nodes_[curr_node]->neighbors_codes_(); // get all adjacent nodes

      for (int neighbor : neighbors) {
        if (visited.find(neighbor) == visited.end()) { //only proceed if node is not visited before

          Node* currentNode = nodes_[curr_node];
          Node* neighborNode = nodes_[neighbor];
          double dist = distances_[curr_node] + currentNode->distance(neighborNode);

          if (dist <= distances_[neighbor]) {
            distances_[neighbor] = dist;
            routes_[neighbor] = curr_node;

            q.push(std::pair<int, double>(neighbor, dist));

          }
        }
      }
    }

    if (routes_.find(end) == routes_.end()) { // if no path exists
      return vector<Node*>();                          //return empty vector
    }

    //backtracing the path from routes_
    vector<Node*> path;
    int curr = end;
    while (curr != start) {
      // Find node in nodes_
      Node* pathNode = nodes_[curr];
      path.push_back(pathNode);
      curr = routes_.at(curr);
    }

    path.push_back(startNode); // Push startNode
    std::reverse(path.begin(), path.end());
    return path;

}

Node* Graph::getNode(int airportCode) {
  return nodes_[airportCode];
}
