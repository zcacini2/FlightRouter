#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <string>

#include "readFromFile.hpp"

/**
 * The following class is used as a coding/decoding process with the airports.txt file and the airport codes found in the routes.txt file. This 
 * will be used as an external storage process to simplify Graph.
 */

class Airports {
    public:

        /**
         * Default airports ctor
         */
        Airports();

        /** 
         * This constructor will handle the airport coder/decoder. This will be maintained as 2 vectors. The vectors'
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
        Airports(const std::string & filename);

        /**
         * Gets the latitude of the airport.
         * 
         * @param code airport code
         *
         * @return latitude of the airport of provided code
         */
        double latitude(int code);

        /**
         * Gets the longitude of the airport.
         * 
         * @param code airport code
         *
         * @return longitude of the airport of provided code
         */
        double longitude(int code);

        /**
         * Gets the number of airports.
         *
         * @return number of airports stored
         */
        unsigned size();

        /**
         * This method returns the airport name for a given airport code
         *
         * @param code airport code
         * 
         * @return string of the airport name for given airport code
         */
        std::string name(int code);
        
    private:

        /** 
         * Index corresponds to the OpenFlights identifier.
         * Data stored: Airport Name
         */
        std::vector<std::string> names;

        /**
         * Index corresponds to the OpenFlights identifier.
         * Data stored: Latitude and Longitude.
         */
        std::vector<std::vector<double>> lat_long;

};