#pragma once

#include <iterator>
#include <queue>
#include "Graph.h"
#include "Node.h"

class BFS {
    public:
        BFS();
        /** 
         *  Constructs a BFS traversal object using the given graph to be traversed and an
         *  arbitrary starting node
         *  @param graph graph to be traversed
         *  @param start starting node/center for the traversal
         */
        BFS(Graph graph, Node start);
        /**
         *  This function traverses the entire graph passed into the constructor. The
         *  traversal itself currently does no work.
         */
        void traverse();
    private:
        //queue used for BFS traversal of the graph
        queue<Node> queue_;

        //vector keeping track of visited nodes
        vector<bool> visited_;
        Graph graph_;
};

