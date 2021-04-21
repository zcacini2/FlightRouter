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

using namespace std;


TEST_CASE("Verify that file_to_string works on a small example") {
	std::string res = file_to_string("tests/smallSample.txt");
	// always check "expected" == "actual" --> be consistent

	std::cout << res << std::endl;
	REQUIRE("hello\nstudents\nof\ncs\n225\n!!!\n" == res);
}

TEST_CASE("Verify that file_to_vector works on a small example") {
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

TEST_CASE("Test behavior of CSV file parsing", "[part=1]") {
	
	std::string str = file_to_string("tests/airportsDataSmall.txt");

  	std::vector<string> line;  //create line vector
	stringstream s_stream(str); //create string stream from the string
  	string airportID, lat, lng;
	int count = 0;

  	while(s_stream.good()) {
		string row, substr;
		getline(s_stream, row, '\n'); //get first string delimited by comma
		stringstream row_stream(row);

		while (row_stream.good()) {
			getline(row_stream, substr, ',');
			substr.erase(std::remove( substr.begin(), substr.end(), '\"' ), substr.end()); //cleans quotations
			line.push_back(substr);
			std::cout << line.back() << std::endl;
		}
		
		airportID = line[0];
		lat = line[6];
		lng = line[7];
		
		line.clear();
		std::cout << airportID << ", " << lat << ", " << lng << std::endl;

  	}

	REQUIRE(line[0] == "3");
	
}

TEST_CASE("Check Airports ctor populates lat_long correctly", "[part=0]") {
	Airports airports("tests/airportsDataSmall.txt");

	REQUIRE(airports.latitude(0) == -6.081689834590001);
	REQUIRE(airports.latitude(1) == -5.20707988739);
	REQUIRE(airports.latitude(2) == -5.826789855957031);
	REQUIRE(airports.longitude(0) == 145.391998291);
	REQUIRE(airports.longitude(1) == 145.789001465);
	REQUIRE(airports.longitude(2) == 144.29600524902344);
}


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

TEST_CASE("Test sample data on Graph Ctor") {
	Graph graph("tests/routesDataSmall.txt");
	vector<Node> nodes = graph.getNodes();
	vector<Edge> edges = graph.getEdges();

	vector<double> nodesLats{-6.081689834590001, -5.20707988739, -5.826789855957031, -6.569803};

	for (unsigned i = 1; i <= nodes.size(); i++) {
		REQUIRE(nodes[i].latitude() == nodesLats[i]);
	}

	for (unsigned i = 1; i <= edges.size(); i++) {
		REQUIRE(edges[i].start().latitude() == nodesLats[i]);
	}
}



