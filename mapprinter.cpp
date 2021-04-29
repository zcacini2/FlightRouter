#include "mapprinter.h"
#include "Graph.h"
#include "Node.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

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
    double x = longToX(longitude);
    double y = latToY(latitude);

    HSLAPixel& pixel1 = png_.getPixel((int) x, (int) y);
    pixel1.h = 0.0;
    pixel1.s = 0.5;
    pixel1.l = 0.5;
    pixel1.a = 1.0;
}

void MapPrinter::addPath() { }

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
