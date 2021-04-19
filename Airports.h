/**
 * Class definiton for the Airport Decoder.
 */

#include <vector>
#include <string>


class Airports {
    public:

        Airports(string filename);
        
    private:

        /** 
         * Index corresponds to the OpenFlights identifier.
         * Data stored: Airport Name and City of Airport.
         */
        std::vector<std::vector<string>> airports;

        /**
         * Index corresponds to the OpenFlights identifier.
         * Data stored: Latitude and Longitude.
         */
        std::vector<std::vector<double>> lat_long;

};