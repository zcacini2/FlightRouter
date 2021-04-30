#pragma once


#include "Edge.h"
#include "Node.h"
#include <vector>
#include <string>
#include <memory>
#include <queue>
#include <set>
#include <unordered_map>

using namespace std;

class Graph {
    public:

        Graph();

        ~Graph();

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
        Graph(const string & routesFile, const string & airportsFile);

        /*
        void insertNode(Node toAdd);

        void removeNode(Node toRemove);

        //inserts an edge between two nodes into the graph structure
        void insertEdge(Node start, Node goal);

        removes edge between two given nodes from graph structure. this
        function should also make sure to adjust the adjacencies/neighbors of the
        nodes that are losing an edge

        void removeEdge(Node start, Node goal);

        //returns true if two nodes are adjacent (have an edge), false otherwise
        bool areAdjacent(Node node1, Node node2);
        */


        /**
         * Method returning all nodes of a graph.
         */
        vector<Node*> getNodes();

        /**
         * Method returning all edges of a graph.
         */
        vector<Edge> getEdges();

        Node* getFirstNode();
        vector<int> shortestPath(int start, int end);
          /* dijkstra function. this function takes graph and two Nodes
          and return shortest distance from starting point to the end.
          */

        double getDistance(int start, int end);
        /* helper function for shortestPath. this function takes two airportcodes,
        get nodes from the codes, and returns distance of two nodes if they're adjacent.
        */

        //void print();

    private:

        /**
         * Vector of Nodes stored by the OpenFlights ID of the airport
         */

        //vector<Node*> nodes_;
        vector<Node*> nodes_;

        /**
         * Vector of edges. Each edge starts at the airport with the
         */
        vector<Edge> edges_;
};
