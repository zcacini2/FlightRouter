#include "mapprinter.h"
#include "Graph.h"
#include "Node.h"
#include "cs225/PNG.h"

using namespace cs225;
using namespace std;

MapPrinter::MapPrinter() { }

MapPrinter::MapPrinter(Graph graph, PNG background) {
    graph_ = graph;
    png_ = background;
}

void MapPrinter::addPoint(Node node) { 
    //take node lat and long
    //use algorithm/code (stackoverflow) to convert lat/long to desirable pixels on map
    //add said pixels to png
    //
}

void MapPrinter::addPath() { }

void MapPrinter::print(string filename) {
    png_.writeToFile(filename);
}
