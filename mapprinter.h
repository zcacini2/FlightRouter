#pragma once

#include "Graph.h"
#include "cs225/PNG.h"
#include "Node.h"

using namespace cs225;
using namespace std;

class MapPrinter {
    public:
        MapPrinter();
        MapPrinter(Graph graph, PNG background);
        void addPoint(Node);
        void addPath(Edge edge);
        void print(string filename);
        double longToX(double longitude);
        double latToY(double latitude);
    private:
        Graph graph_;
        PNG png_;
};