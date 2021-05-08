# CS225 Final Project 

## Team Members: Giwon Jung, Krystyna Madel, and Zach Cacini

**Our Project**

For our final project, we have decided to implement a graph-based flight routing program. The OpenFlights Data Set (https://openflights.org/data.html) provides our team access to over 67,000 flight routes and over 10,000 airports to contruct our edges and nodes, respectively. We weigh our edges using the physical distance between the two airports, and using DIjkstra's Shortest Path Algorithm, we are able to output the shortest path between any two nodes and the graphical output onto a map. 

**Datasets**

The full datasets for our project are the routes.txt and airports.txt files included in the dataset folder in the repo. Here, you can finda. listing of all routes and airports. However, the routes are coded by airport code. We chose to use the OpenFlights identifier code for our project. This code is an ambiguous numbering of airports from the airports.txt file. Using these airport codes, we were better able to index and store our airports because we coudl use the integer codes as indicies. An entry in the airports.txt file is as follows: "".

README which describes: (1) The location of all major code, data, and results. (2) Full instructions on how to build and run your executable, including how to
define the input data and output location for each method. (3) Full instructions how to build and run your test suite, including a general description on what 
tests you have created. It is in your best interest to make the instructions (and the running of your executables and tests) as simple and straightforward as 
possible.

