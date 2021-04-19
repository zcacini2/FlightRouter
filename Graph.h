#pragma once


#include "Edge.h"
#include "Node.h"
//#include "Edge.h"
#include <vector>
#include <unordered_map>


using namespace std;
using std::unordered_map;

class Graph {
    public:

        //Graph constructor from CSV file.
        Graph(const std::string & filename);

        //inserts node into graph
        void insertNode(Node toAdd);

        //removes nodes from graph and returns the removed node
        Node removeNode(Node toRemove);

        //inserts an edge between two nodes into the graph structure
        void insertEdge(Node start, Node goal);

        /*removes edge between two given nodes from graph structure. this
        function should also make sure to adjust the adjacencies/neighbors of the
        nodes that are losing an edge*/
        void removeEdge(Node start, Node goal);

        //returns true if two nodes are adjacent (have an edge), false otherwise
        bool areAdjacent(Node node1, Node node2);

        /** 
         * This method will handle the airport coder/decoder. This will be maintained as 2 vectors. The vectos'
         * indices correspond to the OpenFlights ID. This will aid the creation of nodes by matching airport ID
         * to the lat/long found in the airports file. 
         * 
         * This method will accomplish this by first translating the file into a vector, and then pulling all relevant
         * information. The information stored in the airports file is as follows: Airport ID (OpenFlights ID), Name,
         * City, Country, 3 Letter IATA code, 4 Letter ICAO code, Latitude, Longitude, Altitude, Timezone, DST, Tz
         * database time zone, and source. Relevant information is Airport ID (OpenFlights ID), Latitude, and Longitude. 
         * Later we will add Name and City.
         *
         * @param filename name of file to parse to fill airport information.
         */
        void airportCoder(const std::string & filename);

    private:

        unordered_map<Node, unordered_map<Node, Edge>> adjacent_list;
        vector<Node> nodes_;
        vector<Edge> edges_;

        /** 
         * TO BE ADDED TO FUNCTIONALITY LATER!!
         * Index corresponds to the OpenFlights identifier.
         * Data stored: Airport Name and City of Airport.
         */
        std::vector<std::vector<string>> airports;

        /**
         * Index corresponds to the OpenFlights identifier.
         * Data stored: Latitude and Longitude.
         */
        std::vector<std::vector<double>> lat_long;
};
