#include "BFS.h"
#include "Graph.h"
#include "Node.h"
#include "mapprinter.h"
#include "cs225/PNG.h"

#include <string>
#include <iostream>

int main() {

    std::cout << "Initializing..." << std::endl;
    //Graph graph("dataset/routes.txt", "dataset/airports.txt");
    std::cout << "Initializion Complete." << std::endl;
    std::cout << std::endl;
    std::cout << "Hello, and welcome to FlightRouter!" << std::endl; // << std::endl;
    std::cout << "We are a flight routing platform that has access to over 10,000 airports and over 60,000 flight routes." << std::endl;
    std::cout << "Using this data, we are able to provide you with the shortest route between any two airports in the world! "; // << std::endl;
    std::cout << "Our platform provides both a listing of airports to travel through and a graphical map output to aid your travels." << std::endl;
    std::cout << std::endl;
    std::cout << "What is your origin airport? (Please input a valid airport code found in the ReadME file)" << std::endl;

    int origin;
    bool valid = false;
    std::cin >> origin;
    
    std::cout << "You have chosen " << origin << " as your origin airport. Is this correct?" << std::endl;


    /*const std::string& filename1 = "tests/routesDataSmall.txt";
    Graph graph1(filename1);
    BFS test(graph1, (graph1.getFirstNode()));
    test.traverse();

    const std::string& filename2 = "dataset/routes.txt";
    Graph graph2(filename2);
    BFS bfs2(graph2, (graph2.getFirstNode()));
    bfs2.traverse();*/

    return 0;
}
