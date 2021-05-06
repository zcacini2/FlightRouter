#pragma once

#include "Graph.h"
#include "cs225/PNG.h"
#include "Node.h"

using namespace cs225;
using namespace std;

/**
 * This class is the implementation of our graphical representation algorithm.
 * It requires a PNG image to be used as a background to function properly. By default this
 * is the mercator map provided as background.png, but a different image can also be passed
 * during construction. 
 */
class MapPrinter {
    public:

        /** 
         * This is the default constructor which uses background.png by default as the background.
         */
        MapPrinter();

        /** 
         * This constructor allows for a custom image to be passed as a background. However,
         * this class will only function as intended if a PNG of a centered mercator world map
         * is used.
         * 
         * @param background PNG object to be used for printing instead of the default 
         */
        MapPrinter(PNG background);

        /** 
         * This constructor is the same as the one argument constructor and has no special
         * function other than testing. The graph is unused in the algorithm.
         * 
         * @param graph graph object passed in for testing, obsolete argument
         * @param background PNG object to be used for printing instead of the default 
         */
        MapPrinter(Graph graph, PNG background);

        /**
         * Adds the given airport Node onto the PNG map as a dot using its latitude and longitude.
         * The first point printed is purple to indicate the starting point and the last point printed
         * is green to indicate the ending point of the route. The starting and ending points are also
         * squares instead of circles just as an added distinction. All other middle points are red
         * and circular.
         * 
         * @param node node to be printed onto the PNG image in the mapprinter object
         */
        void addPoint(Node node);

        /**
         * Same as the one argument version, but with customizability for the color and size of
         * the points. Used by the MapPrinter object to print the starting and ending points of the route.
         * This function prints the points as squares.
         * 
         * @param node node to be printed onto the PNG image in the mapprinter object
         * @param h desired hue of the color for this point in the HSLA color space 
         * @param s desired saturation of the color for this point in the HSLA color space
         * @param l desired luminance of the color for this point in the HSLA color space
         * @param sizeInc desired increase (or decrease) in size for this point
         */
        void addPoint(Node node, double h, double s, double l, int sizeInc);

        /**
         * Adds a linear path from one point to another on the map PNG about 2 pixels in thickness
         * using the passed Edge.
         * The path is always red (0, 100%, 50%, 100% in HSLA) in color. This function automatically prints
         * two points in the Edge object on the map as well.
         * 
         * @param edge path to be printed onto the PNG image along with its nodes
         */
        void addPath(Edge edge);

        /**
         * Adds an entire route onto the map PNG by adding all the points and paths using
         * the Node* objects in the vector. The order of the Node* objects determines the paths printed
         * between the points on the map.
         * 
         * @param route array of Nodes to be added, in order, stored in a vector
         */
        void addRoute(vector<Node*> route);

        /**
         * Outputs the background image and all modifications done to it (added points, paths)
         * to the desired filename ending in png.
         * 
         * @param filename desired name for output PNG file
         */
        void print(string filename);

    private:

        /**
         * Converts the given longitude into an appropriate X coordinate on the PNG image
         * under the assumption that the PNG image passed to the constructor is a centered
         * mercator map. Used by addPoint.
         * 
         * @param longitude longitude value to be converted
         * @returns x-coordinate on the PNG space as a double
         */
        double longToX(double longitude);

        /**
         * Converts the given latitude into an appropriate Y coordinate on the PNG image
         * under the assumption that the PNG image passed to the constructor is a centered
         * mercator map. Used by addPoint.
         * 
         * @param latitude latitude value to be converted
         * @returns y-coordinate on the PNG space as a double
         */
        double latToY(double latitude);

        /**
         * Obsolete private variable previously used for testing and kept in order for tests
         * to work. Does not serve any purpose at this point.
         */
        Graph graph_;

        /**
         * Background PNG that the MapPrinter object prints points and paths on. This PNG
         * should be a centered Mercator map of the world in order for this algorithm
         * to function as intended.
         */
        PNG png_;

        /**
         * Flag used to determine which inputted node is the starting point in order to give
         * it a different color.
         */
        bool firstDone_ = false;

        /**
         * Used to print the last node inputted to the mapprinter object a distinct color.
         */
        Node lastPoint_;
};