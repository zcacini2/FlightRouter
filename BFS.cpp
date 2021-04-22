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
<<<<<<< HEAD
        Node curr = queue_.front();
<<<<<<< HEAD

=======
=======
        Node* curr = queue_.front();
        visited_[curr->airportCode()] = true;
>>>>>>> a5d79e9c2fa2472db1852833c04ba1d4c6dccabf
        //curr.addNeighbor(Node(4, -1, -1));
        
>>>>>>> 73a72beb6d5da08e902c15d50d778acf7a9f27b1
        //work
        //std::cout << "Airport Code:" << curr->airportCode() << std::endl;
        //std::vector<std::string> toReturn;
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
<<<<<<< HEAD
}
=======
    return toReturn;
}
>>>>>>> 8387e32685ebfcf91d864a5099a1fd72bab6ec4c
