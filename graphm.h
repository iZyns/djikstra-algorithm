#ifndef GRAPHM_H
#define GRAPHM_H
#include "nodedata.h"
#include <climits>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class GraphM {
  static const int MAXNODES = 100;

public:
  GraphM();
  void buildGraph(ifstream &infile);
  void insertEdge(int fromNode, int toNode, int distance);
  void removeEdge(int fromNode, int toNode);
  void findShortestPath();
  void displayAll() const;
  void display(int fromNode, int toNode) const;

private:
  struct TableType {
    bool visited; // whether node has been visited
    int dist;     // shortest distance from source known so far
    int path;     // previous node in path of min dist
  };
  NodeData data[MAXNODES];         // data for graph nodes
  int C[MAXNODES][MAXNODES];       // Cost array, the adjacency matrix
  int size;                        // number of nodes in the graph
  TableType T[MAXNODES][MAXNODES]; // stores visited, distance, path
  void findPath(int fromNode, int toNode) const;
  void findName(int fromNode, int toNode) const;
};

#endif