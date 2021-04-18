
#include <Airports.h>

Airports::Airports() {
    
    fstream file;
    file.open("airports.dat.txt", ios::in);

    std::vector<string> line;

    string row, word, name, city;
    double latitude, longitude;

    while (file >> longitude) {
        getline(file, row);

        string stream ss(row);

        while(getline(ss, word, ',')) {
            
        }
    }
}