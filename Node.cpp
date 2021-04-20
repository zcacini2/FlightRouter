#include <string>

#include "Node.h"
//#include "Edge.h"

using namespace std;

Node::Node() { 
    airportCode_ = -1;
    latitude_ = 0.0;
    longitude_ = 0.0;
}

Node::Node(int code, double latitude, double longitude) {
    airportCode_ = code;
    latitude_ = latitude;
    longitude_ = longitude;
}

int Node::airportCode() {
    return airportCode_;
}

double Node::latitude() {
    return latitude_;
}

double Node::longitude() {
    return longitude_;
}

void Node::addNeighbor() {
    return;
}

/*void Node::addIncidentEdge(Edge edge) {
    if (edge.start() == *this || edge.end() == *this) {
        incidentEdges_.push_back(edge);
    }
    incidentEdges_.push_back(edge);
}*/