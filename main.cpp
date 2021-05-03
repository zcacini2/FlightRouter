#include "BFS.h"
#include "Graph.h"
#include "Node.h"
#include "mapprinter.h"
#include "cs225/PNG.h"
#include "Airports.h"

#include <string>
#include <iostream>

bool isValidAirport(Airports airports, int airportCode) {
    
    if (airportCode < 0) {
        return false;
    } else if (airports.latitude(airportCode) == -1000) {
        return false;
    }

    return true;
}

bool isOneOrZero(int num) {
    if (num == 1 || num == 0) {
        return true;
    }
    return false;
}

int main() {

    std::cout << "Initializing..." << std::endl;
    //Graph graph("dataset/routes.txt", "dataset/airports.txt");
    Airports airports("dataset/airports.txt");
    std::cout << "Initializion Complete." << std::endl;
    std::cout << std::endl;
    std::cout << "Hello, and welcome to FlightRouter!" << std::endl; // << std::endl;
    std::cout << "We are a flight routing platform that has access to over 10,000 airports and over 60,000 flight routes." << std::endl;
    std::cout << "Using this data, we are able to provide you with the shortest route between any two airports in the world! "; // << std::endl;
    std::cout << "Our platform provides both a listing of airports to travel through and a graphical map output to aid your travels." << std::endl;
    std::cout << std::endl;
    std::cout << "What is your origin airport? (Please input a valid airport code found in the ReadME file)" << std::endl;

    int origin;
    std::cin >> origin;

    while (std::cin.fail() || !isValidAirport(airports, origin)) {
        std::cout << "You have entered an invalid airport code. Please enter a valid integer aiport code from the ReadME file included on GitHub" << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> origin;
    }

    std::cout << "You have chosen " << origin << " as your origin airport. Is this correct? (Enter 1 if yes, 0 if no)" << std::endl;
    int valid;
    std::cin >> valid;

    while (std::cin.fail() || !isOneOrZero(valid)) {
        std::cout << "You have entered an invalid response. Please enter 1 if " << origin << " is your desired origin airport or 0 if it is not" << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> valid;
    }

    if (valid == 0) {
        std::cout << "Please reenter your desired origin airport code (Enter a valid integer aiport code from the ReadME file included on GitHub)" << std::endl;
        std::cin >> origin;
        while (std::cin.fail() || !isValidAirport(airports, origin)) {
            std::cout << "You have entered an invalid airport code. Please enter a valid integer aiport code from the ReadME file included on GitHub" << std::endl;
            std::cin.clear();
            std::cin.ignore(256,'\n');
            std::cin >> origin;
        }
    }


    int dest;
    std::cout << "You have confirmed " << origin << " as your origin airport." << std::endl;
    std::cout << "What is your destination airport? (Please input a valid airport code found in the ReadME file)" << std::endl;
    std::cin >> dest;

    while (std::cin.fail() || !isValidAirport(airports, dest)) {
        std::cout << "You have entered an invalid airport code. Please enter a valid integer aiport code from the ReadME file included on GitHub" << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> dest;
    }

    std::cout << "You have chosen " << dest << " as your destination airport. Is this correct? (Enter 1 if yes, 0 if no)" << std::endl;
    int valid2;
    std::cin >> valid2;

    while (std::cin.fail() || !isOneOrZero(valid2)) {
        std::cout << "You have entered an invalid response. Please enter 1 if " << dest << " is your desired origin airport or 0 if it is not" << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> valid2;
    }

    if (valid2 == 0) {
        std::cout << "Please reenter your desired destination airport code (Enter a valid integer aiport code from the ReadME file included on GitHub)" << std::endl;
        std::cin >> dest;
        while (std::cin.fail() || !isValidAirport(airports, dest)) {
            std::cout << "You have entered an invalid airport code. Please enter a valid integer aiport code from the ReadME file included on GitHub" << std::endl;
            std::cin.clear();
            std::cin.ignore(256,'\n');
            std::cin >> dest;
        }
    }

    std::cout << "You have confirmed " << origin << " as your origin airport and " << dest << " as your destination airport." << std::endl;


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
