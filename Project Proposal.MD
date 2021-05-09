CS225 Data Structures Final Project 

Project Proposal (madel3-zcacini2-gjung10)

Google Doc Link: https://docs.google.com/document/d/1cuo78FzsqoF4lvTw05_gfvHy_nqAWimyw_5TowVx7Z0/edit?usp=sharing

Leading Question: 

We will create a routing search tool for flights using flight path data. Since June 2014, this data set has been updated with flight data from over 67,000 routes, 
between about 7000 airports and carried by over 500 different airlines. Additional data that is provided is airport coordinates. We hope to use this information to 
weigh the different paths according to distance between airports. Using this weighting scheme, we would be able to find the shortest (physical distance) path 
between any airport in the world. Secondarily, we will use the graph to construct a visual mapping of these routes. 

A successful product will be able to intake a data set containing thousands of routes and airports and construct a graph of these points. Then, a user can input 
any two airports in the world and compute the shortest path (between other airports or a direct connection if an edge exists between the two airports). The 
shortest path will be output by airport and visualized on a map. This product would also be able to project visually a map of airports and/or routes depending on 
user input. The exact options and inputs are still to be determined.

Dataset Acquisition and Processing: 

We have chosen to use the OpenFlights Data Set (https://openflights.org/data.html). The website above provides raw 2017 data of about 7000 airports as well as 
raw route data from 2014, which details source and destination airports for over 67 000 routes. The route data, along with the airport data, can be used to figure 
out what real world connections exist between airports, as well as what their distances are.  This data comes in raw text form in a comma separated format. With 
that in mind, we will have to process and organize the data into a database that will suit our needs and leave out the unnecessary details included. We are unsure 
exactly what this final database will look like, but it will likely remain in some sort of comma-separated text format. The source website has some discrepancies 
in terms of the data it provides; most notably, the airport data posted is from 2017 whereas the route data is from 2014, so there are bound to be situations 
where there are airports with no routes and routes with airports that may not exist anymore. We will have to implement checks into our code that output an error 
message specific to these cases and any others we find on the way.

Graph Algorithms: 

To construct the graph, we will pass in both a CSV of route data and a CSV of airport data to decode the airport codes in the route data CSV. The traversal of 
the graph will likely be a BFS or DFS traversal that will be dictated by design choices for our algorithm.
We plan to cover the shortest path algorithm. This algorithm will take two airports as input and compute the shortest path between them. It will compute the 
shortest path through the routes (edges) of our graph. The graph we will create will be a directed graph constructed by each airport to airport route. The nodes 
will be the airports, and the edges will be weighted by the distance between the two airports. The output will be a string of airports that represent the shortest 
path between flight routes to the two airports. If the two airports are directly connected, the shortest path will simply be that edge. We hope that this algorithm 
will have a runtime of O(log(n)).

Additionally, we will implement a map visualization of this path as our second method. Mapping this path by the coordinates of the airports in latitudinal and 
longitudinal space to the pixels of a PNG map. This will act as a secondary output of the shortest path algorithm. This method will take in a list of the airports
representing the shortest path. 

Timeline: 

Tasks: Data Acquisition, Data Processing, Traversal, Shortest Path Algorithm, Graphical Visualization, and Final Deliverables

Week 1 (April 7-14): Data Acquisition and Processing, beginning graph constructor
 - Data Acquisition and Processing: Zach 
 - Implementing graph class: Giwon
 - Implementing node and edge class: Krystyna
 
Week 2 (April 14-21): Traversal and Begin Shortest Path Algorithm
Krys:
BFS Traversal test cases

Giwon:
Start out the bare bones/files for shortest path algorithm
Psuedocode/Approach for the algorithm

Zach:
Graph Ctor tests and Compatibility with big data set


(Mid-Semester Check-In Apr 19-23)

Week 3 (April 21-28): Finish Shortest Path and Begin Graphical Representation

Week 4 (April 28 - May 5): Finish Graphical Representation and Polish off Code

Week 5 (May 5-12): Final Deliverables (Record Presentation)


