#pragma once

#ifndef NODE_H
#define NODE_H

#include <string>
#include <list>
#include <vector>

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

        ~Node();

        Node(int, double, double);

        int airportCode();
        double latitude();
        double longitude();
        void addNeighbor(Node* neighbor);
        Node* removeNeighbor(Node* toRemove);
        bool areNeighbors(Node* check);
        list<Node*> neighbors();
        void setVisited(bool visited);
        bool getVisited();
        double distance(Node* other);
        double getRouteDistance(vector<Node*> route);
        
        //void addIncidentEdge(Edge edge);

        /**
        * overload operator ==
        * @param other The other point
        * @return True for smaller, false for otherwise
        */
        bool operator==(const Node &other) const;

    private:
        /**
         * Put Node private members here.
         */

        //The beginning/necessary components
        int airportCode_;
        double latitude_;
        double longitude_;
        list<Node*> neighbors_;
        bool isVisited_; // member required for implementing dijkstra's algorithm
    
        //list<Edge> incidentEdges_;
        

        /*
        Necessary for advanced input methods
        string name;
        string city;
        string country;
        */
        

};
#endif
