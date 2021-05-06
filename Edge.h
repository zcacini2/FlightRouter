#pragma once

#include "Node.h"

using namespace std;

/**
 * This Edge class represents the edges of our graph. Each edge represents a valid route between
 * two airports passed in as Node objects.
 */
class Edge {
    public:
        Edge();

        /**
         * Creates an Edge object using two nodes that this edge is meant to represent the path between.
         * This constructor also automatically calculates the distance between the two nodes.
         * 
         * @param start first node this edge is to represent
         * @param end second node this edge is to represent
         */
        Edge(Node * start, Node * end);

        /**
         * Public getter for the first node stored in this edge object.
         * 
         * @returns the first node this edge represents.
         */
        Node* start();

        /**
         * Public getter for the second node stored in this edge object.
         * 
         * @returns the second node this edge represents.
         */
        Node* end();

        /**
         * Public getter for the distance calculated and stored in this edge object in kilometers.
         * 
         * @returns the distance between the two nodes as a double in kilometers
         */
        double distance();

    private:

        //the first node this edge represents
        Node* start_;

        //the second node this edge represents
        Node* end_;

        //the distance between the two airports in kilometers
        double distance_;

        /**
         * Calculates the distance between the two Nodes passed. Is automatically used by constructor
         * to initialize the weight (distance) for this Edge. Uses the nodes' latitudes and longitudes.
         * @param node1 first node to calculate the distance from
         * @param node2 second node to calculate the distance to
         * @returns the distance between the two airports in kilometers
         */ 
        double calculateDistance(Node * node1, Node * node2);
};
