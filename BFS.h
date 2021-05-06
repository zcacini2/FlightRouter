#pragma once

#include <string>
#include <vector>
#include <iterator>
#include <queue>
#include "Graph.h"
#include "Node.h"

/**
 * This is the BFS (Breadth First Search) traversal class. This class takes in a graph object and
 * traverses it using the traverse() method.
 */
class BFS {
    
    public:

        BFS();

        /** 
         *  Constructs a BFS traversal object using the given graph to be traversed and an
         *  arbitrary starting node
         *  @param graph graph to be traversed
         *  @param start starting node/center for the traversal
         */
        BFS(Graph graph, Node* start);

        /**
         *  This function traverses the entire graph passed into the constructor and returns
         *  an array of the airport codes in the order they were traversed.
         * 
         *  @returns an array of the traversed nodes' airport codes as integers
         */
        std::vector<int> traverse();

    private:

        //queue used for BFS traversal of the graph
        queue<Node*> queue_;

        //vector keeping track of visited nodes
        vector<bool> visited_;

        //graph object that is to be traversed
        Graph graph_;
};

