#pragma once

#ifndef NODE_H
#define NODE_H

#include <string>
#include <list>
#include <vector>

using namespace std;

/**
 * The Node class represents an Airport in the graph linked-memory structure.
 * It stores the airport code (index) of the airport it is supposed to represent,
 * along with its latitude and longitude. It also stores its neighbors in the graph
 * structure as a list.
 */
class Node {

    public:
        /**
         * Default constructor. Sets airport code to -1 (invalid airport) and latitude and longitude
         * to 0. Used to represent airports that do not exist during graph contruction.
         */
        Node();

        /**
         * Destroys allocated memory in neighbors list for this node object
         */
        ~Node();

        /**
         * Constructor for a valid airport. Takes an airport code as an int as well as
         * the latitude and longitude.
         * 
         * @param airportCode Airport Code (index, the first column in the airports.txt dataset)
         * @param latitude latitude of this airport
         * @param longitude longitude of this airport
         */
        Node(int airportCode, double latitude, double longitude);

        /**
         * Public getter for the airport code of this node object.
         * 
         * @returns airport code stored in the object as an int
         */
        int airportCode();

        /**
         * Public getter for the airport code of this node object.
         * 
         * @returns latitude of this airport as a double
         */
        double latitude();

        /**
         * Public getter for the airport code of this node object.
         * 
         * @returns longitude for this airport as a double
         */
        double longitude();

        /**
         * Adds a neighbor to the list of neighbors for this node. Used
         * in the graph constructor.
         * 
         * @param neighbor a pointer to the node that neighbors this node object.
         */
        void addNeighbor(Node* neighbor);

        /**
         * Removes a neighbor from the list of neighbors for this node.
         * 
         * @param toRemove the node to be declassified as a neighbor
         * @returns the removed node for testing purposes
         */
        Node* removeNeighbor(Node* toRemove);

        /**
         * Returns true if the passed node is a neighbor to this node object.
         * 
         * @param check node to be checked for neighbor status
         * @returns true if the node neighbors this node, false otherwise
         */
        bool areNeighbors(Node* check);

        /**
         * Public getter for the list of neighbors of this node object
         * as a list of Node pointers.
         * 
         * @returns neighbors of this node, as a list
         */
        list<Node*> neighbors();

        /**
         * Public getter for the airport codes of this Node's neighbors
         * 
         * @returns airport codes of the neighbors as a list of ints
         */
        list<int> neighbors_codes_();

        /**
         * Calculates the distance in kilometers between this node object
         * and another Node object passed by pointer using their latitudes and longitudes.
         * 
         * @param other a pointer to the Node to which the distance is calculated
         * @returns the linear distance between the two nodes in kilometers.
         */
        double distance(Node* other);

        /**
         * Same as the one argument version, but the Node is passed by airport code and found
         * from the given vector of Nodes. 
         * 
         * @param nodes vector of nodes to use in finding the desired node by airport code
         * @param other airport code of the node to/from which the distance should be calculated
         * @returns the linear distance between the two nodes in kilometers
         */
        double distance(vector<Node*> nodes, int other);

        /**
         * Calculates the total distance in kilometers between the Nodes in the passed vector
         * using distance(Node).
         * 
         * @param route the vector of Nodes representing the route to be measured.
         * @returns total distance from first to last node in the vector in kilometers.
         */
        double getRouteDistance(vector<Node*> route);

        bool operator==(const Node &other) const;

    private:

        /**
         * Airport Code, otherwise known as the index for this airport used in all other
         * methods of the graph implementation, for this airport node.
         */
        int airportCode_;

        /**
         * Latitude in degrees for this airport as a double. Negative values indicate the southern
         * hemisphere.
         */
        double latitude_;

        /**
         * Longitude in degrees for this airport as a double. Negative values indicate the western
         * hemisphere.
         */
        double longitude_;

        /**
         * List of all the nodes that neighbor this node in the graph structure.
         */
        list<Node*> neighbors_;

        /**
         * List of all the airport codes of the neighbors of this node in the graph structure.
         * Used in shortest path implementation.
         */
        list<int> neighbors_code_;
};
#endif
