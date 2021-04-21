#pragma once

#include <iterator>
#include <queue>
#include "Graph.h"
#include "Node.h"

class BFS {
    public:
        BFS(Graph graph, Node start);
        /*{
            queue_.push(start);
            graph_ = graph;
            visited_.resize(1000000);
            for (unsigned long i = 0; i < visited_.size(); i++) {
                visited_[i] = false;
            }
        }*/
        traverse();
        /*{
            while (queue not empty) 
                Node curr = queue_.front();

                *do stuff here to node* (depth? predecessor? print?)

                queue.pop();
                

                for (every adjacent node) 
                    if (adj node not visited) 
                        visited[adj node] = true;
                        enqueue(adj node)
        }*/
    private:
        queue<Node> queue_;
        vector<bool> visited_;
        Graph graph_;
};



/*
class BFS {
    public:
        class Iterator : std::iterator<std::forward_iterator_tag, Node> {
            public:
                Iterator();
                Iterator()
            private:
        }
        BFS(Graph graph, Node start);

};*/