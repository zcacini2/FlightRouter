#include <math.h>

#include "Edge.h"
#include "Node.h"


Edge::Edge() { }

/**
 * Creates an Edge object using two nodes that this edge is meant to represent the path between.
 * This constructor also automatically calculates the distance between the two nodes.
 * 
 * @param start first node this edge is to represent
 * @param end second node this edge is to represent
 */
Edge::Edge(Node * start, Node * end) {
    start_ = start;
    end_ = end;
    distance_ = calculateDistance(start, end);
}

/**
 * Calculates the distance between the two Nodes passed. Is automatically used by constructor
 * to initialize the weight (distance) for this Edge. Uses the nodes' latitudes and longitudes.
 * @param node1 first node to calculate the distance from
 * @param node2 second node to calculate the distance to
 * @returns the distance between the two airports in kilometers
 */
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

/**
 * Public getter for the first node stored in this edge object.
 * 
 * @returns the first node this edge represents.
 */
Node* Edge::start() {
    return start_;
}

/**
 * Public getter for the second node stored in this edge object.
 * 
 * @returns the second node this edge represents.
 */
Node* Edge::end() {
    return end_;
}

/**
 * Public getter for the distance calculated and stored in this edge object in kilometers.
 * 
 * @returns the distance between the two nodes as a double in kilometers
 */
double Edge::distance() {
    return distance_;
}
