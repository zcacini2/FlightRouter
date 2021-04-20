#include "Graph.h"
#include <vector>
#include "Edge.h"
#include "readFromFile.hpp"

/**
 * Default Graph Constructor
 */
Graph::Graph() {
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


Graph::Graph(const std::string & filename) {

  std::string str = file_to_string(filename);

  Airports airports("tests/airportsDataSmall.txt");

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
      std::cout << line.back() << std::endl;
    }
    
    sourceID = stoi(line[3]); //OpenFlights ID of the source airport
    destID = stoi(line[5]); //OpenFlights ID of the destination airport

    if (nodes[sourceID] ==  NULL && nodes[destID] == NULL) {
      //If neither node exists, build both nodes and add to list of edges

      double sourceLat = airports[sourceID][0];
      double sourceLng = airports[sourceID][1];
      double destLat = airports[destID][0];
      double destLng = airports[destID][1];

      Node source(sourceID, sourceLat, sourceLng);
      Node dest(destID, destLat, destLng);

      if (nodes.size() < sourceID || nodes.size() < destID) {
        nodes.resize(std::max(sourceID, destID));
      }

      nodes.emplace(nodes.begin() + sourceID, source);
      nodes.emplace(nodes.begin() + destID, dest);

      //Add edge

    }

    // Check if edge exists using are adjacent
      // But how will we use that with just two airport codes
    // Check that both nodes exist
    // Perform necessary logic

  
    line.clear();

  }
  
  
}


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

bool Graph::areAdjacent(Node node1, Node node2){
  auto list_1 = adjacent_list.find(node1);
  auto list_2 = adjacent_list.find(node2);
  if ()
}
