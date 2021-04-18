#pragma once

//#ifndef EDGE_H
//#define EDGE_H

#include "Node.h"

using namespace std;

class Edge {
    public:
        Edge();
        Edge(Node start, Node end);

        Node start();
        Node end();
        double distance();
    private:
        Node start_; 
        Node end_;
        double distance_; //the edge should store the distance between the two airports

        double calculateDistance(Node node1, Node node2);
};

//#endif

