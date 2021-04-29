#include <string>

#include "Node.h"
#include "Edge.h"

using namespace std;

Node::Node() {
    airportCode_ = -1;
    latitude_ = 0.0;
    longitude_ = 0.0;
    isVisited_ = false;
}

Node::~Node() {
    neighbors_.clear();
}

Node::Node(int code, double latitude, double longitude) {
    airportCode_ = code;
    latitude_ = latitude;
    longitude_ = longitude;
    isVisited_ = false;

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

void Node::addNeighbor(Node* neighbor) {
    neighbors_.push_back(neighbor);
}

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

double Node::getDistance(Node *node) {
  if (areNeighbors(node)){
    double earthRadius = 6371;
    double lat1 = latitude_;
    double long1 = longitude_;
    double lat2 = node->latitude();
    double long2 = node2->longitude();

    double latDiffRads = (lat2 - lat1) * (M_PI/180);
    double longDiffRads = (long2 - long1) * (M_PI/180);

    double a = 0.5 - cos(latDiffRads)/2 + cos(lat1 * (M_PI/180)) *
        cos(lat2 * (M_PI/180)) * (1 - cos(longDiffRads))/2;

    return 2 * earthRadius * asin(sqrt(a));
  }
}
list<Node*> Node::neighbors() {
    return neighbors_;
}


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


    /*for (Node neighbor : neighbors_) {
        if (neighbor.airportCode() != other.neighbors_[i].airportCode()) {
            return false;
        }
    }*/

    return true;
}


bool Node::areNeighbors(Node* check) {
    for (list<Node*>::iterator it = neighbors_.begin(); it != neighbors_.end(); ++it) {
        if ((*it)->airportCode() == check->airportCode()) {
            return true;
        }
    }
    return false;
}

/*void Node::addIncidentEdge(Edge edge) {
    if (edge.start() == *this || edge.end() == *this) {
        incidentEdges_.push_back(edge);
    }
    incidentEdges_.push_back(edge);
}*/
