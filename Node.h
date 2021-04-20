#pragma once

#ifndef NODE_H
#define NODE_H

#include <string>
#include <list>

//#include "Edge.h"

using namespace std;

/**
 * The Node class represents an Airport in the graph linked-memory structure. 
 */
class Node {

    public:
        /**
         * Put Node public members here.
         */
        Node();

        Node(int, double, double);

        int airportCode();
        double latitude();
        double longitude();
        void addNeighbor();
        //void addIncidentEdge(Edge edge);

    private:
        /**
         * Put Node private members here.
         */

        //The beginning/necessary components
        int airportCode_;
        double latitude_;
        double longitude_;
        list<Node> neighbors_;
        //list<Edge> incidentEdges_;
        

        /*
        Necessary for advanced input methods
        string name;
        string city;
        string country;
        */
        

};
#endif