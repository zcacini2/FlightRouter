# CS225 Final Project 

## Team Members: Giwon Jung, Krystyna Madel, and Zach Cacini

**Our Project**

For our final project, we have decided to implement a graph-based flight routing program. The OpenFlights Data Set (https://openflights.org/data.html) provides our team access to over 67,000 flight routes and over 10,000 airports to contruct our edges and nodes, respectively. We weigh our edges using the physical distance between the two airports, and using DIjkstra's Shortest Path Algorithm, we are able to output the shortest path between any two nodes and the graphical output onto a map. 

**Datasets**

The full datasets for our project are the routes.txt and airports.txt files included in the dataset folder in the repo. Here, you can finda. listing of all routes and airports. However, the routes are coded by airport code. We chose to use the OpenFlights identifier code for our project. This code is an ambiguous numbering of airports from the airports.txt file. Using these airport codes, we were better able to index and store our airports because we coudl use the integer codes as indicies. 

An entry in the airports.txt file is as follows: 3830,"Chicago O'Hare International Airport","Chicago","United States","ORD","KORD",41.9786,-87.9048,672, -6,"A","America/Chicago","airport","OurAirports". 3830, the first entry, is the unique OpenFlights airport code. "Chicago O'Hare International Airport", the second entry, is the name of the airport. 41.9786, the seventh entry, is the latitude. -87.9048, the eighth entry, is the longitude. 

An entry in the routes.txt file is as follows: 3E,10739,ORD,3830,DEC,4042,,0,CNC. 3830, the fourth entry, corresponds to the source airport OpenFlights airport code. In this instance 3830 corresponds to Chicago O'Hare International Airport. The second and last important value in the routes entries is 4042, the sixth entry. This value corresponds to the destination airport OpenFlights airport code. 4042 corresponds to Decatur Airport. Therefore, this entry is a route from Chicago O'Hare International Airport to Decatur Airport. To build the route, we must use latitudinal and longitudinal information from the airports.txt entries and calculate distance and other qualities.

**Code Base**



README which describes: (1) The location of all major code, data, and results. (2) Full instructions on how to build and run your executable, including how to
define the input data and output location for each method. (3) Full instructions how to build and run your test suite, including a general description on what 
tests you have created. It is in your best interest to make the instructions (and the running of your executables and tests) as simple and straightforward as 
possible.

