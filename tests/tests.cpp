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

using namespace std;


TEST_CASE("Verify that file_to_string works on a small example", "[readFile]") {
	std::string res = file_to_string("tests/smallSample.txt");
	// always check "expected" == "actual" --> be consistent

	std::cout << res << std::endl;
	REQUIRE("hello\nstudents\nof\ncs\n225\n!!!\n" == res);
}

TEST_CASE("Verify that file_to_vector works on a small example", "[readFile]") {
	std::vector<std::string> res = file_to_vector("tests/smallSample.txt");
	std::string expected[] = {"hello", "students", "of", "cs", "225", "!!!"};

	for (unsigned i = 0; i < res.size(); i++) {
		std::cout << res[i] << std::endl;
	}
	
	REQUIRE(6 == res.size());

	for (int i = 0; i < res.size(); i++) {
		REQUIRE(expected[i] == res[i]);
	}
}

TEST_CASE("Check Airports ctor populates lat_long correctly") {
	Airports airports("tests/airportsDataSmall.txt");

	REQUIRE(airports.latitude(1) == -6.081689834590001);
	REQUIRE(airports.latitude(2) == -5.20707988739);
	REQUIRE(airports.latitude(3) == -5.826789855957031);
	REQUIRE(airports.longitude(1) == 145.391998291);
	REQUIRE(airports.longitude(2) == 145.789001465);
	REQUIRE(airports.longitude(3) == 144.29600524902344);
}

TEST_CASE("Check Airports ctor with full data") {
	Airports airports("dataset/airports.txt");

	REQUIRE(airports.latitude(45) == 49.21080017089844);
	REQUIRE(airports.latitude(426) == 61.24919891357422);
	REQUIRE(airports.latitude(468) == 55.04280090332031);
	REQUIRE(airports.longitude(3348) == 114.088996887);
	REQUIRE(airports.longitude(3675) == -87.395401001);
	REQUIRE(airports.longitude(6712) == -151.7429962);
	REQUIRE(airports.longitude(14110) == 35.305);
}

/*
TEST_CASE("Check that Edge class calculates distance correctly (requires Node and Edge to work)") {
	//sample lat long coordinates from google
	Node ORD(3830, 41.9773, -87.8369); //chicago
	Node JFK(3797, 40.6413, -73.5581); //NY
	Node ICN(3930, 37.4602, 126.4407); //icheon
	Node HND(2359, 35.5494, 139.7798); //tokyo
	Node CMI(4049, 40.0365, -88.2640); //champaign

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
}
*/

TEST_CASE("Test sample data on Graph Ctor") {
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
}

TEST_CASE("Graph Ctor simple data maintains neighbors correctly", "[part=4]") {

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
}

TEST_CASE("Test functionality of areNeighbors", "[part=3]") {
	Node* node1 = new Node(123, 65.666, 34.44);
	Node* node2 = new Node(345, -65.22, 90.4565);

	node1->addNeighbor(node2);

	REQUIRE(node1->neighbors().size() == 1);
	REQUIRE(node2->neighbors().size() == 0);
}

TEST_CASE("Graph Ctor maintains propor neighbors medium complexity", "[part=5]") {

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

	//Graph graph("tests/routesSimpleDataSmall.txt", "tests/airportsDataSmall.txt");

	Graph graph("tests/routesDataMedium.txt", "dataset/airports.txt");
	vector<Node*> nodes = graph.getNodes();

	Node*& node2965 = nodes[2965];
	std::cout << node2965->neighbors().size() << std::endl;
	Node*& node2990 = nodes[2990];
	std::cout << node2990->neighbors().size() << std::endl;
	Node* node2966 = nodes[2966];
	Node* node2962 = nodes[2962];
	Node* node2968 = nodes[2968];
	Node* node4078 = nodes[4078];
	Node* node4029 = nodes[4029];
	Node* node6969 = nodes[6969];

	/*
	list<Node*> exp2965 {nodes[1]};
	list<Node*> exp2990 {nodes[0], nodes[2], nodes[4], nodes[6]};
	list<Node*> exp2966 {nodes[1], nodes[3]};
	list<Node*> exp2962 {nodes[2]};
	list<Node*> exp2968 {nodes[1], nodes[5]};
	list<Node*> exp4078 {nodes[4]};
	list<Node*> exp4029 {nodes[1], nodes[7]};
	list<Node*> exp6969 {nodes[6]};
	*/

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

	//REQUIRE(node2962->neighbors() == exp2962);
	//REQUIRE(node2968->neighbors() == exp2968);
	//REQUIRE(node4078->neighbors() == exp4078);
	//REQUIRE(node4029->neighbors() == exp4029);
	//REQUIRE(node6969->neighbors() == exp6969);
}

TEST_CASE("Graph Ctor doesn't add repeat nodes") {
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

}

TEST_CASE("Graph Ctor complex data maintains nodes and edges correctly") {}

TEST_CASE("Graph Ctor complex data maintains neighbors correctly") {}

TEST_CASE("Graph Ctor does nothing with null or invalid airports") {

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


}


TEST_CASE("Graph Ctor compiles on full data set", "[part=6]") {
	Graph graph("dataset/routes.txt", "dataset/airports.txt");
}

TEST_CASE("BFS Traversal traverses through a Graph correctly", "[bfs]") {
	/*Graph graph1("tests/routesDataMedium.txt", "dataset/airports.txt");
	BFS bfs1(graph1, graph1.getFirstNode());
    vector<int> vector1 = bfs1.traverse();
	for (unsigned long i = 0; i < vector1.size(); i++) {
		cout << "vector1 " << vector1[i] << endl;
	}*/
	//REQUIRE
	
	cout << "BFS test started" << endl;
	Graph graph2("tests/smallRoutes2.txt", "tests/smallAirports2.txt");
	BFS bfs2(graph2, graph2.getFirstNode());
	vector<int> vector2 = bfs2.traverse();
	vector<int> expected2{1, 2, 3, 4, 5, 6}; 
	for (unsigned long i = 0; i < vector2.size(); i++) {
		REQUIRE(expected2[i] == vector2[i]);
	}
	
}

TEST_CASE("dummy test", "[dummy]") {
	int dummy = 5;
	REQUIRE(dummy == 5);
}
