#include <math.h>

#include "Edge.h"
#include "Node.h"


Edge::Edge() { }

Edge::Edge(Node * start, Node * end) {
    start_ = start;
    end_ = end;
    distance_ = calculateDistance(start, end);
}

//calculates distance in kilometers
double Edge::calculateDistance(Node * node1, Node * node2) {
    double earthRadius = 6371;
    double lat1 = node1->latitude();
    double long1 = node1->longitude();
    double lat2 = node2->latitude();
    double long2 = node2->longitude();

    double latDiffRads = (lat2 - lat1) * (M_PI/180);
    double longDiffRads = (long2 - long1) * (M_PI/180);

    double a = 0.5 - cos(latDiffRads)/2 + cos(lat1 * (M_PI/180)) *
        cos(lat2 * (M_PI/180)) * (1 - cos(longDiffRads))/2;

    return 2 * earthRadius * asin(sqrt(a));
}

Node* Edge::start() {
    return start_;
}

Node* Edge::end() {
    return end_;
}

double Edge::distance() {
    return distance_;
}
