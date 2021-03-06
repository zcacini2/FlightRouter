#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "../catch/catch.hpp"
#include "../readFromFile.hpp"
#include "../Node.h"
#include "../Edge.h"
#include "../Airports.h"
#include "../Graph.h"
#include "../BFS.h"
#include "../cs225/PNG.h"
#include "../mapprinter.h"
#include "../cs225/HSLAPixel.h"

using namespace std;
using namespace cs225;

TEST_CASE("Verify that file_to_string works on a small example", "[readFile][1]") {
	std::string res = file_to_string("tests/smallSample.txt");
	// always check "expected" == "actual" --> be consistent

	//std::cout << res << std::endl;
	REQUIRE("hello\nstudents\nof\ncs\n225\n!!!\n" == res);
}

TEST_CASE("Verify that file_to_vector works on a small example", "[readFile][2]") {
	std::vector<std::string> res = file_to_vector("tests/smallSample.txt");
	std::string expected[] = {"hello", "students", "of", "cs", "225", "!!!"};

	/*
	for (unsigned i = 0; i < res.size(); i++) {
		std::cout << res[i] << std::endl;
	}
	*/
	
	REQUIRE(6 == res.size());

	for (int i = 0; i < (int) res.size(); i++) {
		REQUIRE(expected[i] == res[i]);
	}
}

TEST_CASE("Check Airports ctor populates lat_long correctly", "[airports][1]") {
	Airports airports("tests/airportsDataSmall.txt");

	REQUIRE(airports.latitude(1) == -6.081689834590001);
	REQUIRE(airports.latitude(2) == -5.20707988739);
	REQUIRE(airports.latitude(3) == -5.826789855957031);
	REQUIRE(airports.longitude(1) == 145.391998291);
	REQUIRE(airports.longitude(2) == 145.789001465);
	REQUIRE(airports.longitude(3) == 144.29600524902344);

	std::cout << "Airports class populates lat_long member variable correctly on small data set" << std::endl;
}

TEST_CASE("Check Airports ctor with full data", "[airports][2]") {
	Airports airports("dataset/airports.txt");

	REQUIRE(airports.latitude(45) == 49.21080017089844);
	REQUIRE(airports.latitude(426) == 61.24919891357422);
	REQUIRE(airports.latitude(468) == 55.04280090332031);
	REQUIRE(airports.longitude(3348) == 114.088996887);
	REQUIRE(airports.longitude(3675) == -87.395401001);
	REQUIRE(airports.longitude(6712) == -151.7429962);
	REQUIRE(airports.longitude(14110) == 35.305);

	std::cout << "Airports class populates lat_long member variable correctly on full data set" << std::endl;
}

TEST_CASE("Check Airports ctor populates names correctly", "[airports][3]") {
	Airports airports("tests/airportsDataSmall.txt");

	REQUIRE(airports.name(1) == "Goroka Airport");
	REQUIRE(airports.name(2) == "Madang Airport");
	REQUIRE(airports.name(3) == "Mount Hagen Kagamuga Airport");

	std::cout << "Airports class populates names member variable correctly on small data set" << std::endl;
}

TEST_CASE("Check Airports ctor populates names with full data", "[airports][4]") {
	Airports airports("dataset/airports.txt");

	REQUIRE(airports.name(45) == "Deer Lake Airport");
	REQUIRE(airports.name(426) == "Immola Airport");
	REQUIRE(airports.name(468) == "City of Derry Airport");

	std::cout << "Airports class populates names member variable correctly on full data set" << std::endl;
}

TEST_CASE("Check Airports ctor populates with correct size", "[airports][5]") {
	Airports airports("dataset/airports.txt");

	// size should be equal to one greater than largest airport code
	REQUIRE(airports.size() == 14111);

	std::cout << "Airports class populates with correct size on full data set" << std::endl;
}


TEST_CASE("Check that Edge class calculates distance correctly (requires Node and Edge to work)", "[edge][1]") {
	//sample lat long coordinates from google
	Node* ORD = new Node(3830, 41.9773, -87.8369); //chicago
	Node* JFK = new Node(3797, 40.6413, -73.5581); //NY
	Node* ICN = new Node(3930, 37.4602, 126.4407); //icheon
	Node* HND = new Node(2359, 35.5494, 139.7798); //tokyo
	Node* CMI = new Node(4049, 40.0365, -88.2640); //champaign

	Edge ORDtoJFK(ORD, JFK);
	Edge ORDtoICN(ORD, ICN);
	Edge JFKtoORD(JFK, ORD);
	Edge ORDtoORD(ORD, ORD);
	Edge ORDtoHND(ORD, HND);
	Edge CMItoORD(CMI, ORD);

	//calculated using https://www.nhc.noaa.gov/gccalc.shtml using coords above, truncated
	int expected1 = 1200; 
	int expected2 = 218;
	int expected3 = 1200;
	int expected4 = 0;

	REQUIRE((int) ORDtoJFK.distance() == expected1);
	REQUIRE(ORDtoICN.distance() > ORDtoHND.distance());
	REQUIRE((int) JFKtoORD.distance() == expected3);
	REQUIRE((int) ORDtoORD.distance() == expected4);
	REQUIRE((int) CMItoORD.distance() == expected2);

	std::cout << "Edge class calculates distance correctly" << std::endl;
}

TEST_CASE("Edge populates with correct start and end nodes", "[edge][2]") {
	Node* ORD = new Node(3830, 41.9773, -87.8369); //chicago
	Node* JFK = new Node(3797, 40.6413, -73.5581); //NY

	Edge ORDtoJFK(ORD, JFK);

	REQUIRE(ORDtoJFK.start() == ORD);
	REQUIRE(ORDtoJFK.end() == JFK);
}

TEST_CASE("Test functionality of areNeighbors", "[node][1]") {
	Node* node1 = new Node(123, 65.666, 34.44);
	Node* node2 = new Node(345, -65.22, 90.4565);

	node1->addNeighbor(node2);

	REQUIRE(node1->neighbors().size() == 1);
	REQUIRE(node2->neighbors().size() == 0);

	delete node1;
	delete node2;

	std::cout << "Node::areNeighbors functions correctly" << std::endl;
}

TEST_CASE("testNodeDistance" , "[node][2]") {
	Node* ORD = new Node(3830, 41.9773, -87.8369); //chicago
	Node* JFK = new Node(3797, 40.6413, -73.5581); //NY
	Node* ICN = new Node(3930, 37.4602, 126.4407); //icheon
	Node* HND = new Node(2359, 35.5494, 139.7798); //tokyo
	Node* CMI = new Node(4049, 40.0365, -88.2640); //champaign
	
	int expected1 = 1200; 
	int expected2 = 218;
	int expected3 = 1200;
	int expected4 = 0;

	REQUIRE((int) ORD->distance(JFK) == expected1);
	REQUIRE((int) JFK->distance(ORD) == expected3);
	REQUIRE((int) ORD->distance(ORD) == expected4);
	REQUIRE((int) CMI->distance(ORD) == expected2);

	delete ORD;
	delete JFK;
	delete ICN;
	delete HND;
	delete CMI;

	std::cout << "Node::distance() functions correctly" << std::endl;
}

TEST_CASE("Test sample data on Graph Ctor", "[graph][1]") {
	Graph graph("tests/routesSimpleDataSmall.txt", "tests/airportsDataSmall.txt");
	vector<Node*> nodes = graph.getNodes();
	vector<Edge> edges = graph.getEdges(); 

	double expectedLat1 = -6.081689834590001;
	double expectedLat2 = -5.20707988739; 
	double expectedLat3 = -5.826789855957031;

	REQUIRE(nodes[1]->latitude() == expectedLat1);
	REQUIRE(nodes[2]->latitude() == expectedLat2);
	REQUIRE(nodes[3]->latitude() == expectedLat3);

	REQUIRE(edges[0].start()->latitude() == expectedLat1);
	REQUIRE(edges[1].start()->latitude() == expectedLat2);
	REQUIRE(edges[2].start()->latitude() == expectedLat3);

	std::cout << "Graph constructor functions correctly on small data set" << std::endl;
}

TEST_CASE("Graph Ctor simple data maintains neighbors correctly", "[graph][2]") {

	Graph graph("tests/routesSimpleDataSmall.txt", "tests/airportsDataSmall.txt");
	vector<Node*> nodes = graph.getNodes();

	list<Node*> neigh1 = nodes[1]->neighbors();
	list<Node*> neigh2 = nodes[2]->neighbors();
	list<Node*> neigh3 = nodes[3]->neighbors();

	double lat1 = -6.081689834590001;
	double lat2 = -5.20707988739;
	double lat3 = -5.826789855957031;

	auto it = neigh1.begin();
 	REQUIRE((*it)->latitude() == lat2);
	++it;
	REQUIRE((*it)->latitude() == lat3);

	auto it2 = neigh2.begin();
	REQUIRE((*it2)->latitude() == lat1);
	++it2;
	REQUIRE((*it2)->latitude() == lat3);

	auto it3 = neigh3.begin();
	REQUIRE((*it3)->latitude() == lat2);
	++it3;
	REQUIRE((*it3)->latitude() == lat1);

	std::cout << "Graph Ctor simple data maintains neighbors correctly" << std::endl;
}

TEST_CASE("Graph Ctor maintains propor neighbors medium complexity", "[graph][3]") {

	/*routesDataMedium.txt
	2B,410,AER,2965,KZN,2990,,0,CR2
	2B,410,ASF,2966,KZN,2990,,0,CR2
	2B,410,ASF,2966,MRV,2962,,0,CR2
	2B,410,CEK,2968,KZN,2990,,0,CR2
	2B,410,CEK,2968,OVB,4078,,0,CR2
	2B,410,DME,4029,KZN,2990,,0,CR2
	2B,410,DME,4029,NBC,6969,,0,CR2

	Node and Neighbors
	0 2965 - 2990
	1 2990 - 2965, 2966, 2968, 4029
	2 2966 - 2990, 2962, 
	3 2962 - 2966, 
	4 2968 - 2990, 4078
	5 4078 - 2968,
	6 4029 - 2990 6969
	7 6969 - 4029,
	*/

	Graph graph("tests/routesDataMedium.txt", "dataset/airports.txt");
	vector<Node*> nodes = graph.getNodes();

	Node*& node2965 = nodes[2965];
	Node*& node2990 = nodes[2990];
	Node* node2966 = nodes[2966];
	Node* node2962 = nodes[2962];
	Node* node2968 = nodes[2968];
	Node* node4078 = nodes[4078];
	Node* node4029 = nodes[4029];
	Node* node6969 = nodes[6969];

	REQUIRE(node2965->neighbors().front()->airportCode() == 2990);

	REQUIRE(node2990->neighbors().front()->airportCode() == 2965);
	REQUIRE(node2990->neighbors().back()->airportCode() == 4029);

	REQUIRE(node2966->neighbors().front()->airportCode() == 2990);
	REQUIRE(node2966->neighbors().back()->airportCode() == 2962);

	REQUIRE(node2962->neighbors().front()->airportCode() == 2966);

	REQUIRE(node2968->neighbors().front()->airportCode() == 2990);
	REQUIRE(node2968->neighbors().back()->airportCode() == 4078);

	REQUIRE(node4078->neighbors().front()->airportCode() == 2968);

	REQUIRE(node4029->neighbors().front()->airportCode() == 2990);
	REQUIRE(node4029->neighbors().back()->airportCode() == 6969);

	REQUIRE(node6969->neighbors().front()->airportCode() == 4029);

	std::cout << "Graph Ctor maintains propor neighbors correctly (medium complexity)" << std::endl;
}

TEST_CASE("Graph Ctor doesn't add repeat nodes", "[graph][4]") {
	Graph graph("tests/routesRepeat.txt", "dataset/airports.txt");
	vector<Node*> nodes = graph.getNodes();

	Node*& node2965 = nodes[2965];
	Node*& node2990 = nodes[2990];
	Node* node4029 = nodes[4029];
	Node* node6969 = nodes[6969];

	REQUIRE(node4029->neighbors().front()->airportCode() == 6969);
	REQUIRE(node4029->neighbors().back()->airportCode() == 2990);
	REQUIRE(node6969->neighbors().size() == 1);

	REQUIRE(node2965->neighbors().size() == 1);
	REQUIRE(node2990->neighbors().size() == 4);

	std::cout << "Graph Ctor doesn't add repeat nodes" << std::endl;
}

TEST_CASE("Graph Ctor does nothing with null or invalid airports", "[graph][5]") {

	/*
	2B,410,AER,2965,KZN,2990,,0,CR2
	2B,410,AER,2965,KZN,2963,,0,CR2
	2B,410,AER,7167,KZN,2965,,0,CR2
	2B,410,ASF,2966,KZN,7167,,0,CR2

	2965 - 2990, 2963, not 7167
	2990 - 2965
	2963 - 2965
	7167 - nodes_[7167]->airportCode() == -1
	2966 - size = 0
	*/ 

	Graph graph("tests/routesInvalid.txt", "dataset/airports.txt");
	vector<Node*> nodes = graph.getNodes();

	// Ensure correct neighbros for 2965
	REQUIRE(nodes[2965]->neighbors().front()->airportCode() == 2990);
	REQUIRE(nodes[2965]->neighbors().back()->airportCode() == 2963);
	REQUIRE(nodes[2965]->neighbors().size() == 2);

	// Ensure no neighbors added to 2966
	REQUIRE(nodes[2966]->neighbors().size() == 0);

	// Ensure null node stored at 7167 in nodes_
	REQUIRE(nodes[7167]->airportCode() == -1);

	std::cout << "Graph Ctor does nothing with null or invalid airports" << std::endl;
}


TEST_CASE("Graph Ctor compiles on full data set", "[graph][6]") {
	Graph graph("dataset/routes.txt", "dataset/airports.txt");
	vector<Node*> nodes = graph.getNodes();
	vector<Edge> edges = graph.getEdges();

	/*
	1959 -> back = 4075
	4075 -> front  = 2006
	4075 -> back = 1978
	2913 -> back = 2912
	2912 -> back = 2913
	*/

	REQUIRE(nodes[1959]->neighbors().back()->airportCode() == 3361);
	REQUIRE(nodes[4075]->neighbors().front()->airportCode() == 2006);
	REQUIRE(nodes[4075]->neighbors().back()->airportCode() == 1978);
	REQUIRE(nodes[2913]->neighbors().back()->airportCode() == 2990);
	REQUIRE(nodes[2912]->neighbors().back()->airportCode() == 2990);

	std::cout << "Graph Ctor compiles on full data set" << std::endl;

}

TEST_CASE("BFS Traversal traverses through a Graph correctly", "[bfs]") {
	/*Graph graph1("tests/routesDataMedium.txt", "dataset/airports.txt");
	BFS bfs1(graph1, graph1.getFirstNode());
    vector<int> vector1 = bfs1.traverse();
	for (unsigned long i = 0; i < vector1.size(); i++) {
		cout << "vector1 " << vector1[i] << endl;
	}*/
	
	Graph* graph2 = new Graph("tests/smallRoutes2.txt", "tests/smallAirports2.txt");
	BFS bfs2(*graph2, graph2->getFirstNode());
	vector<int> vector2 = bfs2.traverse();
	vector<int> expected2{1, 2, 3, 4, 5, 6}; 
	for (unsigned long i = 0; i < vector2.size(); i++) {
		REQUIRE(expected2[i] == vector2[i]);
	}
	delete graph2;
	graph2 = nullptr;
	//delete bfs2;

	std::cout << "BFS Traversal traverses through a Graph correctly" << std::endl;
}

TEST_CASE("MapPrinter prints an input image with no modification", "[mapprinter][1]") {
	PNG background;
	Graph graph;
	background.readFromFile("background.png");
	MapPrinter mapprinter(graph, background);
	mapprinter.print("testSimple.png");

	std::cout << "MapPrinter prints an input image with no modification" << std::endl;
}

TEST_CASE("MapPrinter prints points/nodes on the input image", "[mapprinter][2]") {
	PNG background;
	Graph graph;
	background.readFromFile("background.png");
	MapPrinter mapprinter(graph, background);
	mapprinter.addPoint(Node(1, 0.0, 0.0));
	mapprinter.print("testOneIndpndntPoint.png");

	std::cout << "MapPrinter prints points/nodes on the input image" << std::endl;
}

TEST_CASE("MapPrinter prints a line", "[mapprinter][path][3]") {
	PNG background;
	Graph graph;
	Node* node1 = new Node(1, 50.0, 50.0);
	Node* node2 = new Node(2, -50.0, -50.0);
	Edge edge1(node1, node2);
	background.readFromFile("background.png");
	MapPrinter mapprinter(graph, background);
	mapprinter.addPath(edge1);
	mapprinter.print("testPath.png");

	delete node1;
	delete node2;

	std::cout << "MapPrinter prints a line correctly" << std::endl;
}

TEST_CASE("MapPrinter prints a route", "[mapprinter][route][4]") {
	Graph graph("tests/routesDataMedium.txt", "tests/airportsDataMedium.txt");
	vector<Node*> node = graph.getNodes();

	Node* node2966 = node[2966];
	Node* node6969 = node[6969];

	Node* node4078 = node[4078];
	Node* node2962 = node[2962];

	vector<Node*> route1 = graph.shortestPath(2966, 6969);
	vector<Node*> route2 = graph.shortestPath(4078, 2962);
	PNG background;
	background.readFromFile("background.png");
	MapPrinter mapprinter(graph, background);
	mapprinter.addRoute(route2);
	mapprinter.print("testRoute.png");

	std::cout << "MapPrinter prints a route correctly" << std::endl;

}

TEST_CASE("Test Dijkstra test on small data", "[dijkstra][1]") {
	Graph graph("tests/routesDataMedium.txt", "tests/airportsDataMedium.txt");
	vector<Node*> node = graph.getNodes();

	Node* node2966 = node[2966];
	Node* node6969 = node[6969];

	Node* node4078 = node[4078];
	Node* node2962 = node[2962];

	vector<Node*> route1 = graph.shortestPath(2966, 6969);
	vector<Node*> route2 = graph.shortestPath(4078, 2962);
	
	vector<Node*> expected1{node2966, node[2962], node6969};
	vector<Node*> expected2{node4078, node[2968], node[2990], node[2966], node2962}; 
	

	REQUIRE(route1.size() == expected1.size());
	REQUIRE(route2.size() == expected2.size());

	REQUIRE(route1[0]->airportCode() == 2966);
	REQUIRE(route1[1]->airportCode() == 2962);
	REQUIRE(route1[2]->airportCode() == 6969);

	REQUIRE(route2[0]->airportCode() == 4078);
	REQUIRE(route2[1]->airportCode() == 2968);
	REQUIRE(route2[2]->airportCode() == 2990);
	REQUIRE(route2[3]->airportCode() == 2966);
	REQUIRE(route2[4]->airportCode() == 2962);

	std::cout << "Dijkstra test on small data passes" << std::endl;

	/*
	Test Verification
	double D1 = node[2966]->distance(node[2990]);
	double D2 = node[2990]->distance(node[4029]);
	double D3 = node[4029]->distance(node[6969]);

	double D4 = node[2966]->distance(node[2962]);
	double D5 = node[2962]->distance(node[6969]);

	double totD1 = D1 + D2 + D3;
	double totD2 = D4 + D5;

	std::cout << "totD1 = " << totD1 << " and totD2 = " << totD2 << std::endl;

	double D6 = node[4078]->distance(node[2968]);
	double D7 = node[2968]->distance(node[2990]);
	double D8 = node[2990]->distance(node[4029]);
	double D9 = node[4029]->distance(node[6969]);
	double D10 = node[6969]->distance(node[2962]);

	double D11 = node[2990]->distance(node[2966]);
	double D12 = node[2966]->distance(node[2962]);

	double totD3 = D6 + D7 + D8 + D9 + D10;
	double totD4 = D6 + D7 + D11 + D12;

	std::cout << "totD3 = " << totD3 << " and totD4 = " << totD4 << std::endl;

	// Two Logical Routes between 2966 and 6969
	// Route 1: 2966 -D1-> 2990 -D2-> 4029 -D3-> 6969, Distance = D1 + D2 + D3 = 2648.47
	// Route 2: 2966 -D4-> 2962 -D5-> 6969, Distance = D4 + D5 = 1861.97
	// Route 2 is the winner

	// Two Logical Routes between 4078 and 2962
	// Route 3: 4078 -D6-> 2968 -D7-> 2990 -D8-> 4029 -D9-> 6969 -D10-> 2962
	// Distance = D6 + D7 + D8 + D9 + D10 = 5130.98

	// Route 4: 4078 -D6-> 2968 -D7-> 2990 -D11-> 2966 -D12-> 2962
	// Distance = D6 + D7 + D11 + D12 = 3597.74
	// Route 4 is the winner
	*/

}

TEST_CASE("testDijkstraMedium", "[dijkstra][2]") {
	
	Graph graph1 = Graph("tests/routesDataMedium.txt", "tests/airportsDataMedium.txt");
	vector<Node*> node = graph1.getNodes();

	Node* node2966 = node[2966];
	Node* node6969 = node[6969];

	Node* node4078 = node[4078];
	Node* node2962 = node[2962];

	vector<Node*> route1 = graph1.shortestPath(2966, 6969);
	vector<Node*> route2 = graph1.shortestPath(4078, 2962);

	vector<Node*> expected1{node2966, node[2962], node6969};
	vector<Node*> expected2{node4078, node[2968], node[2990], node[2966], node2962}; 

	Node temp;

	REQUIRE(route1.size() == expected1.size());
	REQUIRE(route2.size() == expected2.size());
	REQUIRE(temp.getRouteDistance(route1) == temp.getRouteDistance(expected1));
	REQUIRE(temp.getRouteDistance(route2) == temp.getRouteDistance(expected2));

	std::cout << "Dijkstra test passes on medium data" << std::endl;
}

TEST_CASE("Easy Dijkstra test on full data", "[dijkstra][3]") {
	Graph graph("dataset/routes.txt", "dataset/airports.txt");
	vector<Node*> nodes = graph.getNodes();

	// Node with 30 neighbors
	Node* node4075 = nodes[4075];
	Node* node2047 = nodes[2047];
	Node* node2006 = nodes[2006];

	vector<Node*> route = graph.shortestPath(4075, 2047);

	REQUIRE(route.size() == 3);
	REQUIRE(route[0] == node4075);
	REQUIRE(route[1] == node2006);
	REQUIRE(route[2] == node2047);

	std::cout << "Dijkstra test passes on full data" << std::endl;

	/*
	TEST VERIFICATION
	for (Node * node : _node->neighbors()) {
		
		if (_node->distance(node) < dist) {
			dist = _node->distance(node);
			shortest = node;
		}
		
		if (node->airportCode() == 2047) {
			std::cout << "Airport 2006 has route to Airport " << node->airportCode() << " with distance " << _node->distance(node) << std::endl;
			std::cout << "Airport 2006 has lat,lng: " << _node->latitude() << ", " << _node->longitude() << std::endl;
			std::cout << "Airport " << node->airportCode() << " has lat,lng: " << node->latitude() << ", " << node->longitude() << std::endl;
				//break;
		}
	}
	

	std::cout << "The closest Node to Aiport 4075 is Airport " << shortest->airportCode() << " (" << dist << " away)." << std::endl;

	4075 is Faa'a International Airport, French Polynesia
	2006 is Auckland International Airport
	2047 is Wanganui Airport, New Zealand. There is no route from 4075 to 2047.

	Dijkstra's Path from 4075 to 2047 should be 4075 -> 2006 -> 2047 

	Path from 4075 -> 2006 is 4093.37
	Path from 2006 -> 2047 is 329.106
	Total Dist: 4422.476
	*/
}