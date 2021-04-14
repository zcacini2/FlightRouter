#pragma once

#include "Node.h"

using namespace std;

class Edge {
    public:
        Edge();
        Edge(Node, Node);

        Node start();
        Node end();
        double distance();
        //Edge(Node, Node, double);
    private:
        Node start_; 
        Node end_;
        double distance_; //the edge should store the distance between the two airports

        double calculateDistance(Node, Node);


        void placeholder();

};