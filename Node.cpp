#include "Node.h"

#include <string>

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