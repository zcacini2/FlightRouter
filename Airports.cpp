
#include <Airports.h>
#include <readFromFile.cpp>

Airports::Airports(const std::string & filename) {
    
    std::vector<string> file = file_to_vector(filename);
    for (int i = 0; i < file.size(); i++) {
        std::cout << file[i] << std::endl;
    }
}