#include "BFS.h"
#include "Graph.h"
#include "Node.h"
#include <iostream>
#include <string>
#include <vector>

BFS::BFS() { }

BFS::BFS(Graph graph, Node* start)
{
    queue_.push(start);
    graph_ = graph;
    visited_.resize(1000000);
    for (unsigned long i = 0; i < visited_.size(); i++) {
        visited_[i] = false;
    }
}


std::vector<int> BFS::traverse()
{
    std::vector<int> toReturn;
    while (!(queue_.empty())) {

        Node* curr = queue_.front();
        visited_[curr->airportCode()] = true;
        
        //work
        //std::cout << "Airport Code:" << curr->airportCode() << std::endl;
        toReturn.push_back(curr->airportCode());
        //work

        queue_.pop();
        list<Node*> currNeighbors = curr->neighbors();

        for (list<Node*>::iterator it = currNeighbors.begin(); it != currNeighbors.end(); ++it) {
            //std::cout << "TRAVERSAL FOR LOOP:" << (*it)->airportCode() << std::endl;
            if (!(visited_[(*it)->airportCode()])) {
                visited_[(*it)->airportCode()] = true;
                queue_.push(*it);
            }
        }
    }
    return toReturn;
}

