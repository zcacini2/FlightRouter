#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <string>

#include "readFromFile.hpp"

class Airports {
    public:

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

    private:

        /** 
         * TO BE ADDED TO FUNCTIONALITY LATER!!
         * Index corresponds to the OpenFlights identifier.
         * Data stored: Airport Name and City of Airport.
         */
        std::vector<std::vector<std::string>> airports;

        /**
         * Index corresponds to the OpenFlights identifier.
         * Data stored: Latitude and Longitude.
         */
        std::vector<std::vector<double>> lat_long;

};