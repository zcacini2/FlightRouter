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


        //inserts node into graph
        void insertNode(Node toAdd);

        //removes nodes from graph and returns the removed node
        Node removeNode(Node toRemove);

        //inserts an edge between two nodes into the graph structure
        void insertEdge(Node node1, Node node2);

        /*removes edge between two given nodes from graph structure. this
        function should also make sure to adjust the adjacencies/neighbors of the
        nodes that are losing an edge*/
        void removeEdge(Node node1, Node node2);

        //returns true if two nodes are adjacent (have an edge), false otherwise
        bool areAdjacent(Node node1, Node node2);

    private:

        unordered_map<Node, unordered_map<Node, Edge>> adjacent_list;
        vector<Node> nodes_;
        vector<Edge> edges_;
};
