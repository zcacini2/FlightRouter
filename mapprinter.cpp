#include "mapprinter.h"
#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

//#include <graphics.h>
#include <math.h>

using namespace cs225;
using namespace std;

MapPrinter::MapPrinter() { }

MapPrinter::MapPrinter(Graph graph, PNG background) {
    graph_ = graph;
    png_ = background;
}

void MapPrinter::addPoint(Node node) { 
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
}

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
    

}

void MapPrinter::print(string filename) {
    png_.writeToFile(filename);
}

double MapPrinter::longToX(double longitude) {
    int pngWidth = png_.width();
    
    double x = fmod((pngWidth*(180+longitude)/360), (pngWidth + (pngWidth/2)));
    return x;
}

double MapPrinter::latToY(double latitude) {
    int pngWidth = png_.width();
    int pngHeight = png_.height();

    double latInRadians = latitude * M_PI / 180;
    double mercN = log(tan((M_PI/4) + latInRadians/2));
    double y = pngHeight/2 - pngWidth*mercN/(2*M_PI);
    return y;
}
