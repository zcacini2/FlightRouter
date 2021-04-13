#pragma once

#include <vector>

class Graph {
    public:
        void insertVertex(Node);
        Node removeVertex(Node);
        void insertEdge(Node, Node, K key);
        void removeEdge(Node, Node);
    private:
        std::vector<Node*> _nodes;
        
        
};