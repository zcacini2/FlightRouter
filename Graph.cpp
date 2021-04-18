#include "Graph.h"
#include <vector>
#include "Edge.h"


void Graph:: insertNode(Node toAdd){
/*  if (toAdd == NULL){
    Node node = new Node
  }*/
  //if there already exists toAdd node, remove it
    removeNode(toAdd)
    //add empty node
    adjacent_list(toAdd) = unordered_map<Node,Edge>()
}

void Graph::removeNode(Node toRemove){
  //if the node is not at the end of the graph,
  if (adjacent_list.find(toRemove) != adjacent_list.end()){
    for (auto i = adjacent_list[toRemove].begin(); i != adjacent_list.end(); i++) {
        Node n = i->first;
        adjacent_list[u].erase(v);

    }
    adjacent_list.erase(v);
  }
}

void Graph::insertEdge(Node start, Node goal){
  //Edge newEdge = New Edge(node1, node2);

  //if edge already exists
  if(adjacent_list.find(start)!= adjacent_list.end()
    && adjacent_list[start].find(goal)!= adjacent_list[start].end()){
        return;
    }

  // if start nod does not exists, add it
  if(adjacent_list.find(start)==adjacent_list.end()){
    adjacent_list[start] = unordered_map<Node, Edge>();
  }

  // if start nod exists and edge does not exists between start and goal,
  // add new edge
    adjacent_list[start][goal] = Edge(start, goal);
}

void Graph::removeEdge(Node start, Node goal){
  //shouldn't we check whether the node exists or not first?

  // check whether edge exists or not
  if (adjacent_list[start].find(goal) != adjacent_list[start].end()){
    adjacent_list[start].erase(goal);
  }
}

bool Graph::areAdjacent(Node node1, Node node2){
  auto list_1 = adjacent_list.find(node1);
  auto list_2 = adjacent_list.find(node2);
  if ()
}
