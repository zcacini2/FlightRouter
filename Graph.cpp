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

  /*
  for (unsigned long i = 0; i < nodes_.size(); i++) {
    if (nodes_[i] != nullptr) {
      //delete nodes_[i];
      //nodes_[i] = nullptr;
    }
  }


  for (unsigned i = 0; i < edges_.size(); i++) {
    //delete edges_[i];
  }
  */

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

    /*
    // Tries to convert sourceID to double
    try {
      sourceID = stoi(line[3]);
    } catch (...) {
      std::cerr << "Invalid sourceID on line " << edges_.size() << " with value " << line[3] << std::endl;
      //break;
    }

    // Tries to convert destID to double
    try {
      destID = stoi(line[5]);
    } catch (...) {
      std::cerr << "Invalid destID on line " << edges_.size() << " with value " << line[5] << std::endl;
      //break;
    }
    */

    Node* source;
    Node* dest;

    //std::cout << sourceID << " " << airports.latitude(sourceID) << std::endl;
    //std::cout << destID << " " << airports.latitude(destID) << std::endl;

    // Check if airport with sourceID is null in airports.
    if (airports.latitude(sourceID) == -1000) {
      //std::cout << sourceID << " is invalid source airport in line " << edges_.size() << std::endl;
      areBothValid = false;
      //continue;
      //std::cout << "Kept continuing" << std::endl;
    }

    // Check if airport with destID is null in airports.
    if (airports.latitude(destID) == -1000) {
      //std::cout << destID << " is invalid dest airport in line " << edges_.size() << std::endl;
      areBothValid = false;
      //continue;
      //std::cout << "Kept continuing" << std::endl;
    }

    // If source node doesnt exist create, else set source equal to already built node
    if (areBothValid == true && nodes_[sourceID]->airportCode() == -1) {

      double sourceLat, sourceLng;

      sourceLat = airports.latitude(sourceID);
      sourceLng = airports.longitude(sourceID);

      /*
      // Tries to get source lat
      try {
        sourceLat = airports.latitude(sourceID);
      } catch (...) {
        std::cerr << "Invalid sourceLat on line " << edges_.size() << " with value " << sourceID << std::endl;
        break;
      }

      // Tries to get source lng
      try {
        sourceLng = airports.longitude(sourceID);
      } catch (...) {
        std::cerr << "Invalid sourceLng on line " << edges_.size() << " with value " << sourceID << std::endl;
        break;
      }
      */


      Node* _source = new Node(sourceID, sourceLat, sourceLng);
      source = _source;

      nodes_[sourceID] = source;

    } else if (areBothValid == true) {
      source = nodes_[sourceID];
      //std::cout << "Found " << source->airportCode() << " in nodes_" << std::endl;
    }

    //If dest node doesnt exist create, else set dest equal to already built node
    if (areBothValid == true && nodes_[destID]->airportCode() == -1) {
      //double destLat = airports.latitude(destID);;
      //double destLng = airports.longitude(destID);

      double destLat, destLng = 0.0;

      destLat = airports.latitude(destID);
      destLng = airports.longitude(destID);

      /*
      // Tries to get dest lat
      try {
        destLat = airports.latitude(destID);
      } catch (...) {
        std::cerr << "Invalid destLat on line " << edges_.size() << " with value " << destID << std::endl;
        break;
      }

      // Tries to get dest lng
      try {
        destLng = airports.longitude(destID);
      } catch (...) {
        std::cerr << "Invalid destLng on line " << edges_.size() << " with value " << destID << std::endl;
        break;
      }
      */

      Node* _dest = new Node(destID, destLat, destLng);
      dest = _dest;

      nodes_[destID] = dest;

    } else if (areBothValid == true) {
      dest = nodes_[destID];
      //std::cout << "Found " << dest->airportCode() << " in nodes_" << std::endl;
    }

    //Add edge if not there

    if (areBothValid == true && !source->areNeighbors(dest)) {
      Edge route(source, dest);
      edges_.push_back(route);

      source->addNeighbor(dest);
      //std::cout << "Added " << dest->airportCode() << " as neighbor to " << source->airportCode() << std::endl;
      //std::cout << source->airportCode() << " now has " << source->neighbors().size() << " neighbors." << std::endl;
      dest->addNeighbor(source);
      //std::cout << "Added " << source->airportCode() << " as neighbor to " << dest->airportCode() << std::endl;
      //std::cout << dest->airportCode() << " now has " << dest->neighbors().size() << " neighbors." << std::endl;
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
  Node * start_node = new Node();
  Node * end_node = new Node();
  for (Node * node: nodes_){
    if (node->airportCode() == start) {
      start_node = node;
    }
    if (node->airportCode() == end){
      end_node = node;
    }
  }

  if (start_node->areNeighbors(end_node)) {
    return start_node->distance(end_node);
  }

  return 9999999;
}
vector<int> Graph::shortestPath(int start, int end){
    //struct for comparison function of priority queue
    struct CompareDistance{
      bool operator()(std::pair<int, double> const & a, std::pair<int, double> const & b){
        //return true if a is bigger than b
        // ensures lower distances are prioritized in a queue
        return a.second> b.second;
      }
    };


    //size = number of all nodes(vertices) in graph
    int size = nodes_.size();

    std::unordered_map<int, double> distances_; // retrieve distance values for each node
    std::unordered_map<int, int> routes_;    // initialize a route that records node->its previous node

    //initialize a priority queue of node-distance pair
    typedef std::priority_queue<std::pair<int, double>, vector<std::pair<int, double>>, CompareDistance> pq;
    pq q;
    std::set<int> visited; //initialize set 'visited' to chech whether this nodes are visited

    //getting nodes from airportcode
    Node * startNode = new Node();
    Node * endNode = new Node();
    for (Node * node: nodes_){
      if (node->airportCode() == start) {
        startNode = node;
      }
      if (node->airportCode() == end){
        endNode = node;
      }
    }

    //check if there's adjacent nodes from starting node
    list<Node*> adjacent = startNode->neighbors();
    if(adjacent.empty()){
      return vector<int>(); //return empty vector if there's no adjacent node
    }

    //initialize edges in distance map to be large enough
    for(auto v: ) {
      distances_[v] = 9999999;
    }

    //set distances of starting point to be zero
    distances_[start] = 0;
    q.push(pair<int,double>(start, 0));

    //loop until we reach destination
    while (q.top().first != end && !q.empty()){
      std::pair<int, double> curr = q.top(); //get the next pair from priority_queue
      int curr_node = curr.first;
      q.pop();

      //mark current node as visited
      routes_.insert(curr_node);

      list<int> neighbors = curr_node.neighbors_codes(); // get all adjacent nodes

      for (int neighbor : neighbors){
        if (visited.find(neighbor) == visited.end()){ // if there's no node neighbor in visited
          double dist = distances_[curr_node] + getDistance(nodes, neighbor);
          if (dist <= distances_[neighbor]) {
            distances_[neighbor] = dist;
            routes_[neighbor] = curr_vertex;
            q.push(std::pair<int, double>(neighbor, dist));
          }
        }
      }
    }

    if(routes_.find(end) == routes_.end()){ // if no path exists
      return vector<int>();                          //return empty vector
    }

    //backtracing the path from routes_
    vector<int> path;
    int curr = end;
    while (curr != start) {
      path.push_back(curr);
      curr = routes_[curr];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

//void Graph::print() { }

/*

void Graph::removeNode(Node toRemove){
  //if the node is not at the end of the graph,
  if (adjacent_list.find(toRemove) != adjacent_list.end()){
    for (auto i = adjacent_list[toRemove].begin(); i != adjacent_list.end(); i++) {
        Node n = i->first;
        adjacent_list[u].erase(v);

    }
    adjacent_list.erase(v);
  }
}

void Graph::insertEdge(Node start, Node goal){
  //Edge newEdge = New Edge(node1, node2);

  //if edge already exists
  if(adjacent_list.find(start)!= adjacent_list.end()
    && adjacent_list[start].find(goal)!= adjacent_list[start].end()){
        return;
    }

  // if start nod does not exists, add it
  if(adjacent_list.find(start)==adjacent_list.end()){
    adjacent_list[start] = unordered_map<Node, Edge>();
  }

  // if start nod exists and edge does not exists between start and goal,
  // add new edge
    adjacent_list[start][goal] = Edge(start, goal);
}


void Graph::removeEdge(Node start, Node goal){
  //shouldn't we check whether the node exists or not first?

  // check whether edge exists or not
  if (adjacent_list[start].find(goal) != adjacent_list[start].end()){
    adjacent_list[start].erase(goal);
  }
}

similar to areNeighbors in Node
bool Graph::areAdjacent(Node node1, Node node2){
  auto list_1 = adjacent_list.find(node1);
  auto list_2 = adjacent_list.find(node2);
  //if ()
}

*/

/**
 * This method will insert a node into the nodes_ array maintained by the graph.
 * @param toAdd the Node to add to the nodes_ array
 */
/*void Graph::insertNode(Node toAdd) {

  nodes_.emplace(nodes_.begin() + toAdd.airportCode(), toAdd);

}*/

/**
 * This method will remove a node from the nodes_ array maintained by the graph. Also, must remove all edges associated with that node.
 * To remove the edges, parse throgh all edges maintained by the node, go to
 */
/*void Graph::removeNode(Node toRemove) {

  nodes_.emplace(nodes_.begin() + toRemove.airportCode(), Node());



}*/
