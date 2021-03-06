# CS225 Final Project 

## Team Members: Giwon Jung, Krystyna Madel, and Zach Cacini

**Our Project**

For our final project, we have decided to implement a graph-based flight routing program. The OpenFlights Data Set (https://openflights.org/data.html) provides our team access to over 67,000 flight routes and over 10,000 airports to contruct our edges and nodes, respectively. We weigh our edges using the physical distance between the two airports, and using DIjkstra's Shortest Path Algorithm, we are able to output the shortest path between any two nodes and the graphical output onto a map. 

**Datasets**

The full datasets for our project are the routes.txt and airports.txt files included in the dataset folder in the repo. Here, you can finda. listing of all routes and airports. However, the routes are coded by airport code. We chose to use the OpenFlights identifier code for our project. This code is an ambiguous numbering of airports from the airports.txt file. Using these airport codes, we were better able to index and store our airports because we coudl use the integer codes as indicies. 

An entry in the airports.txt file is as follows: 3830,"Chicago O'Hare International Airport","Chicago","United States","ORD","KORD",41.9786,-87.9048,672, -6,"A","America/Chicago","airport","OurAirports". 3830, the first entry, is the unique OpenFlights airport code. "Chicago O'Hare International Airport", the second entry, is the name of the airport. 41.9786, the seventh entry, is the latitude. -87.9048, the eighth entry, is the longitude. 

An entry in the routes.txt file is as follows: 3E,10739,ORD,3830,DEC,4042,,0,CNC. 3830, the fourth entry, corresponds to the source airport OpenFlights airport code. In this instance 3830 corresponds to Chicago O'Hare International Airport. The second and last important value in the routes entries is 4042, the sixth entry. This value corresponds to the destination airport OpenFlights airport code. 4042 corresponds to Decatur Airport. Therefore, this entry is a route from Chicago O'Hare International Airport to Decatur Airport. To build the route, we must use latitudinal and longitudinal information from the airports.txt entries and calculate distance and other qualities.

**Code Base**

Our code has 6 important classes that all reside in the main project folder. The first class is Airports found in Airports.h. This class is is used as a coding/decoding process with the airports.txt file and the airport codes found in the routes.txt file. This will be used as an external storage process to simplify Graph. Airports stores two vectors; the first holds the names of the airports by airport code, and the second hold the latitude and longitude of the airports by airport code. 
The second class is BFS found in BFS.h. This class provides a BFS traversal of the graph. BFS maintains a vector of booleans of visitied airports, a graph object, and a queue to use for traversal. 
The third class is the Edge class found in Edge.h. This class represents an edge of the graph (a route between two airports). It maintains the start and end airport as well as the distance between them. 
The fourth and most important class is Graph found in Graph.h. This class is responsible for the actual graph. This class holds the graph constructor (parsing the routes.txt file and building every node and edge from each entry) and our implementaion of the Dijkstra Shortest Path algorithm. Each graph holds a vector of Node* airports and a vector of Edges. 
The fifth class is MapPrinter found in mapprinter.h. This class maintains all of the logic to print a shortest path onto a Mercator Projection Map. This class maintains a graph and a PNG for the map.
The last class is the Node class found in Node.h. This class is the definition of a node that represents an airport. Nodes maintain its own airport code, latitude, longitude, a list of all neighbors (Node*), and a list of all neighbors (int airport codes). 

**User Interaction** 

The user will only interact with main. To build our program, simply enter `make` into the main directory terminal. Once this command finishes, please then type `./finalproj` into the main directory terminal. The user should then be provided a seamless experience with directions to input their desired source airport and destination airport. If you would like to find another route, simply run `./finalproj` again.

**Input Directions** 

The user has a choice to specify their dataset or to use default datasets. If the user decides to use their own dataset, the user is responsible for ensuring the following:
  1. The filepaths specified are correct and complete (meaning that the computer will recognize where it is within the main project directory).
  2. Both the airports and routes datasets match the formatting of the OpenFlights data sets uses to construct the project.
  3. The airports and routes data correspond to each other (If there are routes with airport codes not included in the airports dataset, the program will crash).
  
As a result, it is typically easier to use the datasets provided; however, if you have datasets that match there criteria, feel free to use them!

The user will have to input an integer airport code for the code to find the route. The full listing of possible integer airport codes is found in airports.txt, found in the dataset folder of our project. Here, like explained earlier, all airport codes and coresponding airport names are found. If you would like to search for a specific airport code for a certin airport, use your machines "Find on Page" feature. For Mac users, this will be Command + F. For Windows users, this will be Control + F. To search for the airport code for London Heathrow Airport, simply enter London Heathrow Airport. Also, due to the extra airport qualifiers in each entry, a search of United Kingdom will bring up all airports in the United Kingdom. Some airports included in the airports.txt file do not have any provided routes to or from itself in the routes.txt file. If you choose an airport without any routes, the system will tell you that there are no routes through this airport and that it is invalid. Please choose a different airport because we have no data on this airport to find the shortest path.

**Output**

Our code will output the names and airport codes of the list of airports representing the shortest path between the source and destination airports directly to the terminal. The user has a choice to specify a filename ending in .png for where they would like to have the map graphical output stored, or they can default to output.png. The purple square represents the start airport, and the green square represents the destination airport.

**Test Suite**

All of our tests are included in the tests folder of our project in the tests.cpp file. We have 23 test cases. To build the test suite, please run `make test` in the main directory terminal. Then, to run all test cases, run `./test`. To run specific groups of test, we have provided special codes. To run all test cases regarding the Airports class, run `./test [airports]`. To run all test cases regarding the Edge class, run `./test [edge]`. To run all test cases regarding the Node class, run `./test [node]`. To run all test cases regarding the Graph class, run `./test [graph]`. To run all test cases regarding the BFS class, run `./test [bfs]`. To run all test cases regarding the MapPrinter class, run `./test [mapprinter]`. To run all test cases regarding the Shortest Path Algorithm, run `./test [dijkstra]`. There is additionally functionality to include [1], [2], etc. to run a single specific test of each test group.
