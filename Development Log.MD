Week 1 (April 7-14): *committed in project proposal before committed here*
This week, after we had out team contract and project proposal straightened out, we began working on the project itself. We successfully imported all the relevant datasets from the FlightStats website and placed it into a folder of text files in CSV format for future use. After that, other initial folders were added, such as the cs225 PNG class and its related resources, the make folder, the catch folder, and a Makefile template. Some these things came from the model final project repo and others came from the cs225 course. The Graph, Node, and Edge classes were also started as a skeleton for our project, and the graph and edge functions and variables began to be implemented.
Reponsibilities:
-Krystyna: Initial project files, Node and Edge classes
-Zach: Dataset processing/acquisition
-Giwon: Implementation of Graph class

Week 2 (April 14-21): *committed in project proposal before committed here*
This week, the Node and Edge classes were implemented completely. We came across quite a few obstacles when it came to compiling and using a makefile properly, as we had no knowledge or experience with that, but we were able to get our code to function. We also continued implementation of the Graph class and created a whole new Airport class to help with the processing of the data sets and to act as a medium between the dataset textfiles and the Graph class. We came across some team logistic and implementation issues with the Graph class, and the code was almost entirely reworked.
At this point, we also began working on our BFS traversal of our graph ahead of time for our mid-project check in.
Responsibilities:
-Krystyna: BFS Traversal, BFS test cases, help redo Graph class
-Zach: Redid Graph class/constructor, compatibility with entire dataset
-Giwon: Start out implementation for Dijkstra's algorithm

*NOTE: We had our mid-project check in after week 2, during which we were told to make sure to keep a weekly dev log of our progress. Up until that point, we had been keeping very broad bullet point notes of what parts of the project were to be done and who was responsible for each part at the bottom of our project proposal with frequent commits. We also kept a google doc that is more detailed*

Week 3 (April 21-28):
After ironing out many problems and wrinkles with our Graph constructor and its compatibility with the entire dataset and the traversal, we were finally able to get the most important part of the project fully functional along with its BFS traversal. We began implementation of our shortest path algorithm (Dijkstra's algorithm) with no product or result so far. We also created a skeleton for the implementation of our graphical representation algorithm, which will manipulate a PNG based on the output of our project pending the completion of our Dijkstra's algorithm.
Responsibilities:
-Krystyna: Begin graphical representation algorithm, fix/rewrite devlog
-Zach: Writing a lot more tests, helping out with rest
-Giwon: Finish Dijkstra's algorithm

Week 4 (April 29 - May 5):
Our shortest path algorith is now fully functional, and we now have an elaborate user interface for our program through the console.
This ties together all of our work into the final product, which is a route finder that the user interacts with by putting in their
desired origin and destination airports to be given a graphical output of what they asked for. The console gives full user-friendly 
messages to the user and has many protections built in at this time. The graphical representation of our final product is also fully complete and can now print airports and routes on a map of the world. A few extra tests were also added. At this point, we will just be polishing up a few extra things and working on our final deliverables.


