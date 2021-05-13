#include <string>
#include <math.h>

#include "Node.h"
using namespace std;

/**
 * Default constructor. Sets airport code to -1 (invalid airport) and latitude and longitude
 * to 0. Used to represent airports that do not exist during graph contruction.
 */
Node::Node() {
    airportCode_ = -1;
    latitude_ = 0.0;
    longitude_ = 0.0;
}

/**
 * Destroys allocated memory in neighbors list for this node object
 */
Node::~Node() {
    neighbors_.clear();
    neighbors_code_.clear();
}

/**
 * Constructor for a valid airport. Takes an airport code as an int as well as
 * the latitude and longitude.
 * 
 * @param airportCode Airport Code (index, the first column in the airports.txt dataset)
 * @param latitude latitude of this airport
 * @param longitude longitude of this airport
 */
Node::Node(int code, double latitude, double longitude) {
    airportCode_ = code;
    latitude_ = latitude;
    longitude_ = longitude;
}

 /**
 * Public getter for the airport code of this node object.
 * 
 * @returns airport code stored in the object as an int
 */
int Node::airportCode() {
    return airportCode_;
}

/**
 * Public getter for the airport code of this node object.
 * 
 * @returns latitude of this airport as a double
 */
double Node::latitude() {
    return latitude_;
}

/**
 * Public getter for the airport code of this node object.
 * 
 * @returns longitude for this airport as a double
 */
double Node::longitude() {
    return longitude_;
}

/**
 * Adds a neighbor to the list of neighbors for this node. Used
 * in the graph constructor.
 * 
 * @param neighbor a pointer to the node that neighbors this node object.
 */
void Node::addNeighbor(Node* neighbor) {
    neighbors_.push_back(neighbor);
    neighbors_code_.push_back(neighbor->airportCode_);
}

/**
 * Removes a neighbor from the list of neighbors for this node.
 * 
 * @param toRemove the node to be declassified as a neighbor
 * @returns the removed node for testing purposes
 */
Node* Node::removeNeighbor(Node* toRemove) {
    list<Node*>::iterator it;
    for (it = neighbors_.begin(); it != neighbors_.end(); ++it) {
        Node* tmp = (*it);
        if (tmp == toRemove) {
            neighbors_.erase(it);
            return toRemove;
        }
    }
    return toRemove;
}

/**
 * Public getter for the list of neighbors of this node object
 * as a list of Node pointers.
 * 
 * @returns neighbors of this node, as a list
 */
list<Node*> Node::neighbors() {
    return neighbors_;
}

/**
 * Overloaded Node equality operator
 */
bool Node::operator==(const Node &other) const {

    if (airportCode_ != other.airportCode_) {
        return false;
    }

    if (latitude_ != other.latitude_) {
        return false;
    }

    if (longitude_ != other.longitude_) {
        return false;
    }

    return true;
}

/**
 * Returns true if the passed node is a neighbor to this node object.
 * 
 * @param check node to be checked for neighbor status
 * @returns true if the node neighbors this node, false otherwise
 */
bool Node::areNeighbors(Node* check) {
    for (list<Node*>::iterator it = neighbors_.begin(); it != neighbors_.end(); ++it) {
        if ((*it)->airportCode() == check->airportCode()) {
            return true;
        }
    }
    return false;
}

/**
 * Public getter for the airport codes of this Node's neighbors
 * 
 * @returns airport codes of the neighbors as a list of ints
 */
list<int> Node::neighbors_codes_() {
  return neighbors_code_;
}

/**
 * Calculates the distance in kilometers between this node object
 * and another Node object passed by pointer using their latitudes and longitudes.
 * 
 * @param other a pointer to the Node to which the distance is calculated
 * @returns the linear distance between the two nodes in kilometers.
 */
double Node::distance(Node* other) {

    double earthRadius = 6371;
    double lat1 = latitude_;
    double long1 = longitude_;
    double lat2 = other->latitude();
    double long2 = other->longitude();

    double latDiffRads = (lat2 - lat1) * (M_PI/180);
    double longDiffRads = (long2 - long1) * (M_PI/180);

    double a = 0.5 - cos(latDiffRads)/2 + cos(lat1 * (M_PI/180)) *
        cos(lat2 * (M_PI/180)) * (1 - cos(longDiffRads))/2;

    return 2 * earthRadius * asin(sqrt(a));
}

/**
 * Same as the one argument version, but the Node is passed by airport code and found
 * from the given vector of Nodes. 
 * 
 * @param nodes vector of nodes to use in finding the desired node by airport code
 * @param destination airport code of the node to/from which the distance should be calculated
 * @returns the linear distance between the two nodes in kilometers
 */
double Node::distance(vector<Node*> nodes, int destination) {
  Node * dest;

  for (Node * node : nodes){
    if (node->airportCode() == destination){
      dest = node;
    }
  }

  double earthRadius = 6371;
  double lat1 = latitude_;
  double long1 = longitude_;
  double lat2 = dest->latitude();
  double long2 = dest->longitude();
  double latDiffRads = (lat2 - lat1) * (M_PI/180);
  double longDiffRads = (long2 - long1) * (M_PI/180);

  double a = 0.5 - cos(latDiffRads)/2 + cos(lat1 * (M_PI/180)) *
      cos(lat2 * (M_PI/180)) * (1 - cos(longDiffRads))/2;

  return 2 * earthRadius * asin(sqrt(a));
}

/**
 * Calculates the total distance in kilometers between the Nodes in the passed vector
 * using distance(Node).
 * 
 * @param route the vector of Nodes representing the route to be measured.
 * @returns total distance from first to last node in the vector in kilometers.
 */
double Node::getRouteDistance(vector<Node*> route) {
    double totDist = 0;
    for (unsigned i = 0; i < route.size() - 1; i++) {
        totDist += route[i]->distance(route[i+1]);
    }
    return totDist;
}
