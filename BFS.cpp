#include "BFS.h"
#include "Graph.h"
#include "Node.h"

BFS::BFS() { }

BFS::BFS(Graph graph, Node start)
{
    queue_.push(start);
    graph_ = graph;
    visited_.resize(1000000);
    for (unsigned long i = 0; i < visited_.size(); i++) {
        visited_[i] = false;
    }
}


void BFS::traverse()
{
    while (!(queue_.empty())) {
        Node curr = queue_.front();
        
        //work
        std::cout << curr.airportCode() << std::endl;
        //work

        queue_.pop();
        list<Node> currNeighbors = curr.neighbors();
        for (auto it = currNeighbors.begin(); it != currNeighbors.end(); ++it) {
            if (!(visited_[(*it).airportCode()])) {
                visited_[(*it).airportCode()] = true;
                queue_.push(*it);
            }
        }
    }
}