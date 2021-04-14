#pragma once

#include <string>

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

    private:
        /**
         * Put Node private members here.
         */

        //The beginning/necessary components
        string airportCode_;
        double latitude_;
        double longitude_;

        /*
        Necessary for advanced input methods
        string name;
        string city;
        string country;
        */
        

};