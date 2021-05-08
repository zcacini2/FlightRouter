#include "Airports.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "readFromFile.hpp"

Airports::Airports() {
  
}

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

  // Default lat_lng entry
  std::vector<double> location;
  location.push_back(-1000);
  location.push_back(-1000);
  
  // Default airports entry
  std::string name = "Name";

  // Push back all default array vals
  for (unsigned i = 0; i < 14111; i++) {
    lat_long.push_back(location);
    names.push_back(name);
  }

  // Clear lat_lng default, will be used
  location.clear();

  // Initialize data parsing values
  std::vector<std::string> line;  //create line vector
  std::stringstream s_stream(str); //create string stream from the string
  int airportCode;
  double lat, lng;
  
  // Proceed until no more data
  while(s_stream.good()) {
    std::string row, substr;
    getline(s_stream, row, '\n'); //get first string delimited by comma
    std::stringstream row_stream(row);

    // For each line, clean quotation marks and form into line vector
    while (row_stream.good()) {
      getline(row_stream, substr, ',');
      substr.erase(std::remove( substr.begin(), substr.end(), '\"' ), substr.end()); //cleans quotations
      line.push_back(substr);
    }

    // Access meaningful data
    lat = stod(line[6]);
    lng = stod(line[7]);
    name = line[1];
    airportCode = stoi(line[0]);

    // Prep location to store lat and lng
    location.clear();
    location.push_back(lat);
    location.push_back(lng);
    lat_long[airportCode] = location; // Insert into lat_lng

    names[airportCode] = name;  // Insert name into names

    location.clear();
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

/**
 * Gets the name of the airport.
 * 
 * @param code airport code
 *
 * @return name of the airport of provided code
 */
std::string Airports::name(int code) {
    return names[code];
}

/**
 * This method will return the size of the lat_lng vector. Not necessarily equal to num of airports because airports stored by index.
 * 
 * @return size of lat_lng
 */
unsigned Airports::size() {
  return lat_long.size();
}

