#pragma once

#include "Node.h"
#include "Edge.h"
#include <vector>

using namespace std;

class Graph {
    public:
        //inserts node into graph
        void insertNode(Node);

        //removes nodes from graph and returns the removed node
        Node removeNode(Node);

        //inserts an edge between two nodes into the graph structure
        void insertEdge(Node, Node, K key);

        /*removes edge between two given nodes from graph structure. this
        function should also make sure to adjust the adjacencies/neighbors of the
        nodes that are losing an edge*/
        void removeEdge(Node, Node);

        //returns true if two nodes are adjacent (have an edge), false otherwise
        bool areAdjacent(Node, Node);
        
    private:
        vector<Node> nodes_;
        vector<Edge> edges_;
};