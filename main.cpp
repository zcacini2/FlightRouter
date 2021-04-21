#include "BFS.h"
#include "Graph.h"
#include "Node.h"
#include <string>
#include <iostream>

int main() {
    //const int& testint = 5;
    const std::string& filename1 = "tests/routesDataSmall.txt";
    Graph graph1(filename1);
    BFS test(graph1, Node(1, -6.081689834590001, 145.391998291));
    test.traverse();

    return 0;
}