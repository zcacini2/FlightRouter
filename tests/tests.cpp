#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "../catch/catch.hpp"
#include "../readFromFile.hpp"
#include "../Node.h"
#include "../Edge.h"
//#include "../Graph.h"

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

TEST_CASE("Determine behavior of file_to_string on CSV") {
	std::string res = file_to_string("tests/airportsDataSmall.txt");
	std::string res2 = file_to_string("tests/cs225testdata.txt");
	
	//std::string expected[] = {"hello", "students", "of", "cs", "225", "!!!"};
	
	//REQUIRE(6 == res.size());

	std::cout << res2 << std::endl;
	std::cout << res << std::endl;
	for (int i = 0; i < res.size(); i++) {
		//REQUIRE(expected[i] == res[i]);
	}
}

TEST_CASE("Testing string to vector on file_to_string on CSV") {
	std::string res = file_to_string("tests/airportsDataSmall.txt");
	std::string res2 = file_to_string("tests/cs225testdata.txt");
	
	//std::string expected[] = {"hello", "students", "of", "cs", "225", "!!!"};

	std::vector<string> result;
	stringstream s_stream(res); //create string stream from the string
   	while(s_stream.good()) {
      string substr;
      getline(s_stream, substr, ','); //get first string delimited by comma
      result.push_back(substr);
   	}

	for (unsigned i = 0; i < result.size(); i++) {
		std::cout << result[i] << std::endl;
	}
	
}

TEST_CASE("Test behavior of CSV file parsing") {
	
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

TEST_CASE("Check airportCoder populates lat_lng correctly", "[part=0]") {
	
}

TEST_CASE("Check that Edge class calculates distance correctly (requires Node and Edge to work)") {
	//sample lat long coordinates from google
	Node ORD("ORD", 41.9773, -87.8369); //chicago
	Node JFK("JFK", 40.6413, -73.5581); //NY
	Node ICN("ICN", 37.4602, 126.4407); //icheon
	Node HND("HND", 35.5494, 139.7798); //tokyo
	Node CMI("CMI", 40.0365, -88.2640); //champaign

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




