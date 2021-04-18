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

        Node(string, double, double);

        string airportCode();
        double latitude();
        double longitude();
        //void addIncidentEdge(Edge edge);

    private:
        /**
         * Put Node private members here.
         */

        //The beginning/necessary components
        string airportCode_;
        double latitude_;
        double longitude_;
        //list<Edge> incidentEdges_;
        

        /*
        Necessary for advanced input methods
        string name;
        string city;
        string country;
        */
        

};
#endif