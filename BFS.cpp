#include "BFS.h"
#include "Graph.h"
#include "Node.h"
#include <iostream>
#include <string>
#include <vector>

/**
 * This is the BFS (Breadth First Search) traversal class. This class takes in a graph object and
 * traverses it using the traverse() method.
 */
BFS::BFS() { }

/** 
 *  Constructs a BFS traversal object using the given graph to be traversed and an
 *  arbitrary starting node
 *  @param graph graph to be traversed
 *  @param start starting node/center for the traversal
 */
BFS::BFS(Graph graph, Node* start)
{
    queue_.push(start);
    graph_ = graph;
    visited_.resize(1000000);
    for (unsigned long i = 0; i < visited_.size(); i++) {
        visited_[i] = false;
    }
}

/**
 *  This function traverses the entire graph passed into the constructor and returns
 *  an array of the airport codes in the order they were traversed.
 * 
 *  @returns an array of the traversed nodes' airport codes as integers
 */
std::vector<int> BFS::traverse()
{
    std::vector<int> toReturn;
    while (!(queue_.empty())) {

        Node* curr = queue_.front();
        visited_[curr->airportCode()] = true;

        toReturn.push_back(curr->airportCode());

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

