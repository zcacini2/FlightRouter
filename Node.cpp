#include <string>

#include "Node.h"
//#include "Edge.h"

using namespace std;

Node::Node() { }

Node::Node(string code, double latitude, double longitude) {
    airportCode_ = code;
    latitude_ = latitude;
    longitude_ = longitude;
}

string Node::airportCode() {
    return airportCode_;
}

double Node::latitude() {
    return latitude_;
}

double Node::longitude() {
    return longitude_;
}

/*void Node::addIncidentEdge(Edge edge) {
    if (edge.start() == *this || edge.end() == *this) {
        incidentEdges_.push_back(edge);
    }
    incidentEdges_.push_back(edge);
}*/