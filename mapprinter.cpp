#include "mapprinter.h"
#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <math.h>

using namespace cs225;
using namespace std;


/** 
 * This is the default constructor which uses background.png by default as the background.
 */
MapPrinter::MapPrinter() {
    PNG background;
    background.readFromFile("background.png");
    png_ = background;
}

/** 
 * This constructor allows for a custom image to be passed as a background. However,
 * this class will only function as intended if a PNG of a centered mercator world map
 * is used.
 * 
 * @param background PNG object to be used for printing instead of the default 
 */
MapPrinter::MapPrinter(PNG background) {
    graph_ = Graph();
    png_ = background;
}

/** 
 * This constructor is the same as the one argument constructor and has no special
 * function other than testing. The graph is unused in the algorithm.
 * 
 * @param graph graph object passed in for testing, obsolete argument
 * @param background PNG object to be used for printing instead of the default 
 */
MapPrinter::MapPrinter(Graph graph, PNG background) {
    graph_ = graph;
    png_ = background;
}

/**
 * Adds the given airport Node onto the PNG map as a dot using its latitude and longitude.
 * The first point printed is purple to indicate the starting point and the last point printed
 * is green to indicate the ending point of the route. The starting and ending points are also
 * squares instead of circles just as an added distinction. All other middle points are red
 * and circular.
 * 
 * @param node node to be printed onto the PNG image in the mapprinter object
 */
void MapPrinter::addPoint(Node node) {
    if (firstDone_ == false) {
        addPoint(node, 290.0, 1.0, 0.5, 2);
        firstDone_ = true;
        return;
    } 
    double latitude = node.latitude();
    double longitude = node.longitude();
    int x = (int) longToX(longitude);
    int y = (int) latToY(latitude);

    HSLAPixel& pixel1 = png_.getPixel((int) x, (int) y);
    pixel1.h = 0.0;
    pixel1.s = 1.0;
    pixel1.l = 0.5;
    pixel1.a = 1.0;
    
    for (int i = -9 ; i <= 9; i++) {
        for (int j = -9; j <= 9; j++) {
            if ((abs(i) + abs(j)) <= 13) {
                HSLAPixel& pixel2 = png_.getPixel(x+i, y+j);
                pixel2.h = 0.0;
                pixel2.s = 1.0;
                pixel2.l = 0.5;
                pixel2.a = 1.0;
            }
        }
    }
    lastPoint_ = node;
}

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
void MapPrinter::addPoint(Node node, double h, double s, double l, int sizeInc) { 
    double latitude = node.latitude();
    double longitude = node.longitude();
    int x = (int) longToX(longitude);
    int y = (int) latToY(latitude);

    HSLAPixel& pixel1 = png_.getPixel((int) x, (int) y);
    pixel1.h = h;
    pixel1.s = s;
    pixel1.l = l;
    pixel1.a = 1.0;
    
    for (int i = (-9 - sizeInc) ; i <= (9 + sizeInc); i++) {
        for (int j = -9-sizeInc; j <= 9+sizeInc; j++) {
            if ((abs(i) + abs(j)) <= 100) {
                HSLAPixel& pixel2 = png_.getPixel(x+i, y+j);
                pixel2.h = h;
                pixel2.s = s;
                pixel2.l = l;
                pixel2.a = 1.0;
            }
        }
    }
}

/**
 * Adds a linear path from one point to another on the map PNG about 2 pixels in thickness
 * using the passed Edge.
 * The path is always red (0, 100%, 50%, 100% in HSLA) in color. This function automatically prints
 * two points in the Edge object on the map as well.
 * 
 * @param edge path to be printed onto the PNG image along with its nodes
 */
void MapPrinter::addPath(Edge edge) { 
    Node* node1 = edge.start();
    Node* node2 = edge.end();

    double latitude1 = node1->latitude();
    double longitude1 = node1->longitude();
    double latitude2 = node2->latitude();
    double longitude2 = node2->longitude();
    
    int x1 = floor(longToX(longitude1));
    int y1 = floor(latToY(latitude1));
    int x2 = floor(longToX(longitude2));
    int y2 = floor(latToY(latitude2));

    addPoint(*node1);
    addPoint(*node2);

    double neg = 0.0;

    if (latitude2 - latitude1 < 0) neg = neg + 1.0;
    if (longitude2 - longitude1 < 0) neg = neg + 1.0;

    double slope = (double) abs((1.0*(y2 - y1)) / (1.0*(x2 - x1)));
    double invSlope;
    if (x1 > x2) invSlope = -1.0;
    if (x2 > x1) invSlope = 1.0;
    if (y2 < y1) slope = slope * -1.0;

    for (int i = 0; i < 1000; i++) {
        HSLAPixel& pixel1 = png_.getPixel((int) (x1 + (i*invSlope)), (int) (y1 + i*slope));
        pixel1.h = 0.0;
        pixel1.s = 1.0;
        pixel1.l = 0.5;
        pixel1.a = 1.0;
        HSLAPixel& pixel2 = png_.getPixel((int) (x1 + (i*invSlope)), (int) (y1 + i*slope + 1));
        pixel2.h = 0.0;
        pixel2.s = 1.0;
        pixel2.l = 0.5;
        pixel2.a = 1.0;
        if (abs(slope) > 2) {
            for (int j = 0; j < (int) (slope - 1); j++) {
                HSLAPixel& pixel2 = png_.getPixel((int) (x1 + (i*invSlope)), (int) (y1 + i*slope + 1 + j));
                pixel2.h = 0.0;
                pixel2.s = 1.0;
                pixel2.l = 0.5;
                pixel2.a = 1.0;
            }
        }
        if ((abs((x1 + (i*invSlope)) - x2) < 0.5) || (abs((y1 + (y1*invSlope)) - y2) < 0.5)) break;
    }
}

/**
 * Adds an entire route onto the map PNG by adding all the points and paths using
 * the Node* objects in the vector. The order of the Node* objects determines the paths printed
 * between the points on the map.
 * 
 * @param route array of Nodes to be added, in order, stored in a vector
 */
void MapPrinter::addRoute(vector<Node*> route) {
    if (route.size() == 0) return;
    if (route.size() == 1) {
        addPoint(*route[0]);
        return;
    }
    for (unsigned long i = 0; i < (route.size()-1); i++) {
        Edge edge = Edge(route[i], route[i+1]);
        addPath(edge);
    }
}

/**
 * Outputs the background image and all modifications done to it (added points, paths)
 * to the desired filename ending in png.
 * 
 * @param filename desired name for output PNG file
 */
void MapPrinter::print(string filename) {
    addPoint(lastPoint_, 110.0, 1, 0.5, 2);
    png_.writeToFile(filename);
    cout << "Map saved to " << filename << endl;
}

/**
 * Converts the given longitude into an appropriate X coordinate on the PNG image
 * under the assumption that the PNG image passed to the constructor is a centered
 * mercator map. Used by addPoint.
 * 
 * @param longitude longitude value to be converted
 * @returns x-coordinate on the PNG space as a double
 */
double MapPrinter::longToX(double longitude) {
    int pngWidth = png_.width();
    
    double x = fmod((pngWidth*(180+longitude)/360), (pngWidth + (pngWidth/2)));
    return x;
}

/**
 * Converts the given latitude into an appropriate Y coordinate on the PNG image
 * under the assumption that the PNG image passed to the constructor is a centered
 * mercator map. Used by addPoint.
 * 
 * @param latitude latitude value to be converted
 * @returns y-coordinate on the PNG space as a double
 */
double MapPrinter::latToY(double latitude) {
    int pngWidth = png_.width();
    int pngHeight = png_.height();

    double latInRadians = latitude * M_PI / 180;
    double mercN = log(tan((M_PI/4) + latInRadians/2));
    double y = pngHeight/2 - pngWidth*mercN/(2*M_PI);
    return y;
}
