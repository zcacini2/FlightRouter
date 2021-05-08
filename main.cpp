#include "BFS.h"
#include "Graph.h"
#include "Node.h"
#include "mapprinter.h"
#include "cs225/PNG.h"
#include "Airports.h"

#include <string>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


bool isValidAirport(Airports airports, int airportCode, Graph graph) {

    if (airportCode < 0 || airportCode > 14110) {
        return false;
    } else if (airports.latitude(airportCode) == -1000) {
        return false;
    } 
    
    Node* node = graph.getNode(airportCode);
    if (node->neighbors().size() == 0) {
        std::cout << airports.name(airportCode) << " has no provided routes to any other airport. Please choose a different airport." << std::endl;
        return false;
    }

    return true;
}

bool isValidAirportSuppressedOutput(Airports airports, int airportCode, Graph graph) {

    if (airportCode < 0) {
        return false;
    } else if (airports.latitude(airportCode) == -1000) {
        return false;
    } 
    
    Node* node = graph.getNode(airportCode);
    if (node->neighbors().size() == 0) {
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

    /*
    // Initialize Graph and Airports. Provide prompt for user to specify data
    std::cout << "Initializing..." << std::endl;
    //Graph graph("tests/routesDataMedium.txt", "tests/airportsDataMedium.txt");
    Graph graph("dataset/routes.txt", "dataset/airports.txt");
    //Airports airports("tests/airportsDataMedium.txt");
    Airports airports("dataset/airports.txt");
    std::cout << "Initializion Complete." << std::endl;
    std::cout << std::endl;
    */

    std::cout << "Hello, and welcome to FlightRouter!" << std::endl;
    std::cout << "We are a flight routing platform that has access to over 10,000 airports and over 60,000 flight routes." << std::endl;
    std::cout << "Using this data, we are able to provide you with the shortest route between any two airports in the world! "; // << std::endl;
    std::cout << "Our platform provides both a listing of airports to travel through and a graphical map output to aid your travels." << std::endl;
    std::cout << std::endl;

    // Initialize Graph and Airports. Provide prompt for user to specify data
    std::cout << "Please specify an airports dataset to use for this program. Your input must correctly include the filepath as well." << std::endl;
    std::cout << "(Input 0 if you would like to default to the full dataset or 1 if you would like to use a shortened dataset)" << std::endl; 
    std::cout << "NOTE: The program will likely seg fault if your data doesn't match the formatting of airports.txt" << std::endl;
    std::cout << std::endl;

    std::string filepath;
    std::cin >> filepath;

    while (std::cin.fail()) {
        std::cout << "You have entered an invalid filepath. Please enter a valid stirng filepath for your dataset." << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> filepath;
    }

    Airports airports;
    if (filepath == "0") {
        std::cout << "You have chosen to use the full airports dataset." << std::endl;
        std::cout << "Initializing Airports..." << std::endl;
        Airports airportsME("dataset/airports.txt");
        airports = airportsME;
        std::cout << "Airports initialization complete." << std::endl;
        std::cout << std::endl;
    } else if (filepath == "1") {
        std::cout << "You have chosen to use a shorted airports dataset (tests/airportsDataMedium.txt)." << std::endl;
        std::cout << "Initializing Airports..." << std::endl;
        Airports airportsME("tests/airportsDataMedium.txt");
        airports = airportsME;
        std::cout << "Airports initialization complete." << std::endl;
        std::cout << std::endl;
    } else {
        std::cout << "You have chosen to use " << filepath << " as your airports dataset." << std::endl;
        std::cout << "Initializing Airports..." << std::endl;
        Airports airportsME(filepath);
        airports = airportsME;
        std::cout << "Airports initialization complete." << std::endl;
        std::cout << std::endl;
    }

    /*
    std::cout << "Initializing..." << std::endl;
    //Graph graph("tests/routesDataMedium.txt", "tests/airportsDataMedium.txt");
    Graph graph("dataset/routes.txt", "dataset/airports.txt");
    //Airports airports("tests/airportsDataMedium.txt");
    //Airports airports("dataset/airports.txt");
    std::cout << "Initializion Complete." << std::endl;
    std::cout << std::endl;
    */

    // Initialize Graph. Provide prompt for user to specify data
    std::cout << "Please specify an routes dataset to use for this program. Your input must correctly include the filepath as well." << std::endl;
    std::cout << "(Input 0 if you would like to default to the full dataset or 1 if you would like to use a shortened dataset)" << std::endl; 
    std::cout << "WARNING: The program will seg fault if your data doesn't match the formatting of routes.txt OR if your routes data doesn't correspond to the EXACT SAME airports data as you input above." << std::endl;
    std::cout << std::endl;

    std::string filepath2;
    std::cin >> filepath2;

    while (std::cin.fail()) {
        std::cout << "You have entered an invalid filepath. Please enter a valid string filepath for your dataset." << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> filepath2;
    }

    Graph graph;
    if (filepath2 == "0") {
        std::cout << "You have chosen to use the full routes dataset." << std::endl;
        std::cout << "Initializing routes..." << std::endl;
        Graph graphME("dataset/routes.txt", "dataset/airports.txt");
        graph = graphME;
        std::cout << "Routes initialization complete." << std::endl;
        std::cout << std::endl;
    } else if (filepath2 == "1") {
        std::cout << "You have chosen to use a shorted routes dataset (tests/routesDataMedium.txt)." << std::endl;
        std::cout << "Initializing routes..." << std::endl;
        Graph graphME("tests/routesDataMedium.txt", "tests/airportsDataMedium.txt");
        graph = graphME;
        std::cout << "Routes initialization complete." << std::endl;
        std::cout << std::endl;
    } else {
        std::cout << "You have chosen to use " << filepath2 << " as your routes dataset." << std::endl;
        std::cout << "Initializing routes..." << std::endl;
        Graph graphME(filepath2, filepath);
        graph = graphME;
        std::cout << "Routes initialization complete." << std::endl;
        std::cout << std::endl;
    }

    // Suggesting a few airports.
    std::srand(time(NULL));
    int num = std::rand() % airports.size();
    int num2 = std::rand() % airports.size();

    while (!isValidAirportSuppressedOutput(airports, num, graph)) {
        num = std::rand() % airports.size();
    }

    while (!isValidAirportSuppressedOutput(airports, num2, graph)) {
        num2 = std::rand() % airports.size();
    }

    std::cout << "What is your origin airport? (Please input a valid airport code found in the ReadME file)" << std::endl; 
    std::cout << "Some examples include " << airports.name(num) << " (" << num << ") or " <<  airports.name(num2) << " (" << num2 << ")" << std::endl;
    std::cout << std::endl;

    // Take in origin airport and provide invalid input protections
    int origin;
    std::cin >> origin;

    while (std::cin.fail() || !isValidAirport(airports, origin, graph)) {
        std::cout << "You have entered an invalid airport code. Please enter a valid integer aiport code from the ReadME file included on GitHub." << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> origin;
    }

    // Give user a chance to change their mind. Input protections
    std::cout << "You have chosen " << airports.name(origin) << " (" << origin <<  ") as your origin airport. Is this correct? (Enter 1 if yes, 0 if no)" << std::endl;
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
        while (std::cin.fail() || !isValidAirport(airports, origin, graph)) {
            std::cout << "You have entered an invalid airport code. Please enter a valid integer aiport code from the ReadME file included on GitHub" << std::endl;
            std::cin.clear();
            std::cin.ignore(256,'\n');
            std::cin >> origin;
        }
    }

    // Prompt user to input destination airport with input protections
    int dest;
    std::cout << "You have confirmed " << airports.name(origin) << " (" << origin <<  ") as your origin airport." << std::endl;
    std::cout << std::endl;

    num = std::rand() % airports.size();
    while (!isValidAirportSuppressedOutput(airports, num, graph)) {
        num = std::rand() % airports.size();
    }

    num2 = std::rand() % airports.size();
    while (!isValidAirportSuppressedOutput(airports, num2, graph)) {
        num2 = std::rand() % airports.size();
    }

    std::cout << "What is your destination airport? (Please input a valid airport code found in the ReadME file)" << std::endl;
    std::cout << "Some examples include " << airports.name(num) << " (" << num << ") or " <<  airports.name(num2) << " (" << num2 << ")" << std::endl;
    std::cout << std::endl;
    std::cin >> dest;

    while (std::cin.fail() || !isValidAirport(airports, dest, graph)) {
        std::cout << "You have entered an invalid airport code. Please enter a valid integer aiport code from the ReadME file included on GitHub" << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> dest;
    }

    // Confirm and allow user to change mind, with input protections
    std::cout << "You have chosen " << airports.name(dest) << " (" << dest <<  ") as your destination airport. Is this correct? (Enter 1 if yes, 0 if no)" << std::endl;
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
        while (std::cin.fail() || !isValidAirport(airports, dest, graph)) {
            std::cout << "You have entered an invalid airport code. Please enter a valid integer aiport code from the ReadME file included on GitHub" << std::endl;
            std::cin.clear();
            std::cin.ignore(256,'\n');
            std::cin >> dest;
        }
    }

    // Confirmation Message
    std::cout << "You have confirmed " << airports.name(origin) << " (" << origin <<  ") as your origin airport and " << airports.name(dest) << " (" << dest <<  ") as your destination airport." << std::endl;
    std::cout << std::endl;

    // Find shortest path
    vector<Node*> route = graph.shortestPath(origin, dest);

    // Output route
    std::cout << "The shortest route between " << origin << " and " << dest << ":" << std::endl;
    for (unsigned i = 0; i < route.size() - 1; i++) { 
        std::cout << airports.name(route[i]->airportCode()) << " (" << route[i]->airportCode() << ") -> ";
    }
    std::cout << airports.name(route[route.size() - 1]->airportCode()) << " (" << route[route.size() - 1]->airportCode() << ")" << std::endl;
    std::cout << std::endl;

    // Output route distance
    double distance = route[1]->getRouteDistance(route);
    std::cout << "The shortest path has a length of " << distance << " kilometers." << std::endl;
    std::cout << std::endl;

    // Prompt user to input output file name
    std::cout << "Please enter where you would like to store the map route drawing." << std::endl;
    std::cout << "(Format your input as a string including complete file route and .png. Enter 0 to default to output.png)" << std::endl;
    std::cout << std::endl;

    // Input protections
    string filename;
    cin >> filename;
    while (std::cin.fail()) {
        std::cout << "You have entered an invalid filename. Please follow thr directions above to input your desired output file name." << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> filename;
    }

    // If user decides default
    if (filename == "0") {
        filename = "output.png";
    }
    std::cout << std::endl;

    // Draw map and save to filename
    PNG background;
	background.readFromFile("background.png");
	MapPrinter map(graph, background);
    
    map.addRoute(route);
    map.print(filename);
    std::cout << std::endl;

    // Direct user to open file to see the route
    std::cout << "The shortest path between " << origin << " and " << dest << " is displayed above. To view the path on a map, please open " << filename << std::endl;
    std::cout << "Thank you for using FlightRouter! If you would like to route another trip, please simply type in ./finalproj after this message!" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    return 0;
}
