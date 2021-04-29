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
        void addPath();
        void print(string filename);
    private:
        Graph graph_;
        PNG png_;
};