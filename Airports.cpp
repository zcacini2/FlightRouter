#include "Airports.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "readFromFile.hpp"



/** 
 * This method will handle the airport coder/decoder. This will be maintained as 2 vectors. The vector's
 * indices correspond to the OpenFlights ID. This will aid the creation of nodes by matching airport ID
 * to the lat/long found in the airports file. 
 * 
 * This method will accomplish this by first translating the file into a vector, and then pulling all relevant
 * information. The information stored in the airports file is as follows: Airport ID (OpenFlights ID), Name,
 * City, Country, 3 Letter IATA code, 4 Letter ICAO code, Latitude, Longitude, Altitude, Timezone, DST, Tz
 * database time zone, and source. Relevant information is Airport ID (OpenFlights ID), Latitude, and Longitude. 
 * Later we will add Name and City.
 * 
 * @param filename name of file to parse to fill airport information.
 */
Airports::Airports(const std::string & filename) {

  std::string str = file_to_string(filename);

  std::vector<double> tmp;
  tmp.push_back(-1000);
  tmp.push_back(-1000);
  //lat_long.push_back(tmp);

  //lat_long.resize(14111);

  std::cout << "Airports vector begin filling with empty latlng" << std::endl;

  for (unsigned i = 0; i < 14111; i++) {
    lat_long.push_back(tmp);
  }

  std::cout << "Airports vector filled with empty latlng" << std::endl;

  tmp.clear();


  std::vector<std::string> line;  //create line vector
  std::stringstream s_stream(str); //create string stream from the string
  int airportCode;
  double lat, lng;
  

  while(s_stream.good()) {
    std::string row, substr;
    getline(s_stream, row, '\n'); //get first string delimited by comma
    std::stringstream row_stream(row);

    while (row_stream.good()) {
      getline(row_stream, substr, ',');
      substr.erase(std::remove( substr.begin(), substr.end(), '\"' ), substr.end()); //cleans quotations
      line.push_back(substr);
    }
    
    
    lat = stod(line[6]);
    lng = stod(line[7]);
    airportCode = stoi(line[0]);
    

    /*
    try {
      lat = stod(line[6]);
    } catch (...) {
      std::cerr << "Invalid lat on line " << lat_long.size() << " with value " << line[6] << std::endl;
      break;
    }
    
    try {
      lng = stod(line[7]);
    } catch (...) {
      std::cerr << "Invalid lng on line " << lat_long.size() << " with value " << line[7] << std::endl;
      break;
    }

    try {
      airportCode = stoi(line[0]);
    } catch (...) {
      std::cerr << "Invalid code on line " << lat_long.size() << " with value " << line[0] << std::endl;
      break;
    }
    */
    
    //name = line[1];
    //city = line[2];

    tmp.clear();

    tmp.push_back(lat);
    tmp.push_back(lng);
    lat_long[airportCode] = tmp;

    tmp.clear();
    line.clear();

  }
}

/**
 * Gets the latitude of the airport.
 * 
 * @param code airport code
 *
 * @return latitude of the airport of provided code
 */
double Airports::latitude(int code) {
    return lat_long[code][0];
}

/**
 * Gets the longitude of the airport.
 * 
 * @param code airport code
 *
 * @return longitude of the airport of provided code
 */
double Airports::longitude(int code) {
    return lat_long[code][1];
}

unsigned Airports::size() {
  return lat_long.size();
}