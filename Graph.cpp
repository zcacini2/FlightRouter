<<<<<<< HEAD
#include "Graph.h"
#include <vector>
#include "Edge.h"


void Graph:: insertNode(Node toAdd){
/*  if (toAdd == NULL){
    Node node = new Node
  }*/
  //if there already exists toAdd node, remove it
    removeNode(toAdd)
    //add empty node
    adjacent_list(toAdd) = unordered_map<Node,Edge>()
}

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
  if(adjacent_list.find(start)==adjacent_list.end()) {
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

bool Graph::areAdjacent(Node node1, Node node2){
  auto list_1 = adjacent_list.find(node1);
  auto list_2 = adjacent_list.find(node2);
  if ()
}
=======
#include "Graph.h"
#include <vector>
#include "Edge.h"
#include "readFromFile.hpp"
#include "Airports.h"
//#include <unordered_map>

Graph::Graph() { }

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
Graph::Graph(const std::string & filename) {

  std::string str = file_to_string(filename);

  Airports airports("tests/airportsDataSmall.txt");

  nodes_.resize(airports.size() + 1);
  for (unsigned i = 0; i <= airports.size(); i++) {
    nodes_[i] = Node();
  }

  std::vector<string> line;  //create line vector
  stringstream s_stream(str); //create string stream from the string
  int sourceID, destID; 

  while(s_stream.good()) {
    string row, substr;
    getline(s_stream, row, '\n'); //get first string delimited by comma
    stringstream row_stream(row);

    while (row_stream.good()) {
      getline(row_stream, substr, ',');
      substr.erase(std::remove( substr.begin(), substr.end(), '\"' ), substr.end()); //cleans quotations
      line.push_back(substr);
    }
    
    sourceID = stoi(line[3]); //OpenFlights ID of the source airport
    destID = stoi(line[5]); //OpenFlights ID of the destination airport

    Node source, dest;

    // If source node doesnt exist create, else set source equal to already built node
    if (nodes_[sourceID].airportCode() == -1) {
      double sourceLat = airports.latitude(sourceID);
      double sourceLng = airports.longitude(sourceID);

      Node _source(sourceID, sourceLat, sourceLng);
      source = _source;

      nodes_[sourceID] = source;

    } else {
      source = nodes_[sourceID];
    }

    //If dest node doesnt exist create, else set dest equal to already built node
    if (nodes_[destID].airportCode() == -1) {
      double destLat = airports.latitude(destID);;
      double destLng = airports.longitude(destID);

      Node _dest(destID, destLat, destLng);
      dest = _dest;

      nodes_[destID] = dest;

    } else {
      dest = nodes_[destID];
    }

    //Add edge if not there

    if (!source.areNeighbors(dest)) {
      Edge route(source, dest);
      edges_.push_back(route);

      source.addNeighbor(dest);
      dest.addNeighbor(source);
    }

    line.clear();

  }
  
  
}

/**
 * Method returning all nodes of a graph.
 */
vector<Node> Graph::getNodes() {
  return nodes_;
}

/**
 * Method returning all edges of a graph
 */
vector<Edge> Graph::getEdges() {
  return edges_;
}


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
>>>>>>> e31239400d14e126e6d6d8c0898015a8ae707855
